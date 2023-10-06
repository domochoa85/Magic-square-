#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    const int SIZE = 4096;
    const char *name = "OS";

    int fd;
    char *ptr;

    // Open the shared memory object
    fd = shm_open(name, O_RDONLY, 0666);
    if (fd == -1) 
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    // Memory map the shared memory object
    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) 
    {
        perror("mmap");
        return EXIT_FAILURE;
    }

    // Read and print the contents of the shared memory
    printf("Message: %s\n", ptr);

    // Close the shared memory object
    close(fd);

    // Unlink the shared memory object (optional)
    // shm_unlink(name);
    
    // run the producer first, then run consumer multiple time, record what you see. Why?
    // then comment out the above unlink statement, recompile, and run multiple time again. What do you see? Record. Why?
    

    return 0;
}
