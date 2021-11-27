#include "../includes/minishell.h"

int	get_fck_num(char **com, const int *real)
{
	int	i;
	int	flag;
	int	num;

	i = -1;
	flag = 0;
	num = 0;
	while (com[++i] && real[i] != 0)
	{
		if (real[i] == 1 && ft_strchr("><|", com[i][0]))
			num++;
		if (real[i + 1] != 1 && ft_strchr("><|", com[i][0]))
			i++;
	}
	while (com[i])
	{
		if (real[i] == 1)
			num++;
		flag = 1;
		i++;
	}
	return (num + flag);
}

int	define_fckflag(const char *str)
{
	if (str[0] == '|')
		return (2);
	else if (str[0] == '>' && str[1] == '>')
		return (6);
	else if (str[0] == '>')
		return (3);
	else if (str[0] == '<' && str[1] == '<')
		return (8);
	else if (str[0] == '<')
		return (4);
	return (0);
}

void	fck_str(t_struct *strc, int k, int i, t_parser *parser)
{
	strc->comand[i][0] = ft_strdup(parser->com[k - 2]);
	strc->comand[i][1] = ft_strdup(parser->com[k - 1]);
	strc->comand[i][2] = NULL;
	strc->flags[i] = define_fckflag(parser->com[k - 2]);
	strc->flags[i + 1] = parser->real[k - 1];
	parser->real[k - 1] = 1;
}

void	get_fck_cmd(t_struct *strc, t_parser *parser, int num)
{
	int	i;
	int	k;
	int	n;
	int	flag;

	flag = 0;
	k = 0;
	i = -1;
	while (++i < num)
	{
		n = get_num_fckstr(parser->real, &k, parser->com, &flag);
		strc->comand[i] = malloc(sizeof(char **) * (n + 1));
		if (flag == 0)
			fck_str(strc, k, i, parser);
		else
			*strc = get_str(*strc, k, i, *parser);
	}
	strc->comand[i] = NULL;
}

void	fck_case(t_struct *strc, t_parser *parser)
{
	int	num;

	num = get_fck_num(parser->com, parser->real);
	strc->comand = malloc(sizeof(char ***) * (num + 1));
	get_fck_cmd(strc, parser, num);
}
