#include "../includes/minishell.h"

void	error(t_struct *strc, char *src, char *problem, int ret_cod)
{
	if (strc)
	{
		strc->ret_val = ret_cod;
		strc->err = 1;
	}
	ft_putstr_fd("minishit: ", 2);
	ft_putstr_fd(src, 2);
	ft_putstr_fd(": ", 2);
	if (problem)
		ft_putstr_fd(problem, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
