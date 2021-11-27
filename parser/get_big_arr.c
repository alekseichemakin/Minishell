#include "../includes/minishell.h"

int	get_num_arr(const int *real, char **com)
{
	int	i;
	int	num;

	num = 0;
	i = -1;
	while (com[++i])
		if (real[i] == 1)
			num++;
	return (num);
}

int	get_num_str(const int *real, int *k, char **com)
{
	int	i;

	i = 0;
	while (com[*k])
	{
		if (real[*k] == 1)
		{
			(*k)++;
			return (i);
		}
		i++;
		(*k)++;
	}
	return (i);
}

t_struct	get_str(t_struct strc, int k, int i, t_parser parser)
{
	int	d;
	int	n;

	n = k;
	if (parser.real[k - 1] == 1)
		k = k - 2;
	while (parser.real[k] != 1 && k > 0)
		k--;
	if (parser.real[k] == 1)
		k++;
	d = 0;
	while (parser.real[k] != 1 && k < n)
	{
		strc.comand[i][d] = ft_strdup(parser.com[k]);
		if (parser.real[k] != 0)
			strc.flags[i] = parser.real[k];
		k++;
		d++;
	}
	strc.comand[i][d] = NULL;
	return (strc);
}

static	t_struct	get_comand(t_struct strc, int num, t_parser parser)
{
	int	i;
	int	k;
	int	n;

	k = 0;
	i = -1;
	while (++i < num)
	{
		n = get_num_str(parser.real, &k, parser.com);
		strc.comand[i] = malloc(sizeof(char **) * (n + 1));
		strc = get_str(strc, k, i, parser);
	}
	strc.comand[i] = NULL;
	return (strc);
}

t_struct	get_3d_massive(t_struct strc, t_parser parser)
{
	int	num;

	if (parser.com)
	{
		if ((parser.com[0][0] == '>' || parser.com[0][0] == '<') &&
				parser.real[0] != 0)
			fck_case(&strc, &parser);
		else
		{
			num = get_num_arr(parser.real, parser.com) + 1;
			strc.comand = malloc(sizeof(char ***) * (num + 1));
			strc = get_comand(strc, num, parser);
		}
	}
	return (strc);
}
