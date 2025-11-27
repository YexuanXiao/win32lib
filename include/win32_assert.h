#ifndef BIZWEN_WIN32_ASSERT_H
#define BIZWEN_WIN32_ASSERT_H

// This macro is used to test whether the program can be built without using <cassert>,
// as <cassert> may contain irrelevant declarations
#define TEST_ASSERT

#ifdef TEST_ASSERT
#define assert(expression) ((void)0)
#else
#include <cassert>
#endif
#endif
