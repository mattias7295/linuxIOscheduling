#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
    double end_time, start_time, total_time;

    const char *file = "/home/c12mkn/Downloads/CLion-2016.2.3.tar.gz";
    off_t size = file_size(file);

    FILE *fp = fopen(file, "rb");
    if (!fp) {
        perror(file);
        exit(1);
    }
    start_time = get_time();

    while (fgetc(fp) != EOF) {

    }

    fclose(fp);
    end_time = get_time();

    total_time = end_time - start_time;

    printf("Took %.2f seconds to read %.2f MiB. Speed %.2f MiB/s.\n", total_time, size/1000000.0, (size/1000000)/total_time);

    return 0;
}
