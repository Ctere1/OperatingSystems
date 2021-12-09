#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

/*
* C program that reverses the data received from the user. Parent process will receive the
  relevant number from the user and send it to the child process, and child process will reverse
  the incoming number. Parent operation will write the calculated number and the number from the
  child operation to the screen. It uses pipes for data exchange.

* Example Input: 12365
  Output: 12365
          56321
*/

int child_proccess(int file_descriptor[], int file_descriptor2[])
{
    close(file_descriptor[1]);
    char y[100];
    char reverse[100];
    read(file_descriptor[0], y, 100);

    close(file_descriptor[0]);
    close(file_descriptor2[0]);

    for (int i = 0; i < strlen(y); i++)
    {
        reverse[i] = y[strlen(y) - i - 1];
    }

    write(file_descriptor2[1], reverse, strlen(reverse) + 1);
    close(file_descriptor2[1]);
    return EXIT_SUCCESS;
}

int main()
{
    int file_descriptor[2];
    int file_descriptor2[2];
    if (pipe(file_descriptor) == -1 || pipe(file_descriptor2) == -1)
    {
        printf("Pipe Create Error");
        return EXIT_FAILURE;
    }

    pid_t id = fork();
    if (id < 0)
    {
        /* The fork failed. */
        printf("Fork failed.\n");
        return EXIT_FAILURE;
    }
    else if (id > 0)
    {
        /* Parent Proccess */
        close(file_descriptor[0]);

        char result[100];
        char input[100];

        scanf("%s", input);
        printf("%s\n", input);
        write(file_descriptor[1], input, strlen(input) + 1);

        close(file_descriptor[1]);

        wait(NULL);

        close(file_descriptor2[1]);

        read(file_descriptor2[0], result, 100);
        printf("%s\n", result);
        close(file_descriptor2[0]);

        return EXIT_SUCCESS;
    }
    else
    {
        /* Child Proccess */
        if (child_proccess(file_descriptor, file_descriptor2))
        {
            printf("Child Proccess Error");
        }
        else
        {
            // Success
        }
    }
    return EXIT_SUCCESS;
}