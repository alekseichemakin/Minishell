#include "../includes/minishell.h"

static int	get_num(const char *line)
{
	int	open;
	int	num;
	int	i;

	i = -1;
	open = 0;
	num = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && line[i - 1] != '\\' && open == 0)
			open = 1;
		else if (line[i] == '\"' && line[i - 1] != '\\' && open == 0)
			open = 2;
		else if ((line[i] == '\'' && open == 1) || (line[i] == '\"'
				&& open == 2 && line[i - 1] != '\\'))
			open = 0;
		else if (line[i] == ';' && open == 0 && line[i - 1] != '\\'
			&& line[i + 1] != '\0')
			num++;
	}
	return (num);
}

static char	**get_arr(char *line, char **arr, int num, int i)
{
	int	k;
	int	open;
	int	n;

	n = 0;
	open = 0;
	k = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && line[i - 1] != '\\' && open == 0)
			open = 1;
		else if (line[i] == '\"' && line[i - 1] != '\\' && open == 0)
			open = 2;
		else if ((line[i] == '\'' && open == 1) || (line[i] == '\"' && open == 2
				&& line[i - 1] != '\\'))
			open = 0;
		if (((line[i + 1] == ';' && line[i] != '\\') || line[i + 1] == '\0')
			&& open == 0 && k <= num)
		{
			arr[k] = ft_substr(line, n, i - n + 1);
			k++;
			n = i + 2;
		}
	}
	return (arr);
}

char	**get_comands(char *line, t_struct *strc)
{
	int		i;
	int		num;
	char	**arr;

	if (pre_parser(line))
	{
		strc->ret_val = 258;
		return (NULL);
	}
	num = get_num(line);
	arr = malloc(sizeof (char *) * (num + 2));
	if (arr == NULL)
	{
		error(strc, "malloc", "memory not allocated", 1);
		return (NULL);
	}
	i = -1;
	while (++i <= num + 1)
		arr[i] = NULL;
	i = -1;
	return (get_arr(line, arr, num, i));
}
