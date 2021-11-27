#include "../includes/minishell.h"

int	echo_func(char **mass)
{
	int	i;
	int	fl;

	i = 1;
	fl = 0;
	if (mass[1] && mass[1][0])
	{
		while (ft_strncmp(mass[i], "-n", ft_strlen(mass[1])) == 0)
		{
			fl = 1;
			i++;
		}
	}
	while (mass[i])
	{
		ft_putstr_fd(mass[i++], 1);
		if (mass[i])
			write(1, " ", 1);
	}
	if (fl != 1)
		printf("\n");
	return (1);
}
