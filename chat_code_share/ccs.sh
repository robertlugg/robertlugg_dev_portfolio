#!/bin/bash
set -euo pipefail

# Function to display usage
usage() {
    echo "Usage: $0 <command> [options]"
    echo "Commands:"
    echo "  baseline -d <directory>    Create a new baseline for the given directory"
    echo "  diff <full|incremental> -d <directory>   Create a diff from the baseline or last diff"
    echo "  apply -d <directory> <diff_file>  Apply a diff to the given directory"
    exit 1
}

# Parse command-line arguments
if [[ $# -lt 2 ]]; then
    usage
fi

COMMAND="$1"
shift

# Default values
TARGET_DIR=""
DIFF_TYPE=""
DIFF_FILE=""

# Parse options
while [[ $# -gt 0 ]]; do
    case "$1" in
        -d)
            shift
            TARGET_DIR="$1"
            ;;
        full|incremental)
            DIFF_TYPE="$1"
            ;;
        *)
            DIFF_FILE="$1"
            ;;
    esac
    shift
done

if [[ -z "$TARGET_DIR" ]]; then
    echo "Error: Missing directory (-d <directory>)"
    usage
fi

# Ensure target directory exists
if [[ ! -d "$TARGET_DIR" ]]; then
    echo "Error: Directory '$TARGET_DIR' does not exist."
    exit 1
fi

# Directory to store baselines and diffs
BASE_DIR="$TARGET_DIR/git_snapshots"
mkdir -p "$BASE_DIR"

# File to track last baseline and last diff commit
TRACK_FILE="$BASE_DIR/tracking_info.txt"

# Function to get the latest Git commit hash
git_latest_commit() {
    git -C "$TARGET_DIR" rev-parse HEAD
}

# Function to get stored commit hash
get_stored_commit() {
    local key="$1"
    grep "^$key=" "$TRACK_FILE" 2>/dev/null | cut -d'=' -f2 || echo ""
}

# Function to store commit hash
store_commit() {
    local key="$1"
    local value="$2"
    grep -v "^$key=" "$TRACK_FILE" 2>/dev/null > "$TRACK_FILE.tmp" || true
    echo "$key=$value" >> "$TRACK_FILE.tmp"
    mv "$TRACK_FILE.tmp" "$TRACK_FILE"
}

# Function to create a baseline
do_baseline() {
    local baseline_commit="$(git_latest_commit)"
    local baseline_file="$BASE_DIR/baseline_${baseline_commit}.tar.gz"

    echo "Creating baseline from commit $baseline_commit in $TARGET_DIR..."
    git -C "$TARGET_DIR" archive --format=tar.gz -o "$baseline_file" "$baseline_commit"
    store_commit "baseline" "$baseline_commit"
    echo "Baseline saved: $baseline_file"
}

# Function to create a diff
do_diff() {
    local current_commit="$(git_latest_commit)"
    local last_commit="$(get_stored_commit baseline)"
    local last_diff_commit="$(get_stored_commit last_diff)"
    local compare_commit="$last_commit"

    if [[ "$DIFF_TYPE" == "incremental" && -n "$last_diff_commit" ]]; then
        compare_commit="$last_diff_commit"
    fi

    if [[ -z "$compare_commit" ]]; then
        echo "Error: No baseline set. Run 'baseline' first."
        exit 1
    fi

    local diff_file="$BASE_DIR/diff_${compare_commit}_to_${current_commit}.tar.gz"
    echo "Creating diff from $compare_commit to $current_commit in $TARGET_DIR..."
    git -C "$TARGET_DIR" diff --name-only "$compare_commit" "$current_commit" | tar -czf "$diff_file" -T -
    store_commit "last_diff" "$current_commit"
    echo "Diff saved: $diff_file"
}

# Function to apply a diff
do_apply() {
    if [[ -z "$DIFF_FILE" ]]; then
        echo "Error: Missing diff file argument"
        usage
    fi
    if [[ ! -f "$DIFF_FILE" ]]; then
        echo "Error: Diff file $DIFF_FILE not found."
        exit 1
    fi
    echo "Applying diff from $DIFF_FILE to $TARGET_DIR..."
    tar -xzf "$DIFF_FILE" -C "$TARGET_DIR"
    echo "Diff applied successfully."
}

case "$COMMAND" in
    baseline)
        do_baseline
        ;;
    diff)
        if [[ -z "$DIFF_TYPE" ]]; then
            echo "Error: Missing diff type (full|incremental)"
            usage
        fi
        do_diff
        ;;
    apply)
        do_apply
        ;;
    *)
        echo "Invalid command. Use: baseline, diff full|incremental, apply <diff_file>"
        usage
        ;;
esac
