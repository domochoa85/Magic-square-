#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int c=0;
int counter=0;
pthread_mutex_t lock;


void* trythis(void* arg)
{
        unsigned long i = 0;
        pthread_mutex_lock(&lock);
        c+= 1;
        printf("\n Job %d has started\n", c);

        for (i = 0; i < 100000; i++)
                counter++       ;
        printf("\n Job %d has finished\n", c);
        pthread_mutex_unlock(&lock);

        return NULL;
}

int main(void)
{
        int i = 0;
        int error;

        if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }


        while (i < 2) {
                error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
                if (error != 0)
                        printf("\nThread can't be created : [%s]", strerror(error));
                i++;
        }

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
        pthread_mutex_destroy(&lock);

        printf("%i, %i\n", c, counter);



        return 0;
}

