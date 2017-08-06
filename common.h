#include <stdio.h>

#define ERROR_EXIT(...)                                                 \
    do{                                                                 \
        fprintf(stderr, "[E]:%s:%d ", __FILE__, __LINE__);              \
        fprintf(stderr, __VA_ARGS__);                                   \
        fprintf(stderr, ":Exiting... \n");                              \
        std::raise(SIGTERM);                                                 \
    } while(0)

#define ERROR_LOG(...)                                                  \
    do{                                                                 \
        fprintf(stderr, "[E]:%s:%d ", __FILE__, __LINE__);              \
        fprintf(stderr, __VA_ARGS__);                                   \
        fprintf(stderr, "\n");                                          \
    } while(0)

#define INFO_LOG(...)                                                   \
    do{                                                                 \
        fprintf(stderr, "[I]: ");                                       \
        fprintf(stderr, __VA__ARGS__);                                  \
        fprintf(stderr, "\n");                                          \
    } while(0)