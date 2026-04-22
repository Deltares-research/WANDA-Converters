// required because Windows.h is included via our header file.  Otherwise std::max doesn't work
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/f5915ad0-a9d1-49f3-8643-ffd623f72b93/error-c2039-max-is-not-a-member-of-std
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
