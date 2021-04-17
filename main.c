
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	parse_line(char *linha, int argc, char **argv, char **envp)
{
	char	**args;
	int		i;
	pid_t	pid;

	args = ft_split(linha, ' ');

	i = 0;
	while (args[i])
	{
		if (i == 0)
		{
			pid = fork();
			wait(NULL);
			if (pid == 0)
				execve(args[i], argv, envp);
		}
		free(args[i]);
		i++;
	}
	free(args);
}

int	gnl(int argc, char **argv, char **envp)
{
	char *linha;
	int retorno;

	get_next_line(0, &linha);
	parse_line(linha, argc, argv, envp);
	if (ft_strncmp(linha, "exit", ft_strlen("exit")) == 0)
	{
		free(linha);
		return (1);
	}
	free(linha);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	while (1)
	{
		ft_putstr_fd("minishell $ ", 1);
		if (gnl(argc, argv, envp) == 1)
			break;
	}
	return (0);
}
