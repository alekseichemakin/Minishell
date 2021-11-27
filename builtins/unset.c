#include "../includes/minishell.h"

int	check_unset_valid(char *comand)
{
	int	i;

	i = 0;
	while (comand[i])
	{
		if (ft_isalpha(comand[i]) || comand[i] == '_')
			i++;
		else
		{
			write(2, "minishit: export: `", 15);
			ft_putstr_fd(comand, 1);
			write(2, "\": not a valid identifier", 25);
			write(2, "\n", 1);
			return (0);
		}
	}
	return (1);
}

char	**delete_str(int num_str, t_struct *strc)
{
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (strc->envs[i])
		i++;
	buff = malloc((i) * sizeof (char **));
	i = 0;
	while (strc->envs[i])
	{
		if (i != num_str)
			buff[j++] = ft_strdup(strc->envs[i]);
		i++;
	}
	buff[j] = NULL;
	free_arr(strc->envs);
	return (buff);
}

void	check_str(t_struct *strc, char *comand)
{
	int		i;
	int		j;

	j = (int)ft_strlen(comand);
	i = 0;
	while (strc->envs[i])
	{
		if (!(ft_strncmp(strc->envs[i], comand, j))
			&& (strc->envs[i][j] == '\0' || strc->envs[i][j] == '='))
		{
			strc->envs = delete_str(i, strc);
			return ;
		}
		i++;
	}
}

int	unset_func(t_struct *strc, char **comand)
{
	int		i;

	i = 1;
	while (comand[i])
	{
		if (check_unset_valid(comand[i]))
			check_str(strc, comand[i]);
		else
			strc->ret_val = 1;
		i++;
	}
	return (1);
}
