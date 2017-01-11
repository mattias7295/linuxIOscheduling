#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

// Command to create many files
// for i in {10..110}; do dd if=/dev/urandom bs=1000 count=1 of=sfile$i; done


#define MEGABYTE 1048576
#define KILOBYTE 1024

#define bool int
#define true 1
#define false 0

bool stop = false;

struct data {
    char filename[30];
    int filesize;
};

double get_time() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec + now.tv_usec / 1000000.0;
}

off_t file_size(const char *file) {
    struct stat st;

    if (stat(file, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

void *read(void *id) {
    char *file = (char *) id;
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror(file);
    } else {
        while (!stop) {
            if (fgetc(fp) == EOF) {
                fseek(fp, 0, SEEK_SET); // beginning of file
            }
        }
        fclose(fp);
    }

    return 0;
}

void *write(void *id) {
    struct data *d = (struct data *) id;
    FILE *fp = fopen(d->filename, "w+");
    if (!fp) {
        perror(d->filename);
    } else {
        int size = MEGABYTE*d->filesize;
        for (int i = 0; i < size; i++) {
            if (fputc(1, fp) == EOF) {
                fclose(fp);
                return (void*) -1;
            }
        }
        fclose(fp);
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s size_in_MB\n", argv[0]);
        return 0;
    }


    double end_time, start_time, total_time;
    int num_threads = 110;
    int size;

    sscanf(argv[1], "%d", &size);
    pthread_t threads[num_threads];

    start_time = get_time();
    for (int i = 0; i < 10; i++) {
        struct data *d = malloc(sizeof(struct data));
        //char *file = malloc(sizeof(char) * 30);
        sprintf(d->filename, "files/file%d", i);
        d->filesize = size;
        pthread_create(&threads[i], NULL, write, (void *) d);
    }

    for (int i = 10; i < num_threads; i++) {
        char *file = malloc(sizeof(char) * 30);
        sprintf(file, "files/sfile%d", i);
        pthread_create(&threads[i], NULL, read, (void *) file);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    end_time = get_time();
    stop = true;

    for (int i = 10; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    total_time = end_time - start_time;

    printf("Result: with 10 threads writing %dMB total and 100 threads reading 1KB files\n", size);
    printf("Took %.2f seconds to read %d MB. Speed %.2f MB/s.\n", total_time, size*10, (size*10.0)/total_time);

    return 0;
}
