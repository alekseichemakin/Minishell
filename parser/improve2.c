#include "../includes/minishell.h"

char	***ex_case2(t_struct *strc)
{
	int		i;
	char	***new;
	int		k;

	i = 0;
	while (strc->comand[i])
		i++;
	new = malloc(sizeof(char ***) * i);
	i = 0;
	while (strc->comand[++i])
	{
		new[i - 1] = malloc((sizeof(char **) * ft_arrsize(strc->comand[i]))
				+ 1);
		k = -1;
		while (strc->comand[i][++k])
		{
			new[i - 1][k] = ft_strdup(strc->comand[i][k]);
			strc->flags[i - 1] = strc->flags[i];
		}
		new[i - 1][k] = NULL;
	}
	new[i - 1] = NULL;
	return (new);
}

void	ex_case(t_struct *strc, int flag, int n)
{
	int		i;
	char	***new;

	i = 0;
	if (flag == 1)
		strc->flags_out[n] = 1;
	else if (flag == 0)
		strc->flags_in[n] = 1;
	while (strc->comand[i])
		i++;
	new = ex_case2(strc);
	i = -1;
	while (strc->comand[++i])
		free_arr(strc->comand[i]);
	free(strc->comand);
	strc->comand = new;
}

int	trunc_file(t_struct *strc, int k, int i)
{
	if (strc->redir_out != 0)
		close(strc->redir_out);
	if (strc->comand[i][0][0] == '>')
	{
		strc->redir_out = open(strc->comand[i][1], O_WRONLY | O_TRUNC
				| O_CREAT, 0777);
		ex_case(strc, 1, i);
		k = 2;
	}
	else
	{
		strc->redir_out = open(strc->comand[i + 1][0],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		k = 1;
	}
	return (k);
}

int	append_file(t_struct *strc, int k, int i)
{
	if (strc->redir_out != 0)
		close(strc->redir_out);
	if (strc->redir_out != 0)
		close(strc->redir_out);
	if (strc->comand[i][0][0] == '>')
	{
		strc->redir_out = open(strc->comand[i][1], O_WRONLY | O_APPEND
				| O_CREAT, 0777);
		ex_case(strc, 1, i);
		k = 2;
	}
	else
	{
		strc->redir_out = open(strc->comand[i + 1][0],
				O_WRONLY | O_APPEND | O_CREAT, 0777);
		k = 1;
	}
	return (k);
}

int	create_files(t_struct *strc, int i)
{
	int	k;

	k = 0;
	if (strc->flags[i] == 3)
		k = trunc_file(strc, k, i);
	if (strc->flags[i] == 6)
		k = append_file(strc, k, i);
	if (strc->redir_out == -1)
	{
		error(strc, strc->comand[i + 1][0], NULL, 1);
		k = -1;
	}
	if (k == 1 && strc->err == 0)
		rebuild(strc, 3, i);
	return (k);
}
