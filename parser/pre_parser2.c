#include "../includes/minishell.h"

int	err_proc(int err)
{
	if (err == 1)
		ft_putstr_fd("minishit: syntax error near unexpected token ';'\n", 2);
	else if (err == 2)
		ft_putstr_fd("minishit: syntax error near unexpected token '\"'\n", 2);
	else if (err == 3)
		ft_putstr_fd("minishit: syntax error near unexpected token '|'\n", 2);
	else if (err == 4)
		ft_putstr_fd("minishit: syntax error near unexpected token '\\'\n", 2);
	else if (err == 5)
		ft_putstr_fd("minishit: syntax error near unexpected token 'newline'\n",
			2);
	return (1);
}

int 	chek_semicolon(const char *line, int i, const int *fek)
{
	if (i == 0)
		return (1);
	while (--i >= 0)
	{
		if (!ft_strchr(" \t|;><", line[i]) || (ft_strchr(" \t|;><", line[i])
				&& fek[i] == 1))
			return (0);
		else if (ft_strchr("|;><", line[i]) && fek[i] == 0)
			return (1);
	}
	return (1);
}

int 	check_quote(const char *line, int i, int *err, const int *fek)
{
	if (line[i] == '\'' && fek[i] == 0)
	{
		while (line[++i])
			if (line[i] == '\'')
				return (i);
		*err = 2;
	}
	else if (line[i] == '\"' && fek[i] == 0)
	{
		while (line[++i])
		{
			while (line[i] == '\\' && line[i + 1] != '\0')
				i = i + 2;
			if (line[i] == '\"')
				return (i);
		}
		*err = 2;
	}
	return (-1);
}
