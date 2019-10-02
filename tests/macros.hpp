#ifndef STREEGP_TEST_MACROS_HPP_
#define STREEGP_TEST_MACROS_HPP_

#include <stree/stree.hpp>

// Define test function that does nothing
#define DEFUN_EMPTY(func)                                               \
    static stree::Value func(const stree::Arguments& args, stree::DataPtr) { \
        return stree::Value{};                                          \
    }

#endif
