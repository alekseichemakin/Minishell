#include "../../includes/minishell.h"

void	copy_pwd_arg_to_oldpwd(t_struct *strc, int old, int pwd)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = "OLDPWD=";
	while (strc->envs[pwd][i])
		i++;
	free(strc->envs[old]);
	strc->envs[old] = malloc(sizeof(char) * (7 + i - 4 + 1));
	while (str[j])
	{
		strc->envs[old][j] = str[j];
		j++;
	}
	i = 4;
	while (strc->envs[pwd][i])
		strc->envs[old][j++] = strc->envs[pwd][i++];
	strc->envs[old][j] = '\0';
}

void	pwd_rewrite(t_struct *strc, int j)
{
	char	*str;

	free (strc->envs[j]);
	str = getcwd(NULL, 1024);
	strc->envs[j] = ft_strjoin("PWD=", str);
	free (str);
}

void	old_pwd(t_struct *strc)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (ft_strncmp(strc->envs[i], "OLDPWD", 6))
		i++;
	while (ft_strncmp(strc->envs[j], "PWD=", 4))
		j++;
	copy_pwd_arg_to_oldpwd(strc, i, j);
	str = getcwd(NULL, 1024);
	if (str != NULL)
		pwd_rewrite(strc, j);
	free (str);
}
