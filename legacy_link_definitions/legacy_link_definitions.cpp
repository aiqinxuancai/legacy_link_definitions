#include "pch.h"
#include "framework.h"
#include <time.h>

extern "C" {

#pragma warning(push)
#pragma warning(disable : 4996)

long* __cdecl __p__timezone(void)
{
    _tzset();
    return __timezone();
}

int* __cdecl __p__daylight(void)
{
    _tzset();
    return __daylight();
}

long* __cdecl __p__dstbias(void)
{
    _tzset();
    return __dstbias();
}

char** __cdecl __p__tzname(void)
{
    _tzset();
    return __tzname();
}

#pragma warning(pop)

}
