NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -I $(HEADER)

SRCS		=	main.c \
				builtins/env.c \
				builtins/export.c \
				builtins/export_2.c \
				builtins/unset.c \
                builtins/echo.c \
                builtins/pwd.c \
                builtins/exit.c \
                builtins/cd/cd.c \
                builtins/cd/cd_home.c \
                builtins/cd/cd_oldpwd.c \
                parser/clear_functions.c \
				parser/improve.c \
				parser/improve2.c \
				parser/improve3.c \
                parser/utils.c \
                parser/utils2.c \
                parser/utils3.c \
                parser/get_commands.c \
                parser/parser.c \
                parser/parser2.c \
                parser/get_flags.c \
                parser/pre_parser.c \
                parser/pre_parser2.c \
                pipe/pipe_first.c \
                process/side_process.c \
                parser/ft_signal.c \
				exec/exec_comand.c \
				exec/exec_flags.c \
				parser/get_big_arr.c \
				parser/get_big_arr2.c \
				parser/get_big_arr3.c \
				errors/errors.c\
				process/user_side_process.c\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) -lreadline -ltermcap -L ~/.brew/Cellar/readline/8.1/lib/ \
				 -I ~/.brew/Cellar/readline/8.1/include $(CFLAGS)  \
				   $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all