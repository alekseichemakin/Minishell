#include "../../includes/minishell.h"

int	cd_pars(t_struct *strc, char *comand)
{
	if (chdir(comand) == -1)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(comand, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		strc->err = 1;
		return (-1);
	}
	else
		old_pwd(strc);
	return (1);
}

int	cd_func(t_struct *strc, char **comand)
{
	if (comand[1] && !(comand[1][0] == '~' && comand[1][1] == '\0'))
		cd_pars(strc, comand[1]);
	else
		cd_home(strc);
	return (1);
}
