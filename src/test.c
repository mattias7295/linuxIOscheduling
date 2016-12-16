#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

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

void *work(void *id) {
    char *file = (char *) id;
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        perror(file);
    } else {
        while (fgetc(fp) != EOF) {

        }

        fclose(fp);
    }

    return (void *)1;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: %s filename num_threads\n", argv[0]);
        exit(1);
    }
    double end_time, start_time, total_time;
    int num_threads;

    const char *file = argv[1];
    sscanf(argv[2], "%d", &num_threads);
    pthread_t threads[num_threads];

    off_t size = file_size(file);
    start_time = get_time();
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, work, (void *) file);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    end_time = get_time();

    total_time = end_time - start_time;

    printf("Result: with %d threads reading %s\n", num_threads, file);
    printf("Took %.2f seconds to read %.2f MiB. Speed %.2f MiB/s.\n", total_time, size/1000000.0, (size/1000000)/total_time);

    return 0;
}
