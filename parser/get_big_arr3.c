#include "../includes/minishell.h"

int	get_num_fckstr2(const int *real, int *k, char **com, int *flag)
{
	if (*k == 0 && real[0] != 1)
		(*k)++;
	if (real[*k] == 1 && ft_strchr("><", com[*k][0]))
	{
		(*k) += 2;
		return (2);
	}
	else
	{
		if (real[*k] == 1)
			(*k)++;
		*flag = 1;
	}
	return (0);
}

int	get_num_fckstr(const int *real, int *k, char **com, int *flag)
{
	int	i;

	if (*flag == 0)
		if (get_num_fckstr2(real, k, com, flag) == 2)
			return (2);
	i = 0;
	while (com[*k])
	{
		if (real[*k] == 1)
		{
			(*k)++;
			return (i);
		}
		i++;
		(*k)++;
	}
	return (i);
}
