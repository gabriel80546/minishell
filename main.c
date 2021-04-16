
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	gnl(void)
{
	char *linha;
	int retorno;

	get_next_line(0, &linha);
	write(1, linha, strlen(linha));
	if (strlen(linha) > 0)
		write(1, "\n", 1);
	if (strcmp(linha, "exit") == 0)
	{
		free(linha);
		return (1);
	}
	free(linha);
	return (0);
}

int main(void)
{
	while (1)
	{
		write(1, "minishell $ ", strlen("minishell $ "));
		if (gnl() == 1)
			break;
	}
	return (0);
}
