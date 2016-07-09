#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "waitgroup.h"

Waitgroup* create_waitgroup(){
    Waitgroup* wg = (Waitgroup*) malloc(sizeof(Waitgroup));
    wg->waitGroupSize = 0;
    int ok = pthread_mutex_init(&(wg->mutex), NULL);
    if (ok != 0) {
        free(wg);
        return NULL;
    }
    return wg;
}

void add_waitgroup(Waitgroup* wg, int size) {
    if (wg == NULL) {
        return;
    }
    pthread_mutex_lock(&( wg->mutex ));
    wg->waitGroupSize += size;
    pthread_mutex_unlock(&( wg->mutex ));
}

void done_waitgroup(Waitgroup* wg) {
    if (wg == NULL) {
        return;
    }
    pthread_mutex_lock(&( wg->mutex ));
    wg->waitGroupSize--;
    pthread_mutex_unlock(&( wg->mutex ));
}

void wait_waitgroup(Waitgroup* wg) {
    if (wg == NULL) {
        return;
    }
    while(wg->waitGroupSize > 0) {
        usleep(100); //every 100 milisseconds check for the variable
    }
    pthread_mutex_destroy(&( wg->mutex ));
    free(wg);
}
