#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int c=0;
int counter=0;

void* trythis(void* arg)
{
        unsigned long i = 0;
        //c+= 1;
        c = c+1;

        printf("\n Job %d has started\n", c);

        for (i = 0; i < 100000; i++)
                counter++       ;
                //counter=counter + 1;    load [counter] AX; inc AX; store AX, [counter];
        printf("\n Job %d has finished\n", c);

        return NULL;
}

int main(void)
{
        int i = 0;
        int error;

        while (i < 2) {
                error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
                if (error != 0)
                        printf("\nThread can't be created : [%s]", strerror(error));
                i++;
        }

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

        printf("%i, %i\n", c, counter);

        return 0;
}

