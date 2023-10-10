// legacy_link_definitions.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


    long compute_timezone_value() {
        long t = 0;
        _get_timezone(&t);
        return t;
    }

    long& timezone() {
        static long value = compute_timezone_value();
        return value;
    }


#ifdef __cplusplus
}
#endif