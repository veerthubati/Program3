#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#define MAX 100

int num_aleatorio() {
    int num = random() % MAX;
    return num;
}

void generateMatrix(int * a, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        a[i] = num_aleatorio();
    }
}

void primeMatrix(int * a, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    long int number_tosses, number_in_circle;
    int thread_count, i, j, n, count;
    srandom(0);
    thread_count = strtol(argv[1], NULL, 10);
    n = strtol(argv[2], NULL, 10);
    int *a = malloc(n * sizeof(int));
    primeMatrix(a, n);
    int *temp = malloc(n * sizeof(int));
    double start = omp_get_wtime();
#pragma omp parallel for num_threads(thread_count) \
   default(none) private(i, j, count) shared(a, n, temp, thread_count)
    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }
    memcpy(a, temp, n * sizeof(int));
    double finish = omp_get_wtime();
    free(temp);
    printf("Estimated time %e seconds\n", finish - start);
    primeMatrix(a, n);
    return 0;
}