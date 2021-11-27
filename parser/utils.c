#include "../includes/minishell.h"

int	*init_real(int *arr)
{
	int	i;

	arr = malloc(sizeof(int *) * 1024);
	if (arr == NULL)
		error(NULL, "malloc", "memory not allocated", 1);
	i = -1;
	while (++i < 1024)
		arr[i] = 0;
	return (arr);
}

char	*is_slash(char *line, int i)
{
	char	*new;
	char	*new2;

	new = ft_substr(line, 0, i);
	new2 = ft_strdup(line + (i) + 1);
	free(line);
	line = ft_strjoin(new, new2);
	free(new2);
	free(new);
	return (line);
}

char	*clear_slash(char *line, const int *flag, t_struct strc, int k)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		while (line[i] == '$' && flag[i + k] == 1)
			line = is_dollar(line, &i, strc, &k);
		if (line[i] == '\\' && flag[i + k] == 1)
		{
			line = is_slash(line, i);
			k++;
		}
	}
	return (line);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = -1;
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}

void	init_structs(t_struct *strc, t_parser *parser, char *line)
{
	strc->comand = NULL;
	strc->redir_out = 0;
	strc->redir_in = 0;
	parser->com = NULL;
	strc->flags = init_real(strc->flags);
	strc->last = -1;
	parser->real = init_real(parser->real);
	parser->flags = NULL;
	parser->x = 0;
	parser->add = 0;
	parser->flags = get_flags(line);
}
