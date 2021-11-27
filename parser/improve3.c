#include "../includes/minishell.h"

int	get_redir_in(t_struct *strc, int i, int k)
{
	if (strc->redir_in != 0)
		close(strc->redir_in);
	if (strc->comand[i][0][0] == '<')
	{
		strc->redir_in = open(strc->comand[i][1], O_RDONLY);
		ex_case(strc, 0, i);
		k = 2;
	}
	else
	{
		strc->redir_in = open(strc->comand[i + 1][0], O_RDONLY);
		k = 1;
	}
	return (k);
}

void	rec_to_fd(t_struct *strc)
{
	int		fd[2];
	int		n;
	char	*buf;

	pipe(fd);
	while (1)
	{
		n = (int)ft_strlen(strc->cod_word);
		buf = readline("> ");
		if ((int)ft_strlen(buf) > n)
			n = (int)ft_strlen(buf);
		if (ft_strncmp(buf, strc->cod_word, n) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(buf);
	}
	close(fd[1]);
	strc->redir_in = fd[0];
}

int	double_revers(t_struct *strc, int k, int i)
{
	if (strc->redir_in != 0)
		close(strc->redir_in);
	strc->cod_word = ft_strdup(strc->comand[i + 1][0]);
	rec_to_fd(strc);
	k = 1;
	if (strc->comand[i][0][0] == '<')
	{
		ex_case(strc, 0, i);
		k = 2;
	}
	return (k);
}

int	get_input(t_struct *strc, int i)
{
	int		k;

	errno = 0;
	k = 0;
	if (strc->flags[i] == 8)
		k = double_revers(strc, k, i);
	if (strc->flags[i] == 4)
		k = get_redir_in(strc, i, k);
	if (strc->redir_in == -1)
	{
		error(strc, strc->comand[i + 1][0], NULL, 1);
		k = -1;
	}
	if (k == 1 && strc->err == 0)
		rebuild(strc, 4, i);
	return (k);
}
