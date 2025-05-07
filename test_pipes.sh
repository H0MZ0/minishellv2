#!/bin/bash

MINISHELL=./minishell     # Adjust this if needed
TEST_DIR=tests_output
mkdir -p $TEST_DIR

test_case() {
    local name="$1"
    local command="$2"

    echo "$command" | bash > "$TEST_DIR/bash_$name.out" 2> "$TEST_DIR/bash_$name.err"
    echo "$command" | $MINISHELL > "$TEST_DIR/minishell_$name.out" 2> "$TEST_DIR/minishell_$name.err"

    echo -e "\nTest: $name"
    if diff "$TEST_DIR/bash_$name.out" "$TEST_DIR/minishell_$name.out" > /dev/null && \
       diff "$TEST_DIR/bash_$name.err" "$TEST_DIR/minishell_$name.err" > /dev/null; then
        echo "✅ PASSED"
    else
        echo "❌ FAILED"
        echo "--- Bash Output ---"
        cat "$TEST_DIR/bash_$name.out"
        echo "--- Minishell Output ---"
        cat "$TEST_DIR/minishell_$name.out"
        echo "--- Bash Error ---"
        cat "$TEST_DIR/bash_$name.err"
        echo "--- Minishell Error ---"
        cat "$TEST_DIR/minishell_$name.err"
    fi
}

test_case "basic_pipe" "echo hello | cat"
test_case "multi_pipe" "echo one two three | tr ' ' '\n' | wc -l"
test_case "builtin_to_external" "pwd | cat"
test_case "invalid_cmd_in_pipe" "echo test | notacommand | wc"
test_case "pipe_with_redirection" "echo line1 | tee pipe_test_out.txt"
test_case "pipe_with_file_input" "echo '42\nhello\n42' > infile.txt && cat infile.txt | grep 42 | wc -l"

rm -f infile.txt pipe_test_out.txt

