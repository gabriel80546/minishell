
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	parse_line(char *linha)
{
	char	**args;
	char	*nbr;
	int		i;

	args = ft_split(linha, ' ');

	i = 0;
	while (args[i])
	{
		nbr = ft_itoa(i);
		ft_putstr_fd("arg[", 1);
		ft_putstr_fd(nbr, 1);
		ft_putstr_fd("] = '", 1);
		ft_putstr_fd(args[i], 1);
		ft_putstr_fd("'\n", 1);
		free(nbr);
		free(args[i]);
		i++;
	}
	free(args);
}

int	gnl(void)
{
	char *linha;
	int retorno;

	get_next_line(0, &linha);
	parse_line(linha);
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
		if (gnl() == 1)
			break;
	}
	return (0);
}
