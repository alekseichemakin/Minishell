#include "../includes/minishell.h"

int	env_func(t_struct *strc)
{
	int	i;

	i = 0;
	while (strc->envs[i])
	{
		if (ft_strchr(strc->envs[i], '='))
		{
			ft_putstr_fd(strc->envs[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	return (1);
}
