#!/bin/bash
set -euo pipefail

# Default values
TARGET_DIR="$(pwd)"
CHAT_SHARE_DIR="$TARGET_DIR/chat_share"
LOG_FILE="$CHAT_SHARE_DIR/log.txt"

# Ensure chat_share directory exists
mkdir -p "$CHAT_SHARE_DIR"

# File to track last baseline and last diff commit
TRACK_FILE="$CHAT_SHARE_DIR/tracking_info.txt"

# Function to get the latest Git commit hash (short version)
git_latest_commit() {
    git -C "$TARGET_DIR" rev-parse --short HEAD
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

# Function to log messages
log_message() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a "$LOG_FILE"
}

# Function to run diagnostics
do_diagnostics() {
    local diag_dir="$CHAT_SHARE_DIR/info_for_chat"
    mkdir -p "$diag_dir"
    local diag_file="$diag_dir/system_info.txt"

    log_message "Running system diagnostics..."
    (
        echo "### ENVIRONMENT VARIABLES ###"
        env
        echo "\n### SYSTEM INFO ###"
        uname -a
        echo "\n### NODE & NPM INFO ###"
        node -v 2>/dev/null || echo "Node not installed"
        npm -v 2>/dev/null || echo "NPM not installed"
        echo "\n### PYTHON INFO ###"
        python3 --version 2>/dev/null || echo "Python not installed"
        echo "\n### GIT INFO ###"
        git --version
    ) > "$diag_file"
    log_message "Diagnostics saved to: $diag_file"
}

# Function to run all code checks
do_code_checks() {
    local diag_dir="$CHAT_SHARE_DIR/info_for_chat"
    mkdir -p "$diag_dir"

    log_message "Running ESLint..."
    npx eslint "$TARGET_DIR" --ext .js,.ts,.tsx --no-interactive > "$diag_dir/eslint_results.txt" 2>&1 || log_message "ESLint completed with warnings/errors."

    log_message "Running TypeScript checks..."
    npx tsc --noEmit > "$diag_dir/ts_check_results.txt" 2>&1 || log_message "TypeScript check completed with warnings/errors."

    log_message "Running Prettier..."
    npx prettier --check . > "$diag_dir/prettier_results.txt" 2>&1 || log_message "Prettier found issues."

    log_message "Running Jest..."
    npx --no-install jest --passWithNoTests --detectOpenHandles --no-install > "$diag_dir/jest_results.txt" 2>&1 || log_message "Jest completed with warnings/errors."

    log_message "Running Mocha..."
    npx --no-install mocha --dry-run > "$diag_dir/mocha_results.txt" 2>&1 || log_message "Mocha completed with warnings/errors."

    log_message "Running Vitest..."
    npx --no-install vitest --dry-run > "$diag_dir/vitest_results.txt" 2>&1 || log_message "Vitest completed with warnings/errors."

    log_message "Running Depcheck..."
    npx --no-install depcheck > "$diag_dir/depcheck_results.txt" 2>&1 || log_message "Depcheck found issues."

    log_message "Running TS-Prune..."
    npx ts-prune > "$diag_dir/ts_prune_results.txt" 2>&1 || log_message "TS-Prune found unused exports."

    log_message "Code checks completed."
}

# Function to create a baseline
do_baseline() {
    local baseline_commit="$(git_latest_commit)"
    local baseline_file="$CHAT_SHARE_DIR/baseline_${baseline_commit}.tar.gz"
    local baseline_dir="$CHAT_SHARE_DIR/project"

    log_message "Creating baseline from commit $baseline_commit..."
    mkdir -p "$baseline_dir"
    git -C "$TARGET_DIR" archive --format=tar -o "$CHAT_SHARE_DIR/repo_files.tar" "$baseline_commit"
    tar -xf "$CHAT_SHARE_DIR/repo_files.tar" -C "$baseline_dir"
    rm "$CHAT_SHARE_DIR/repo_files.tar"

    store_commit "baseline" "$baseline_commit"
    do_diagnostics
    do_code_checks

    tar -czf "$baseline_file" -C "$CHAT_SHARE_DIR" project info_for_chat tracking_info.txt
    log_message "Baseline saved: $baseline_file"
}

do_diffs() {
    local current_commit="$(git_latest_commit)"
    local baseline_commit="$(get_stored_commit baseline)"
    local last_diff_commit="$(get_stored_commit last_diff)"

    # Skip diff generation if nothing has changed
    if [[ "$current_commit" == "$baseline_commit" ]]; then
        log_message "No changes detected since the baseline. Skipping diff generation."
        exit 0
    fi

    log_message "Generating diffs..."

    local cumulative_diff_file="$CHAT_SHARE_DIR/cumulative_${baseline_commit}_to_${current_commit}.tar.gz"
    local incremental_diff_file="$CHAT_SHARE_DIR/incremental_${last_diff_commit}_to_${current_commit}.tar.gz"

    # Generate Git patch only if last_diff_commit exists
    if [[ -n "$last_diff_commit" ]]; then
        git -C "$TARGET_DIR" diff "$last_diff_commit" "$current_commit" > "$CHAT_SHARE_DIR/incremental_changes.patch"
    else
        log_message "No previous diff found. Skipping incremental diff."
    fi

    # Generate cumulative diff
    git -C "$TARGET_DIR" diff "$baseline_commit" "$current_commit" > "$CHAT_SHARE_DIR/repo_changes.patch"

    # Run diagnostics and checks
    do_diagnostics #
    do_code_checks

    # Save only the differences in system diagnostics
    diff -u "$CHAT_SHARE_DIR/info_for_chat/system_info.txt" "$CHAT_SHARE_DIR/system_info_${current_commit}.txt" > "$CHAT_SHARE_DIR/info_for_chat/system_info_diff.txt" || true

    # Package cumulative diff
    tar -czf "$cumulative_diff_file" -C "$CHAT_SHARE_DIR" repo_changes.patch info_for_chat/system_info_diff.txt
    log_message "Cumulative diff saved: $cumulative_diff_file"

    # Package incremental diff only if it was generated
    if [[ -f "$CHAT_SHARE_DIR/incremental_changes.patch" ]]; then
        tar -czf "$incremental_diff_file" -C "$CHAT_SHARE_DIR" incremental_changes.patch info_for_chat/system_info_diff.txt
        log_message "Incremental diff saved: $incremental_diff_file"
        store_commit "last_diff" "$current_commit"
    fi
}


# Determine if baseline needs to be created

baseline_file=$(echo "$CHAT_SHARE_DIR"/baseline_*.tar.gz)
baseline_exists=$(test -f "$baseline_file" && echo 1 || echo 0)

if [[ ! -d "$CHAT_SHARE_DIR" || "$baseline_exists" -eq 0 ]]; then
    log_message "No existing chat_share directory or baseline found. Creating a new baseline..."
    do_baseline
    exit 0
fi


# If chat_share exists and baseline is present, generate diffs
do_diffs
