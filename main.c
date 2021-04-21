
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
#ifndef DEB
# define DEB __FILE__, __func__, __LINE__
#endif

int		say(const char *format, char *file, const char *func, int line, ...)
{
	va_list		args;
	int			saida;
	static int	counter = 0;

	printf("%05d:%s(%s:%d): ", counter, file, func, line);
	va_start(args, line);
	saida = vprintf(format, args);
	va_end(args);
	counter++;
	return (saida);
}

int	command_exist(char *cmd)
{
	struct stat temp;
	if (stat(cmd, &temp) == -1)
	{
		if (ft_strncmp(cmd, "exit", ft_strlen("exit")) != 0)
			printf("comando '%s' nao encontrado\n", cmd);
		return (0);
	}
	else
		return (1);
}

int	parse_line(char *linha/*, int argc,  char **argv*/, char **envp)
{
	char	**args;
	int		i;
	pid_t	pid;

	args = ft_split(linha, ' ');
	if (args[0] != NULL)
	{
		if (command_exist(args[0]) == 1)
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			if (pid == 0)
				execve(args[0], args, envp);
		}
	}
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}

int	gnl(/*int argc, char **argv, */char **envp)
{
	char *linha;

	get_next_line(0, &linha);
	parse_line(linha/*, argc, argv*/, envp);
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
	argc = argc + 0;
	argv = argv + 0;
	while (1)
	{
		ft_putstr_fd("minishell $ ", 1);
		if (gnl(/*argc, argv, */envp) == 1)
			break;
	}
	return (0);
}
