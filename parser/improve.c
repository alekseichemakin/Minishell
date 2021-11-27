#include "../includes/minishell.h"

char	***get_new_command(t_struct *strc, char ***new_command, int i)
{
	int	t;
	int	k;
	int	n;

	t = -1;
	n = 0;
	while (strc->comand[++t])
	{
		if (t == 0 || t != i + 1)
		{
			new_command[t - n] = malloc((sizeof(char **) * ft_arrsize
						(strc->comand[t])) + 1);
			k = -1;
			while (strc->comand[t][++k])
				new_command[t - n][k] = ft_strdup(strc->comand[t][k]);
			new_command[t - n][k] = NULL;
		}
		else
			n++;
	}
	new_command[t - n] = NULL;
	return (new_command);
}

int	*get_new_flags(t_struct *strc, int k)
{
	int	*new_flags;
	int	i;
	int	n;
	int	*arr;

	arr = NULL;
	new_flags = NULL;
	new_flags = init_real(new_flags);
	arr = init_real(arr);
	n = 0;
	i = -1;
	while (strc->comand[++i])
	{
		if (i != k)
			new_flags[i - n] = strc->flags[i];
		else
			arr[i - n++] = 1;
	}
	free(strc->flags);
	strc->flags = new_flags;
	return (arr);
}

void	rebuild2(int flag, t_struct *strc, char ***new_command, int i)
{
	int	n;

	if (flag == 3)
	{
		free(strc->flags_out);
		strc->flags_out = get_new_flags(strc, i);
	}
	else if (flag == 4)
	{
		free(strc->flags_in);
		strc->flags_in = get_new_flags(strc, i);
	}
	if (strc->comand)
	{
		n = -1;
		while (strc->comand[++n])
			free_arr(strc->comand[n]);
		free(strc->comand);
		strc->comand = new_command;
	}
}

void	rebuild(t_struct *strc, int flag, int i)
{
	char	***new_command;
	int		n;

	n = 0;
	while (strc->comand[n])
		n++;
	new_command = malloc((sizeof(char ***) * n));
	new_command = get_new_command(strc, new_command, i);
	rebuild2(flag, strc, new_command, i);
}

t_struct	improve_massive(t_struct strc)
{
	int	i;

	strc.flags_in = init_real(strc.flags_in);
	strc.flags_out = init_real(strc.flags_out);
	i = -1;
	while (strc.comand && strc.comand[++i] && strc.err == 0)
	{
		if (create_files(&strc, i))
			i = -1;
		else if (get_input(&strc, i))
			i = -1;
	}
	return (strc);
}
