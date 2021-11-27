#include "../includes/minishell.h"

t_struct	clear_one_quote(char *line, int *i, t_struct strc, t_parser *parser)
{
	int		j;
	char	*new2;

	j = *i;
	(*i)++;
	while (line[(*i)] != '\'' && parser->flags[*i] != 1)
		(*i)++;
	new2 = ft_substr(line, j + 1, (*i) - j - 1);
	if (parser->add == 1)
		parser->com[(parser->x) - 1] = ft_strjoin(parser->com[(parser->x) - 1],
				new2);
	else
		parser->com = add_args(parser, NULL, new2);
	return (strc);
}

char	*get_buf(char *buf, int *i, t_parser *parser, t_struct strc)
{
	int	n;
	int	k;

	k = 0;
	n = (*i);
	while (buf[++n])
		if (buf[n] == '\"' && parser->flags[n] == 1)
			break ;
	while (buf[++(*i)])
	{
		if (buf[*i] == '\\' && parser->flags[*i + k] == 1)
		{
			buf = is_slash(buf, *i);
			k++;
		}
		if (buf[*i] == '$' && parser->flags[*i + k] == 1)
			buf = is_dollar(buf, i, strc, &k);
		if (buf[(*i)] == '\"' && parser->flags[*i + k] == 1)
			break ;
	}
	return (buf);
}

t_struct	clear_two_quote(char *line, int *i, t_struct strc, t_parser *parser)
{
	int		j;
	int		n;
	char	*new2;
	char	*buf;

	buf = ft_strdup(line);
	j = *i;
	n = (*i);
	buf = get_buf(buf, i, parser, strc);
	new2 = ft_substr(buf, j + 1, (*i) - j - 1);
	*i = n;
	if (parser->add == 1)
	{
		parser->com[(parser->x) - 1] = ft_strjoin(parser->com[(parser->x) - 1],
				new2);
		free(new2);
	}
	else
		parser->com = add_args(parser, NULL, new2);
	free(buf);
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	return (strc);
}
