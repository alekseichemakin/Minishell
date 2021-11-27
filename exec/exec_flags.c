#include "../includes/minishell.h"

int	pipe_count(t_struct strc)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	while (strc.comand[++i])
		if (strc.flags[i] == 2)
			n++;
	return (n);
}

void	get_pipe(t_struct *strc)
{
	int	i;
	int	n;

	i = -1;
	n = pipe_count(*strc);
	strc->f_fd = NULL;
	strc->f_fd = malloc(sizeof(int **) * n);
	if (!strc->f_fd)
		return (error(strc, "malloc", "memory not allocated", 1));
	while (++i < n)
	{
		strc->f_fd[i] = malloc((sizeof(int *)) * 2);
		if (!strc->f_fd[i])
			return (error(strc, "malloc", "memory not allocated", 1));
	}
}

void	with_flags(t_struct *strc)
{
	int	i;

	get_pipe(strc);
	i = -1;
	while (strc->comand[++i])
	{
		if (i == 0)
			pipe_first(strc, i);
		else if (strc->flags[i] == 2)
			second_pipe(strc, i);
		else
		{
			close(strc->f_fd[i - 1][1]);
			dup2(strc->f_fd[i - 1][0], 0);
			start_proc(strc, i);
			close(strc->f_fd[i - 1][0]);
		}
	}
}
