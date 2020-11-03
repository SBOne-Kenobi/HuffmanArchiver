#include "auto_test.h"

int Test::totalNum = 0, Test::failedNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
    Test::totalNum++;
    if (expr)
        return;
    printf("TEST %s FAILED\nFILE: %s\nLINE: %zu\n", func, filename, lineNum);
    Test::failedNum++;
}

void Test::showFinalResult() {
    printf("\n\n%d TESTS RAN\n%d TESTS FAILED\n", Test::totalNum, Test::failedNum);
}