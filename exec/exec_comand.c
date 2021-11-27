#include "../includes/minishell.h"

int	strncmp_mod(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (s1 && (ft_strlen(s1) == ft_strlen(s2)))
	{
		i = 0;
		if (n == 0)
			return (0);
		while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
			i++;
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	else
		return (1);
}

int	check_builtins(t_struct *strc, int i)
{
	if ((strncmp_mod(strc->comand[i][0], "exit", 4)) == 0)
		exit_func(strc->comand[i]);
	else if ((strncmp_mod(strc->comand[i][0], "echo", 4)) == 0)
		return (echo_func(strc->comand[i]));
	else if ((strncmp_mod(strc->comand[i][0], "pwd", 3)) == 0)
		return (pwd_func(strc->comand[i]));
	else if ((strncmp_mod(strc->comand[i][0], "env", 3)) == 0)
		return (env_func(strc));
	else if ((strncmp_mod(strc->comand[i][0], "export", 6)) == 0)
		return (export_func(strc, strc->comand[i]));
	else if ((strncmp_mod(strc->comand[i][0], "unset", 5)) == 0)
		return (unset_func(strc, strc->comand[i]));
	else if ((strncmp_mod(strc->comand[i][0], "cd", 2)) == 0)
		return (cd_func(strc, strc->comand[i]));
	return (0);
}

int	start_proc(t_struct *strc, int i)
{
	int	ret;

	if (strc->flags_in[i] != 0)
		dup2(strc->redir_in, 0);
	if (strc->flags_out[i] != 0)
		dup2(strc->redir_out, 1);
	ret = check_builtins(strc, i);
	if (ret == 1)
		return (0);
	else if (ret < 0)
		return (-1);
	outside_process(strc, i);
	dup2(strc->orig_fd_0, 0);
	dup2(strc->orig_fd_1, 1);
	return (1);
}

int	exec_comand(t_struct *strc)
{
	if (strc->comand[0])
	{
		if (strc->flags[0] == 0)
		{
			start_proc(strc, 0);
			if (strc->redir_out != 0)
				close(strc->redir_out);
			if (strc->redir_in != 0)
				close(strc->redir_in);
			return (0);
		}
		else
			with_flags(strc);
	}
	if (strc->redir_out != 0)
		close(strc->redir_out);
	if (strc->redir_in != 0)
		close(strc->redir_in);
	return (1);
}
