#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "waitgroup.h"

#define FILE_BUFFER_SIZE 1024
#define VIRUS_LOCATION_START 500
#define VIRUS_LOCATION_END 700
#define VIRUS_LENGTH VIRUS_LOCATION_END - VIRUS_LOCATION_START
#define VIRUS_CONTENT "VIRUS"
#define VIRUS_CONTENT_LENGTH 5
Waitgroup* wg;
bool found = false;

bool findVirus(char* name) {
    int file_descriptor = -1;

    file_descriptor = open(name, O_RDONLY);
    if (file_descriptor < 0 ) {
        char* msg = calloc(200, sizeof(char));
        sprintf(msg,"Error opening file %s", name);
        perror(msg);
        exit(7);
    }
    //position at 500
    int offset_position = lseek(file_descriptor, 500, SEEK_SET);

    if (offset_position < 0) {
        //can't find position 500
        return false;
    }
    char* file = calloc(VIRUS_LENGTH, sizeof(char));
    int bytes_read = 0;
    bytes_read = read(file_descriptor, file, VIRUS_LENGTH);
    //if error comoqera
    close(file_descriptor);
    char* virus_location = (char*) memmem(file, VIRUS_LENGTH, VIRUS_CONTENT, VIRUS_CONTENT_LENGTH);
    if (virus_location != NULL) {
        return true;
    }
    return false;
}

void *findAndPrint(void* argName) {
    char* name = (char*) argName;
    if (findVirus(name)) {
        puts(name);
        found = true;
    }
    done_waitgroup(wg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "At least one file expected: '%s filename'", argv[0]);
        return 3;
    }
    wg = create_waitgroup();
    if (wg == NULL){
        perror("Can't create mutex");
        return 4;
    }
    pthread_attr_t attr;
    int rc;
    rc = pthread_attr_init(&attr);
    rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    for (int i=1; i < argc; i++) {
        add_waitgroup(wg, 1);
        pthread_t _;
        int err = pthread_create(&_, &attr, &findAndPrint, (void*)argv[i]);
        if (err != 0) {
            fprintf(stderr, "can't create thread :[%s]", strerror(err));
        }
    }
    wait_waitgroup(wg);
    if (found) {
        return 0;
    } else {
        fputs("No virus found!", stderr);
        return 1;
    }

}
