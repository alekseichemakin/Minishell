#include "../includes/minishell.h"

void	export_arg_write2(t_struct *strc, char *comand, char *str, int fl)
{
	int	i;

	i = 0;
	while (strc->envs[i])
	{
		if (!(ft_strncmp(strc->envs[i], str, ft_strlen(str))) && fl == 1)
		{
			free(strc->envs[i]);
			strc->envs[i] = ft_strdup(comand);
			return ;
		}
		i++;
	}
	strc->envs = rewrite(strc->envs, i, 1);
	strc->envs[i] = ft_strdup(comand);
	strc->envs[i + 1] = NULL;
}

void	export_arg_write(t_struct *strc, char *comand)
{
	int		i;
	char	*str;
	int		fl;

	i = 0;
	fl = 0;
	while (comand[i] != '=' && comand[i])
		i++;
	if (comand[i] == '=')
		fl = 1;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		error(strc, "malloc", "could not allocate memory", 1);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = comand[i];
		i--;
	}
	export_arg_write2(strc, comand, str, fl);
	free(str);
}

void	export_arg_func(t_struct *strc, char **comand)
{
	int	i;

	i = 1;
	while (comand[i])
	{
		if (ft_isalpha(comand[i][0]) || comand[i][0] == '_')
			export_arg_write(strc, comand[i]);
		else
		{
			write(1, "minishit: export: `", 15);
			ft_putstr_fd(comand[i], 1);
			write(1, "\": not a valid identifier", 25);
			write(1, "\n", 1);
		}
		i++;
	}
}
