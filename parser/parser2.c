#include "../includes/minishell.h"

t_parser	get_real(t_parser parser)
{
	int	i;

	i = -1;
	if (parser.com)
	{
		while (parser.com[++i])
			if (parser.real[i] == 1)
				parser = define_real(i, parser);
	}
	return (parser);
}

char	*get_first_arg(const char *line, int i)
{
	char	*arg;

	arg = NULL;
	if (line[i] == '>' && line[i + 1] == '>')
		arg = ft_strdup(">>");
	else if (line[i] == '<' && line[i + 1] == '<')
		arg = ft_strdup("<<");
	else if (line[i] == '>' && line[i - 1] == '>')
		return (NULL);
	else if (line[i] == '<' && line[i - 1] == '<')
		return (NULL);
	else
	{
		arg = malloc(2);
		arg[0] = line[i];
		arg[1] = '\0';
	}
	return (arg);
}

int	get_j(int j, t_parser *pars, const char *line)
{
	while (--j > 0)
	{
		if (pars->flags[j] == 1 && line[j] != '\\' && line[j] != '$')
		{
			j++;
			break ;
		}
	}
	if (pars->flags[j] == 1 && line[j] != '\\' && line[j] != '$')
		j++;
	return (j);
}

char	*get_second_arr(const char *line, int i, t_parser *pars, t_struct *strc)
{
	int		j;
	char	*arg2;

	j = i;
	if (j != 0 && (pars->flags[j - 1] != 1 || ft_strchr("$\\",
				line[j - 1])))
		j = get_j(j, pars, line);
	if (!ft_strchr(" \t|><\"\';", line[i]) || line[i] == '\0'
		|| (ft_strchr(" \t|><\"\'", line[i]) && pars->flags[i] == 0))
	{
		if (line[i] == '\0' && ft_strchr(" \t|><\"\';", line[i - 1]))
			j--;
		i++;
	}
	arg2 = ft_substr(line, j, i - j);
	arg2 = clear_slash(arg2, pars->flags, *strc, j);
	return (arg2);
}

t_struct	get_args(const char *line, int i, t_struct strc, t_parser *parser)
{
	char	*arg;
	char	*arg2;

	arg = NULL;
	arg2 = NULL;
	if (ft_strchr("><|", line[i]) && parser->flags[i] == 1)
	{
		arg = get_first_arg(line, i);
		if (arg == NULL)
			return (strc);
	}
	if (!arg || (parser->flags[i - 1] != 1 && i != 0))
		arg2 = get_second_arr(line, i, parser, &strc);
	if (parser->add == 1)
	{
		if (arg2)
			parser->com[(parser->x) - 1]
				= ft_strjoin(parser->com[(parser->x) - 1], arg2);
		if (arg)
			parser->com = add_args(parser, arg, NULL);
	}
	else if (arg2 || arg)
		parser->com = add_args(parser, arg, arg2);
	return (strc);
}
