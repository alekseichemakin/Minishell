#include "../includes/minishell.h"

char	*path_write(char *comand, const char *path_args, int i, int j)
{
	int		k;
	char	*path;

	k = 0;
	if (path_args[j] == ':' || path_args[j] == '\0')
		j++;
	path = malloc(sizeof(char) * (i - 1 - j + 2 + ft_strlen(comand)));
	while (j < i)
		path[k++] = path_args[j++];
	path[k++] = '/';
	i = 0;
	while (comand[i])
		path[k++] = comand[i++];
	path[k] = '\0';
	return (path);
}

int	search_side_2(t_struct *strc, int str_num, char *path_args)
{
	int		ret;
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (path_args[++i])
	{
		if (path_args[i] == ':' || path_args[i] == '\0')
		{
			path = path_write(strc->comand[str_num][0], path_args, i, j);
			j = i;
			ret = execve(path, strc->comand[str_num], strc->envs);
		}
	}
	if (path_args[i] == '\0')
	{
		path = path_write(strc->comand[str_num][0], path_args, i, j);
		ret = execve(path, strc->comand[str_num], strc->envs);
	}
	return (ret);
}

int	search_side_process(t_struct *strc, int str_num)
{
	int		ret;
	char	*path_args;

	if ((strc->comand[str_num][0][0] == '.' && strc->comand[str_num][0][1] ==
	'/') || strc->comand[str_num][0][0] == '/' || strc->comand[str_num][0][0]
	== '~')
		return (user_side_proc(strc, str_num));
	path_args = env_variable_argument(strc, "PATH=");
	if (path_args == NULL)
		return (-1);
	ret = search_side_2(strc, str_num, path_args);
	return (ret);
}

void	daddy_process(t_struct *strc, int pid)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	strc->ret_val = WEXITSTATUS(pid);
	waitpid(pid, &strc->ret_val, 0);
	if (WTERMSIG(strc->ret_val) == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		strc->ret_val = 256 * 130;
	}
	else if (WTERMSIG(strc->ret_val) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		strc->ret_val = 256 * 131;
	}
	strc->ret_val /= 256;
}

int	outside_process(t_struct *strc, int i)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid < 0)
	{
		error(strc, "fork", NULL, 1);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ret = search_side_process(strc, i);
		if (ret == -1)
		{
			error(strc, strc->comand[i][0], "command not found", 127);
			exit(127);
		}
		exit(0);
	}
	daddy_process(strc, pid);
	return (0);
}
