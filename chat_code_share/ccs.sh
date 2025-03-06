#!/bin/bash
set -euo pipefail

# Default values
TARGET_DIR="$(realpath .)"  # "$(pwd)"
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

# Check if any commits exist
if ! git -C "$TARGET_DIR" rev-parse --verify HEAD >/dev/null 2>&1; then
    log_message "ERROR: No commits found in this repository. Please commit at least once before running ccs.sh."
    exit 1
fi

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

# Function to run all code checks and store only failures
do_code_checks() {
    local diag_dir="$CHAT_SHARE_DIR/info_for_chat"
    mkdir -p "$diag_dir"
    local json_summary="$CHAT_SHARE_DIR/summary_results.json"
    echo "{}" > "$json_summary"

    declare -A categories=( 
        ["ESLint"]="Linting"
        ["TypeScript Check"]="Compilation"
        ["Prettier"]="Linting"
        ["Jest"]="Tests"
        ["Mocha"]="Tests"
        ["Vitest"]="Tests"
        ["Depcheck"]="Dependencies"
        ["TS-Prune"]="Dependencies"
    )

    declare -A failures

    run_check() {
        local check_name="$1"
        local output_file="$2"
        shift 2

        log_message "Running $check_name..."
        
        if ! "$@" > "$output_file" 2>&1; then
            log_message "$check_name failed. Saving results."

            # Extract meaningful errors (if any) and escape JSON characters
            local summary
            summary=$(head -n 10 "$output_file" | tr '\n' '; ' | jq -Rsa .)

            # Categorize the failure
            local category=""
            case "$check_name" in
                "ESLint" | "Prettier") category="Linting" ;;
                "TypeScript Check" | "TS-Prune") category="Compilation" ;;
                "Jest" | "Mocha" | "Vitest") category="Tests" ;;
                "Depcheck") category="Dependencies" ;;
                "Node.js App Startup") category="Runtime" ;;  # <-- Fix: Assign category!
            esac

            # Update JSON structure: Group failures by category
            jq ". + {\"$category\": { \"$check_name\": {\"log\": \"$output_file\", \"summary\": $summary }}}" "$CHAT_SHARE_DIR/summary_results.json" > "$CHAT_SHARE_DIR/summary_results.json.tmp" && mv "$CHAT_SHARE_DIR/summary_results.json.tmp" "$CHAT_SHARE_DIR/summary_results.json"
        else
            rm "$output_file" 2>/dev/null || true  # Delete the log file if no failure
        fi
    }

    run_check "ESLint" "$diag_dir/eslint_results.txt" npx eslint "$TARGET_DIR" --ext .js,.ts,.tsx --no-interactive --ignore-pattern chat_share
    run_check "TypeScript Check" "$diag_dir/ts_check_results.txt" npx tsc --noEmit --skipLibCheck
    run_check "Prettier" "$diag_dir/prettier_results.txt" npx prettier --check . --ignore-path <(echo "chat_share")
    run_check "Jest" "$diag_dir/jest_results.txt" npx --no-install jest --passWithNoTests --detectOpenHandles --coveragePathIgnorePatterns "chat_share"
    run_check "Mocha" "$diag_dir/mocha_results.txt" npx --no-install mocha --dry-run --exclude "chat_share/**"
    run_check "Vitest" "$diag_dir/vitest_results.txt" npx --no-install vitest --dry-run --exclude "chat_share/**"
    run_check "Depcheck" "$diag_dir/depcheck_results.txt" npx --no-install depcheck --ignores "chat_share"
    run_check "TS-Prune" "$diag_dir/ts_prune_results.txt" npx ts-prune --ignore "chat_share"

    # Run HTML validation on all .html files (excluding node_modules and chat_share)
    find "$TARGET_DIR" -name "*.html" ! -path "*/node_modules/*" ! -path "*/chat_share/*" -print0 | while IFS= read -r -d '' html_file; do
        run_check "HTML Validation" "$diag_dir/html_results_$(basename "$html_file").txt" tidy -errors -q "$html_file"
    done
    
    # Run CSS validation on all .css files (excluding node_modules and chat_share)
    run_check "CSS Lint" "$diag_dir/css_results.txt" npx --yes stylelint $(find "$TARGET_DIR" -name "*.css" ! -path "*/node_modules/*" ! -path "*/chat_share/*")

    # Run Node.js app startup check
    run_check "Node.js App Startup" "$diag_dir/node_app_startup.txt" timeout 10 npm run dev

    log_message "Code checks completed."


}

