
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

char	*command_exist(char *cmd, char **envp)
{
	struct stat	temp;
	int			i;
	char		**paths;
	char		*con;
	char		*temp_con;
	int			flag;
	char		*saida;

	saida = NULL;
	i = 0;
	paths = NULL;
	flag = 0;
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (saida);
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
			paths = ft_split((envp[i] + 5), ':');
		i++;
	}
	i = 0;
	while (paths[i] != 0)
	{
		temp_con = ft_strjoin(paths[i], "/");
		con = ft_strjoin(temp_con, cmd);
		free(temp_con);
		if (stat(con, &temp) == -1 && flag == 0)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			saida = ft_strdup(con);
		}
		free(con);
		free(paths[i]);
		i++;
	}
	free(paths);
	if (flag == 0)
		printf("\033[0mcomando \033[22;33m'%s'\033[0m nao encontrado\n", cmd);
	return (saida);
}

int	parse_line(char *linha/*, int argc,  char **argv*/, char **envp)
{
	char	**args;
	int		i;
	pid_t	pid;
	char	*cmd;

	args = ft_split(linha, ' ');
	if (args[0] != NULL)
	{
		cmd = command_exist(args[0], envp);
		if (cmd != NULL)
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			if (pid == 0)
				execve(cmd, args, envp);
			free(cmd);
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
	ft_putstr_fd("\033[0m", 1);
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
		ft_putstr_fd("\033[22;32mminishell $ \033[22;33m", 1);
		if (gnl(/*argc, argv, */envp) == 1)
			break;
	}
	ft_putstr_fd("\033[0m", 1);
	return (0);
}
