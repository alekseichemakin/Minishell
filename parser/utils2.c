#include "../includes/minishell.h"

char	*is_question(int *i, t_struct strc)
{
	char	*new;

	(*i)++;
	new = ft_itoa(strc.ret_val);
	return (new);
}

int	ft_arrsize(char **arr)
{
	int	i;

	if (!(arr))
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_strc(t_struct strc)
{
	int	i;

	if (strc.comand)
	{
		i = -1;
		while (strc.comand[++i])
			free_arr(strc.comand[i]);
		free(strc.comand);
		strc.comand = NULL;
	}
	if (strc.flags)
		free(strc.flags);
	if (strc.flags_in)
		free(strc.flags_in);
	if (strc.flags_out)
		free(strc.flags_out);
}

char	**rewrite(char **comand, int x, int k)
{
	char	**new;
	int		i;

	new = malloc(sizeof (char *) * (x + k + 1));
	if (comand)
	{
		i = -1;
		while (comand[++i])
		{
			new[i] = ft_strdup(comand[i]);
		}
		free_arr(comand);
	}
	return (new);
}
