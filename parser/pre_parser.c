#include "../includes/minishell.h"

int	check_pipe(const char *line, int i, const int *fek)
{
	int	j;
	int	flag;

	flag = 0;
	if (i == 0)
		return (3);
	j = i;
	while (--i >= 0 && flag == 0)
	{
		if (!ft_strchr(" \t|;><", line[i]) || (ft_strchr(" \t|;><", line[i])
				&& fek[i] == 1))
			flag = 1;
		else if (ft_strchr("|;><", line[i]) || i == 0)
			return (3);
	}
	while (line[++j])
		if (!ft_strchr(" \t|;><", line[j]) && line[j] != '\0')
			return (0);
	return (3);
}

static	int	check_slash(const char *line, int i)
{
	int	n;

	n = 1;
	while (i >= 0 && line[--i] == '\\')
		n++;
	if (n % 2 == 0)
		return (0);
	return (4);
}

int	check_n(char *line, int i, const int *fek)
{
	while (--i >= 0)
	{
		if (!ft_strchr(" \t><|", line[i]) || (ft_strchr(" \t><|", line[i])
				&& fek[i] == 1))
			return (0);
		else if (ft_strchr("><|", line[i]) && fek[i] == 0)
			return (5);
	}
	return (0);
}

int	pre_parser_checker(int *fek, int *i, char *line)
{
	int	err;

	err = 0;
	if (line[*i] == ';' && fek[*i] == 0)
		err = chek_semicolon(line, *i, fek);
	else if ((line[*i] == '\'' || line[*i] == '\"') && fek[*i] == 0)
		*i = check_quote(line, *i, &err, fek);
	else if (line[*i] == '|')
		err = check_pipe(line, *i, fek);
	else if (line[*i] == '\\' && line[*i + 1] == '\0')
		err = check_slash(line, *i);
	return (err);
}

int	pre_parser(char *line)
{
	int	i;
	int	err;
	int	*fek;

	fek = NULL;
	fek = init_real(fek);
	err = 0;
	i = 0;
	while (line[i] && err == 0)
	{
		while (line[i] == '\\' && line[i + 1] != '\0')
		{
			fek[i + 1] = 1;
			i = i + 2;
		}
		err = pre_parser_checker(fek, &i, line);
		i++;
	}
	if (line[i] == '\0' && err == 0)
		err = check_n(line, i, fek);
	if (err != 0)
		return (err_proc(err));
	free(fek);
	return (0);
}
