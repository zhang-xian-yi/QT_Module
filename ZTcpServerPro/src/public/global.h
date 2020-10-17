#ifndef GLOBAL_H
#define GLOBAL_H

#define DEBUG_TCP_TRACE
#define LOG_INFO

#ifdef DEBUG_TCP_TRACE
#include <stdio.h>
#define DEBUG_TCP(format,...) printf("[File: " __FILE__ ", Line: %d]:" format "\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_TCP(format,...)
#endif

#ifdef LOG_INFO
#include <stdio.h>
#define LOG_TCP(format,...) printf("[File: " __FILE__ ", Line: %d]:" format "\n", __LINE__, ##__VA_ARGS__)
#else
#define LOG_TCP(format,...)
#endif





#endif // GLOBAL_H
