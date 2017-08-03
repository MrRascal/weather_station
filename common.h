#include <stdio.h>
#define ERROR_LOG(...)                                                  \
    do{                                                                  \
        fprintf(stderr, "[E]:%s:%d ", __FILE__, __LINE__);                                         \
        fprintf(stderr, __VA_ARGS__);                                    \
        fprintf(stderr, "\n");                                           \
    } while(0)