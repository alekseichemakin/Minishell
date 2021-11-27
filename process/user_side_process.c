#include "../includes/minishell.h"

char	*path_rerite(char *comand, char *path_args)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 1;
	str = malloc(sizeof(char) * ft_strlen(path_args) + ft_strlen(comand));
	while (path_args[i])
	{
		str[i] = path_args[i];
		i++;
	}
	while (comand[j])
		str[i++] = comand[j++];
	str[i] = '\0';
	free(path_args);
	return (str);
}

int	user_side_proc(t_struct *strc, int str_num)
{
	char	*path_args;

	if (strc->comand[str_num][0][0] == '/')
		return (execve(strc->comand[str_num][0], strc->comand[str_num],
			strc->envs));
	else if (strc->comand[str_num][0][0] == '.')
	{
		path_args = env_variable_argument(strc, "PWD=");
		path_args = path_rerite(strc->comand[str_num][0], path_args);
		return (execve(path_args, strc->comand[str_num], strc->envs));
	}
	return (0);
}
