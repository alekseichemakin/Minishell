#include "../includes/minishell.h"

int	exec_process(t_struct *strc, int str_num)
{
	if (check_builtins(strc, str_num) == 1)
		exit(0);
	else
	{
		if (search_side_process(strc, str_num) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strc->comand[str_num][0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(1);
		}
	}
	return (0);
}

int	second_pipe(t_struct *strc, int str_num)
{
	pipe(strc->f_fd[str_num]);
	close(strc->f_fd[str_num - 1][1]);
	dup2(strc->f_fd[str_num - 1][0], 0);
	dup2(strc->f_fd[str_num][1], 1);
	start_proc(strc, str_num);
	close(strc->f_fd[str_num - 1][0]);
	return (0);
}

void	piper_first_2(t_struct *strc, int str_num)
{
	if (strc->f_fd)
		pipe(strc->f_fd[0]);
	if (strc->flags_in[str_num] != 0)
		dup2(strc->redir_in, 0);
	if (strc->flags_out[str_num] != 0)
		dup2(strc->redir_out, 1);
}

int	pipe_first(t_struct *strc, int str_num)
{
	pid_t	pid;

	piper_first_2(strc, str_num);
	pid = fork();
	if (pid < 0)
	{
		error(strc, "fork", NULL, 1);
		return (1);
	}
	if (pid == 0)
	{
		if (strc->f_fd && strc->flags_out[str_num] == 0)
		{
			close(strc->f_fd[0][0]);
			dup2(strc->f_fd[0][1], 1);
		}
		exec_process(strc, str_num);
		exit(0);
	}
	daddy_process(strc, pid);
	return (0);
}
