#ifndef WAITGROUP_H
#define WAITGROUP_H

#include <pthread.h>

typedef struct {
    int waitGroupSize;
    pthread_mutex_t mutex;
} Waitgroup;

Waitgroup* create_waitgroup();
void add_waitgroup(Waitgroup* wg, int size);
void done_waitgroup(Waitgroup* wg);
void wait_waitgroup(Waitgroup* wg);

#endif //#ifndef WAITGROUP_H
