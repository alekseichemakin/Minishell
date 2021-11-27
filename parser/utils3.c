#include "../includes/minishell.h"

char	*destributor(char *line, char *new2, int *i, int j)
{
	char	*new;
	char	*new3;
	char	*new4;

	new = ft_substr(line, 0, j);
	new3 = ft_strdup(line + (*i));
	new4 = ft_strjoin(new, new2);
	free(new);
	new = ft_strjoin(new4, new3);
	*i = j + (int)ft_strlen(new2);
	free(line);
	free(new4);
	free(new2);
	free(new3);
	return (new);
}

char	*get_new2(char *new2, t_struct strc, int n, int k)
{
	if (new2)
	{
		free(new2);
		new2 = ft_substr(strc.envs[n], k + 1, ft_strlen(strc.envs[n]) - k);
	}
	else
		new2 = ft_strdup("");
	return (new2);
}

char	*replace_dollar2(char *new, int j, int i, t_struct strc)
{
	int		n;
	int		k;
	char	*new2;

	new2 = NULL;
	n = -1;
	while (strc.envs[++n])
	{
		if ((ft_strnstr(strc.envs[n], new, (i) - j - 1)))
		{
			k = 0;
			while (strc.envs[n][k] && strc.envs[n][k] != '=')
				k++;
			new2 = ft_substr(strc.envs[n], 0, k);
			if (ft_strncmp(new, new2, ft_strlen(new2)) == 0)
				break ;
			else
			{
				free(new2);
				new2 = NULL;
			}
		}
	}
	return (get_new2(new2, strc, n, k));
}

char	*replace_dollar(char *line, int *i, t_struct strc, int *o)
{
	int		j;
	char	*new;
	char	*new2;

	j = *i - 1;
	new = NULL;
	new2 = NULL;
	while (line[(*i)])
	{
		if (line[*i] != '_' && ft_isalnum(line[*i]) == 0)
			break ;
		(*i)++;
	}
	if (*i == j + 1)
		return (line);
	new = ft_substr(line, j + 1, (*i) - j - 1);
	*o += (int) ft_strlen(new) + 1;
	new2 = replace_dollar2(new, j, *i, strc);
	free(new);
	return (new2);
}

char	*is_dollar(char *line, int *i, t_struct strc, int *o)
{
	int		j;
	char	*new2;

	new2 = NULL;
	j = *i;
	if (line[++(*i)] != '_' && !ft_isalpha(line[*i]) && line[(*i)] != '?')
	{
		(*i)++;
		new2 = ft_strdup("");
	}
	else if (line[(*i)] == '?')
		new2 = is_question(i, strc);
	else
		new2 = replace_dollar(line, i, strc, o);
	*o -= (int)ft_strlen(new2);
	return (destributor(line, new2, i, j));
}
