#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int run_test(const char *cmd, int expected_exit) {
    printf("Running: %s\n", cmd);
    int status = system(cmd);
    int exit_code = WEXITSTATUS(status);
    if (exit_code == expected_exit) {
        printf("  [PASS] Got expected exit code %d\n", exit_code);
        return 0;
    } else {
        printf("  [FAIL] Expected exit code %d, got %d\n", expected_exit, exit_code);
        return 1;
    }
}

int main() {
    int failures = 0;

    printf("Starting test suite...\n");

    // Test 1: Wrong argument count (too few)
    failures += run_test("./encode sheldon.bmp out.bmp > /dev/null 2>&1", 1);

    // Test 2: Input file doesn't exist
    failures += run_test("./encode non_existent.bmp out.bmp 'test' > /dev/null 2>&1", 1);

    // Test 3: Output file cannot be created (invalid path)
    failures += run_test("./encode sheldon.bmp /invalid/path/out.bmp 'test' > /dev/null 2>&1", 1);

    // Test 4: Success case - simple message
    failures += run_test("./encode sheldon.bmp test_out.bmp 'hello' > /dev/null 2>&1", 0);

    // Test 5: Success case - empty message
    failures += run_test("./encode sheldon.bmp test_out_empty.bmp '' > /dev/null 2>&1", 0);

    // Test 6: Message that is somewhat long
    failures += run_test("./encode sheldon.bmp test_out_long.bmp 'Testing with a longer message to cover more bits and loop iterations.' > /dev/null 2>&1", 0);

    if (failures == 0) {
        printf("\nAll tests passed!\n");
        return 0;
    } else {
        printf("\n%d tests failed.\n", failures);
        return 1;
    }
}
