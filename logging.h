#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <stdio.h>

#define LOG(...) \
do { \
	fprintf(stdout, __VA_ARGS__); \
} while (0)

#endif
