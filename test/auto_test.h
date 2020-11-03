#ifndef AUTO_TEST_H
#define AUTO_TEST_H

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__);
#include <cstdio>

class Test {
protected:
    static int failedNum;
    static int totalNum;

    static void check(bool expr, const char *func, const char  *filename, size_t lineNum);

public:
    static void showFinalResult();
    virtual void checkAll() = 0;
};

#endif //AUTO_TEST_H