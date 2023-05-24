#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * read_line - Reads a line of input from stdin.
 * @buffer: The buffer to store the input line.
 */
void read_line(char *buffer)
{
	fgets(buffer, BUFFER_SIZE, stdin);
}

/**
 * execute_command - Executes the given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execlp(command, command, NULL) == -1)
		{
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Fork error */
		perror("Fork error");
	}
	else
	{
		/* Parent process */
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("simple_shell$ ");
		read_line(buffer);

		/* Check for end of file */
		if (feof(stdin))
		{
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';  /* Remove trailing newline character */

		execute_command(buffer);
	}

	return 0;
}
