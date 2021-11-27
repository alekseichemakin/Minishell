#include "../includes/minishell.h"

void	sigint_handler(int sign_num)
{
	(void )sign_num;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  ", 2);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
