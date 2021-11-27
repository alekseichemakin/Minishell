#include "../includes/minishell.h"

char	**add_args(t_parser *parser, char *arg, char *arg2)
{
	int	k;

	k = 0;
	if (arg)
		k++;
	if (arg2)
		k++;
	parser->com = rewrite(parser->com, (parser->x), k);
	if (arg2)
	{
		parser->com[(parser->x)] = ft_strdup(arg2);
		free(arg2);
	}
	if (arg)
	{
		if (arg2)
			(parser->x)++;
		parser->com[(parser->x)] = ft_strdup(arg);
		free(arg);
		parser->real[parser->x] = 1;
	}
	parser->com[++(parser->x)] = NULL;
	return (parser->com);
}

int	super_checker(char *line, int i, const int *flag)
{
	if (line[i] == '\0')
		return (1);
	if (ft_strchr(" \t", line[i]) && ft_strchr("|><", line[i - 1])
		&& flag[i - 1] == 1)
		return (0);
	if (ft_strchr(" \t", line[i]) && flag[i] == 1 && i != 0)
		if (!ft_strchr(" \t\'\"", line[i - 1])
			|| (ft_strchr(" \t\'\"", line[i - 1]) && flag[i - 1] == 0))
			return (1);
	if ((ft_strchr("|<>", line[i]) && flag[i] == 1))
		return (1);
	if (line[i + 1] == '\0' && (!ft_strchr(" \t\'\"", line[i - 1])
			|| i == 0 || !ft_strchr(" \t\'\"", line[i])))
		return (1);
	if (ft_strchr("\"\'", line[i]) && flag[i - 1] == 0 && i != 0)
		return (1);
	return (0);
}

static	t_parser	parser_cycle(char *line, int i,
								   t_struct strc, t_parser parser)
{
	while (line[i])
	{
		if (super_checker(line, i, parser.flags))
		{
			strc = get_args(line, i, strc, &parser);
			if (ft_strchr("\"\'", line[i]))
				parser.add = 1;
			else
				parser.add = 0;
		}
		if ((line[i] == '\"' || line[i] == '\'') && parser.flags[i] == 1)
		{
			if (line[i] == '\"')
				strc = clear_two_quote(line, &i, strc, &parser);
			else
				strc = clear_one_quote(line, &i, strc, &parser);
			if (ft_strchr(" \t", line[i + 1]))
				parser.add = 0;
			else
				parser.add = 1;
		}
		i++;
	}
	return (parser);
}

void 	parser(char *line, t_struct *strc)
{
	t_parser	parser;
	int			i;

	init_structs(strc, &parser, line);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	parser = parser_cycle(line, i, *strc, parser);
	parser = get_real(parser);
	free(line);
	line = NULL;
	*strc = get_3d_massive(*strc, parser);
	free(parser.real);
	free(parser.flags);
	free_arr(parser.com);
	*strc = improve_massive(*strc);
}
