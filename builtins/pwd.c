#include "../includes/minishell.h"

int	pwd_func(char **mass)
{
	char	*pwd;

	(void)mass;
	pwd = getcwd(NULL, 1024);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
	return (1);
}
