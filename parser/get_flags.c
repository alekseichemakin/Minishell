#include "../includes/minishell.h"

t_parser	define_real(int i, t_parser parser)
{
	int	n;

	n = i;
	i--;
	while (i > 0 && parser.real[i - 1] != 1)
		i--;
	if (parser.com[n][0] == '|')
		parser.real[i] = 2;
	else if (parser.com[n][0] == '>' && parser.com[n][1] == '>')
		parser.real[i] = 6;
	else if (parser.com[n][0] == '>')
		parser.real[i] = 3;
	else if (parser.com[n][0] == '<' && parser.com[n][1] == '<')
		parser.real[i] = 8;
	else if (parser.com[n][0] == '<')
		parser.real[i] = 4;
	return (parser);
}

int 	check_open(const char *line, int i, const int *flags, int *open)
{
	if (line[i] == '\'' && *open == 0 && (line[i - 1] != '\\'
			|| (line[i - 1] == '\\' && flags[i - 1] == 0)))
	{
		*open = 1;
		return (1);
	}
	else if (line[i] == '\"' && *open == 0 && (line[i - 1] != '\\'
			|| (line[i - 1] == '\\' && flags[i - 1] == 0)))
	{
		*open = 2;
		return (1);
	}
	else if ((line[i] == '\'' && *open == 1) || (line[i] == '\"' && *open == 2
			&& (line[i - 1] != '\\' || flags[i - 1] == 0)))
	{
		*open = 0;
		return (1);
	}
	return (0);
}

static int 	check_slash(const char *line, int i, const int *flags, int open)
{
	if (open == 2 && (line[i - 1] != '\\'
			|| (line[i - 1] == '\\' && flags[i - 1] == 0)))
	{
		if (line[i + 1] == '\\' || line[i + 1] == '\"' || line[i + 1] == '$')
			return (1);
	}
	else if (open == 0 && (line[i - 1] != '\\'
			|| (line[i - 1] == '\\' && flags[i - 1] == 0)))
		return (1);
	return (0);
}

int	*flags_cycle(const char *line, int *flags)
{
	int	i;
	int	open;

	i = -1;
	open = 0;
	while (line[++i])
	{
		if (ft_strchr("\'\"", line[i]))
			flags[i] = check_open(line, i, flags, &open);
		else if (ft_strchr("$", line[i]) && open != 1 && (line[i - 1] != '\\'
				|| (line[i - 1] == '\\' && flags[i - 1] == 0))
			&& line[i + 1] != '\0' && line[i + 1] != ' ')
			flags[i] = 1;
		else if (ft_strchr("><|", line[i]) && (line[i - 1] != '\\'
				|| (line[i - 1] == '\\' && flags[i - 1] == 0)) && open == 0)
			flags[i] = 1;
		else if (line[i] == '\\')
			flags[i] = check_slash(line, i, flags, open);
		else if (ft_strchr(" \t", line[i]))
			if (open == 0 && (line[i - 1] != '\\'
					|| (line[i - 1] == '\\' && flags[i - 1] == 0)))
				flags[i] = 1;
	}
	return (flags);
}

int 	*get_flags(const char *line)
{
	int	*flags;
	int	i;

	flags = malloc(sizeof(int *) * 1024);
	if (!(flags))
		exit(1);
	i = -1;
	while (++i <= 1024)
		flags[i] = 0;
	flags = flags_cycle(line, flags);
	return (flags);
}
