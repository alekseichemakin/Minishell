#include "includes/minishell.h"

void	struct_env_inic(char **env, t_struct *strc)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	strc->envs = malloc((i + 1) * sizeof (char **));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD", 6) != 0)
			strc->envs[i] = ft_strdup(env[i]);
		else
			strc->envs[i] = ft_strdup("OLDPWD");
		i++;
	}
	strc->envs[i] = NULL;
}

void	comands_cycle(char **comands, t_struct *strc)
{
	int	i;

	i = -1;
	while (comands && comands[++i])
	{
		parser(comands[i], strc);
		if (strc->comand && strc->err == 0)
			if (exec_comand(strc) == -1)
				exit (1);
		free_strc(*strc);
		dup2(strc->orig_fd_0, 0);
		dup2(strc->orig_fd_1, 1);
	}
}

void	main_cycle(t_struct *strc)
{
	char	**comands;
	char	*line;

	while (1)
	{
		strc->err = 0;
		dup2(strc->orig_fd_0, 0);
		dup2(strc->orig_fd_1, 1);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishit> ");
		add_history(line);
		if (line == NULL)
			exit(0);
		comands = get_comands(line, strc);
		free(line);
		comands_cycle(comands, strc);
		free(comands);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_struct	strc;

	(void)argv;
	(void)argc;
	struct_env_inic(env, &strc);
	strc.ret_val = 0;
	strc.orig_fd_0 = dup(0);
	strc.orig_fd_1 = dup(1);
	strc.err = 0;
	main_cycle(&strc);
	return (0);
}
