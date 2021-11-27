#include "../../includes/minishell.h"

void	copy_home_arg_to_pwd(t_struct *strc, int pwd, int home)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = "PWD=";
	while (strc->envs[home][i])
		i++;
	free(strc->envs[pwd]);
	strc->envs[pwd] = malloc(sizeof(char) * (4 + i - 5 + 1));
	while (str[j])
	{
		strc->envs[pwd][j] = str[j];
		j++;
	}
	i = 5;
	while (strc->envs[home][i])
		strc->envs[pwd][j++] = strc->envs[home][i++];
	strc->envs[pwd][j] = '\0';
}

char	*env_variable_argument(t_struct *strc, char *var)
{
	int		i;
	int		j;
	int		k;
	char	*comand;

	i = 0;
	j = 0;
	k = (int)ft_strlen(var);
	while (strc->envs[i] && ft_strncmp(strc->envs[i], var, k))
		i++;
	if (strc->envs[i] == NULL)
		return (NULL);
	comand = malloc(sizeof(char) * ft_strlen(strc->envs[i]) - k + 1);
	while (strc->envs[i][j + k])
	{
		comand[j] = strc->envs[i][j + k];
		j++;
	}
	comand[j] = '\0';
	return (comand);
}

void	cd_home(t_struct *strc)
{
	int		i;
	int		j;
	char	*comand;

	i = 0;
	j = 0;
	comand = env_variable_argument(strc, "HOME=");
	cd_pars(strc, comand);
	free(comand);
	while (ft_strncmp(strc->envs[i], "PWD=", 4))
		i++;
	while (ft_strncmp(strc->envs[j], "HOME=", 5))
		j++;
	copy_home_arg_to_pwd(strc, i, j);
}
