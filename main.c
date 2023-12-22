#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int* string_to_array(char* string, int* length) {
    // Conta il numero di numeri nella stringa
    char* tmp = string;
    int count = 0;
    while(*tmp) {
        if (*tmp == ',') {
            count++;
        }
        tmp++;
    }

    // Alloca memoria per l'array
    int* array = malloc(sizeof(int) * (count + 1));

    // Divide la stringa e converte i segmenti in numeri interi
    char* token = strtok(string, ",");
    int i = 0;
    while(token != NULL) {
        array[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    *length = count + 1;
    return array;
}

void print_array(int* array, int length){
    int i;
    for(i = 0; i < length; i++){
        printf("%d", array[i]);
    }
    printf("\n");
}

void *thread_function(void *arg){
    int num = *(int *) arg;

    // thread sleeps for num seconds
    sleep(num);

    // print thread number
    printf("Next number: %d\n", num);

    return NULL;
}

int main(int argc, char *argv[]){
    // get arguments from command line
    int num_threads = atoi(argv[1]);
    int *array = string_to_array(argv[2], &num_threads);

    // print arguments
    printf("Number of threads: %d\n", num_threads);
    printf("Array: ");
    print_array(array, num_threads);

    // create threads
    pthread_t threads[num_threads];

    // run threads
    int i;
    for(i = 0; i < num_threads; i++){
        pthread_create(&threads[i], NULL, thread_function, &array[i]);
    }

    // wait for threads to finish
    for(i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}