# Function to create a baseline
do_baseline() {
    local baseline_commit="$(git_latest_commit)"
    local baseline_file="$CHAT_SHARE_DIR/baseline_${baseline_commit}.tar.gz"
    local baseline_dir="$CHAT_SHARE_DIR/project"

    log_message "WARNING: Creating baseline from the last commit ($baseline_commit), not the current files."
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

# Function to create diffs
do_diffs() {
    local current_commit="$(git_latest_commit)"
    local baseline_commit="$(get_stored_commit baseline)"
    local last_diff_commit="$(get_stored_commit last_diff)"

    if [[ -z "$last_diff_commit" ]]; then
        last_diff_commit="$baseline_commit"
    fi

    log_message "Generating diffs from baseline ($baseline_commit) and last diff ($last_diff_commit) to working directory..."

    local cumulative_diff_file="$CHAT_SHARE_DIR/cumulative_from_baseline.tar.gz"
    local incremental_diff_file="$CHAT_SHARE_DIR/incremental_from_${last_diff_commit}.tar.gz"

    git -C "$TARGET_DIR" diff "$baseline_commit" > "$CHAT_SHARE_DIR/repo_changes.patch"
    git -C "$TARGET_DIR" diff "$last_diff_commit" > "$CHAT_SHARE_DIR/incremental_changes.patch"
    git -C "$TARGET_DIR" diff --stat "$last_diff_commit" > "$CHAT_SHARE_DIR/repo_changes_stat.txt"

    do_diagnostics
    do_code_checks

    # Ensure required files exist before archiving
    if [[ ! -f "$CHAT_SHARE_DIR/repo_changes.patch" || ! -f "$CHAT_SHARE_DIR/summary_results.json" ]]; then
        log_message "ERROR: Required diff files are missing! Skipping diff creation."
        exit 1
    fi

    tar -czf "$cumulative_diff_file" -C "$CHAT_SHARE_DIR" \
        repo_changes.patch repo_changes_stat.txt summary_results.json info_for_chat analysis_instructions.txt
    log_message "Cumulative diff saved: $cumulative_diff_file"

    tar -czf "$incremental_diff_file" -C "$CHAT_SHARE_DIR" \
        incremental_changes.patch repo_changes_stat.txt summary_results.json info_for_chat analysis_instructions.txt
    log_message "Incremental diff saved: $incremental_diff_file"

    store_commit "last_diff" "$current_commit"
}


generate_instruction_file() {
    local instruction_file="$CHAT_SHARE_DIR/analysis_instructions.txt"

    cat > "$instruction_file" <<EOL
Helper Instructions for File Analysis

1. File Structure & Expected Content

   Baseline Archive Contents:
   - tracking_info.txt -> Metadata
   - project/ccs.sh -> Main script (may change)
   - info_for_chat/ -> Directory containing test results:
       - mocha_results.txt
       - depcheck_results.txt
       - vitest_results.txt
       - eslint_results.txt
       - jest_results.txt
       - ts_prune_results.txt
       - ts_check_results.txt

   Cumulative Archive Contents:
   - repo_changes.patch -> The actual code changes
   - repo_changes_stat.txt -> Summary of file modifications
   - summary_results.json -> Test & check results (structured JSON format)

2. Priority Files to Analyze
   - summary_results.json (contains all test/check failures)
   - repo_changes_stat.txt (high-level summary of changed files)
   - repo_changes.patch (actual code modifications)

3. Skipped or Low-Priority Files
   - tracking_info.txt (only metadata)
   - system_info.txt (only needed if debugging system dependencies)

4. Parsing Guidelines (Expected Formats & Keywords)

   summary_results.json:
   - Only process failed tests (ignore passed tests)
   - Each entry follows:
     {
       "Test Name": {
         "log": "<log file path>",
         "summary": "<brief error description>"
       }
     }

   repo_changes_stat.txt:
   - Follows "file | X insertions(+), Y deletions(-)" format
   - Extract filenames and number of changes

   repo_changes.patch:
   - Standard git diff format
   - Focus on function changes (avoid whitespace-only modifications)

5. Expected Failure Patterns & Common Fixes

   ESLint:
   - "Invalid option '--interactive'" → Outdated ESLint CLI command
   - "Unexpected token" → Likely syntax issue in modified files

   Jest/Mocha/Vitest:
   - "npx canceled due to missing packages" → npm install required
   - "Cannot find module" → Check package.json dependencies

   TS-Prune:
   - "File not found: tsconfig.json" → Ensure correct tsconfig.json path

6. Processing Order (Optimization Strategy)
   - Load summary_results.json (extract failures first)
   - Parse repo_changes_stat.txt (check what files changed)
   - Analyze repo_changes.patch (only if function logic changed)
   - Skip system_info.txt unless dependency errors appear

EOL

    log_message "Generated analysis instructions: $instruction_file"
}




if [[ ! -d "$CHAT_SHARE_DIR" ]]; then
    log_message "No chat_share directory found. Creating a new baseline..."
    do_baseline
    generate_instruction_file
    exit 0
fi

baseline_file=$(find "$CHAT_SHARE_DIR" -maxdepth 1 -name "baseline_*.tar.gz" | head -n 1)

if [[ -z "$baseline_file" ]]; then
    log_message "No baseline found in chat_share directory. Creating a new baseline..."
    do_baseline
    generate_instruction_file
    exit 0
fi



do_diffs
generate_instruction_file