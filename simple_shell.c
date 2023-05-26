#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * Displays the prompt symbol to indicate the shell is ready for user input.
 */
void display_prompt(void)
{
    printf("> ");
    fflush(stdout);
}

int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\n");
            break;  /* End of file (Ctrl+D) condition */
        }

        command[strcspn(command, "\n")] = '\0';  /* Remove the trailing newline character */

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            if (execlp(command, command, NULL) == -1)
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
