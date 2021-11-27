#include "../includes/minishell.h"

int	check_num(char *arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		if (ft_isdigit(arr[i]) == 0)
			return (1);
	return (0);
}

void	exit_func(char **arr)
{
	ft_putstr_fd("exit\n", 1);
	if (!arr[1])
		exit(0);
	else
	{
		if (check_num(arr[1]) == 1)
		{
			error(NULL, "exit", "numeric argument required", 1);
			exit(255);
		}
		else
			exit(ft_atoi(arr[1]));
	}
}
