#include "../includes/minishell.h"

int	bubble_sort2(char **buff, int i)
{
	char	*str;

	str = ft_strdup(buff[i]);
	free(buff[i]);
	buff[i] = ft_strdup(buff[i + 1]);
	free(buff[i + 1]);
	buff[i + 1] = ft_strdup(str);
	free(str);
	return (1);
}

void	bubble_sort(char **buff)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buff[i + 1])
	{
		while (buff[i][j] >= buff[i + 1][j])
		{
			if (buff[i][j] == buff[i + 1][j])
				j++;
			else
				flag += bubble_sort2(buff, i);
		}
		i++;
		if (flag == 1)
		{
			i = 0;
			flag = 0;
		}
		j = 0;
	}
}

char	**env_dup(t_struct *strc)
{
	char	**buff;
	int		i;

	i = 0;
	while (strc->envs[i])
		i++;
	buff = malloc((i + 1) * sizeof (char **));
	if (!(buff))
		return (NULL);
	i = 0;
	while (strc->envs[i])
	{
		buff[i] = ft_strdup(strc->envs[i]);
		i++;
	}
	buff[i] = NULL;
	bubble_sort(buff);
	return (buff);
}

void	export_func2(char	**buff, int i, int j)
{
	if (buff[i][j] && buff[i][j] == '=')
	{
		write(1, "=\"", 2);
		ft_putstr_fd((buff[i] + j + 1), 1);
		write(1, "\"", 1);
	}
}

int	export_func(t_struct *strc, char **comand)
{
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (comand[1])
	{
		export_arg_func(strc, comand);
		return (-1);
	}
	buff = env_dup(strc);
	while (buff[i])
	{
		write(1, "declare -x ", 11);
		while (buff[i][j] && buff[i][j] != '=')
			ft_putchar_fd(buff[i][j++], 1);
		export_func2(buff, i, j);
		write(1, "\n", 1);
		i++;
		j = 0;
	}
	free_arr(buff);
	return (1);
}
