
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	main(void)
{
	int fd;
	char *linha;
	int i;
	int retorno;
	char *file;

	i = 0;
	file = "run.sh";
	fd = open(file, O_RDONLY);
	retorno = 1;
	while (retorno == 1)
	{
		retorno = get_next_line(fd, &linha);
		if (retorno != 1)
			break;
		printf("%s(%s:%d): linha[%d] = '%s'(%ld); retorno = %i\n", __FILE__, __func__, __LINE__, i, linha, strlen(linha), retorno);
		free(linha);
		i++;
	}
	if (retorno != -1)
	{
		printf("%s(%s:%d): linha[%d] = '%s'(%ld); retorno = %i\n", __FILE__, __func__, __LINE__, i, linha, strlen(linha), retorno);
		free(linha);
	}
	else
		printf("%s(%s:%d): get_next_line(\"%s\") retornou -1\n", __FILE__, __func__, __LINE__, file);
	return (0);
}
