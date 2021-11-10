#include "main.h"

/**
 *main - executes commands types by user
 *
 *Return: 0 on success
 */

int main(void)
{
	char *input;
	char **arguments = {NULL};
	char *abs_pathname;
	int status;

	while (1)
	{
		printf("#simpleShell$ ");
		input = _getline();
		if (!input)
			exit(EXIT_SUCCESS);
		if (strcmp(input, "\n") == 0)
			continue;
		if (execute_builtin(input) == 0)
			continue;
		else
		{
			arguments = split_string(input, " ");
			if (!arguments)
			{
				fprintf(stderr, "Failed to allocate memory\n");
				continue;
			}
			abs_pathname = get_abs_pathname(arguments[0]);
			if (!abs_pathname)
			{
				perror("Error: ");
				continue;
			}
			else
			{
				arguments[0] = abs_pathname;
				status = create_process(arguments);
				if (status == -1)
					continue;
			}
		}
		free(input);
		free(arguments);
	}
	_exit(EXIT_SUCCESS);
}