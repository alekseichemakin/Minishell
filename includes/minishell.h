#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_parser
{
	int		x;
	int		add;
	int		*flags;
	int		*real;
	char	**com;
}				t_parser;

typedef struct s_struct
{
	int		err;
	int		ret_val;
	char	***comand;
	int		*flags;
	char	**envs;
	int		orig_fd_0;
	int		orig_fd_1;
	int		**f_fd;
	pid_t	pid[3];
	int		redir_in;
	int		redir_out;
	char	*cod_word;
	int		last;
	int		*flags_in;
	int		*flags_out;
}					t_struct;

void		parser(char *line, t_struct *strc);
int			pre_parser(char *line);
void		free_arr(char **arr);
char		*clear_slash(char *line, const int *flag, t_struct strc, int k);
char		*is_slash(char *line, int i);
char		*is_dollar(char *line, int *i, t_struct strc, int *k);
int			*init_real(int *arr);
void		init_structs(t_struct *strc, t_parser *parser, char *line);
char		**get_comands(char *line, t_struct *strc);
int			*get_flags(const char *line);
t_struct	clear_one_quote(char *line, int *i, t_struct strc, t_parser *pars);
t_struct	clear_two_quote(char *line, int *i, t_struct strc, t_parser *pars);
char		**add_args(t_parser *parser, char *arg, char *arg2);
t_parser	get_real(t_parser parser);
void		rl_replace_line(const char *a, int b);
void		sigint_handler(int sign_num);
t_struct	get_3d_massive(t_struct strc, t_parser parser);
void		free_strc(t_struct strc);
t_struct	improve_massive(t_struct strc);
int			ft_arrsize(char **arr);
void		ex_case(t_struct *strc, int flag, int i);
void		fck_case(t_struct *strc, t_parser *parser);
t_struct	get_str(t_struct strc, int k, int i, t_parser parser);
void		main_cycle(t_struct *strc);
void		error(t_struct *strc, char *src, char *problem, int ret_cod);
void		daddy_process(t_struct *strc, int pid);
t_struct	get_args(const char *line, int i, t_struct strc, t_parser *parser);
t_parser	define_real(int i, t_parser parser);
int			get_num_fckstr(const int *real, int *k, char **com, int *flag);
int			create_files(t_struct *strc, int i);
int			get_input(t_struct *strc, int i);
void		rebuild(t_struct *strc, int flag, int i);
int			err_proc(int err);
int			chek_semicolon(const char *line, int i, const int *fek);
int			check_quote(const char *line, int i, int *err, const int *fek);
int			echo_func(char **mass);
int			exec_comand(t_struct *strc);
int			pwd_func(char **mass);
int			env_func(t_struct *strc);
int			export_func(t_struct *strc, char **comand);
char		**rewrite(char **comand, int x, int k);
int			unset_func(t_struct *strc, char **comand);
void		exit_func(char **arr);
int			cd_func(t_struct *strc, char **comand);
void		old_pwd(t_struct *strc);
void		cd_home(t_struct *strc);
int			cd_pars(t_struct *strc, char *comand);
int			search_side_process(t_struct *strc, int str_num);
char		*env_variable_argument(t_struct *strc, char *var);
int			outside_process(t_struct *strc, int i);
void		export_arg_func(t_struct *strc, char **comand);
int			pipe_first(t_struct *strc, int str_num);
void		with_flags(t_struct *strc);
int			start_proc(t_struct *strc, int i);
int			check_builtins(t_struct *strc, int i);
int			second_pipe(t_struct *strc, int str_num);
int			exec_process(t_struct *strc, int str_num);
int			user_side_proc(t_struct *strc, int str_num);
char		*env_variable_argument(t_struct *strc, char *var);
char		*is_question(int *i, t_struct strc);

#endif