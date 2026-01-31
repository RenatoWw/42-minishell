NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a

SRCS = minishell.c \
		lexer/lexer.c \
		lexer/token_functions.c \
		lexer/free_tokens.c \
		parser/parser.c \
		execute/get_commands.c \
		execute/pipe_process.c \
		execute/utils_exec.c \
		parser/syntax_parser.c \
		parser/parser_functions.c \
		minishell_utils.c \
		expander/envp_functions.c \
		expander/expander.c \
		execute/heredoc.c \
		builtins/utils.c \
		builtins/env.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/pwd.c \
		builtins/exit.c \
		builtins/echo.c \
		builtins/cd.c \
		print_dir.c \
		signals/setup.c \
		get_data.c \
		parser/parser_utils.c \

SRCS_TEST = test/test_main.c \
			lexer/lexer.c \
			lexer/token_functions.c \
			lexer/free_tokens.c \
			parser/parser.c \
			execute/get_commands.c \
			execute/pipe_process.c \
			execute/utils_exec.c \
			parser/syntax_parser.c \
			parser/parser_functions.c \
			minishell_utils.c \
			expander/envp_functions.c \
			expander/expander.c \
			builtins/utils.c \
			builtins/env.c \
			builtins/export.c \
			builtins/unset.c \
			builtins/pwd.c \
			builtins/exit.c \
			builtins/echo.c \
			builtins/cd.c \
			print_dir.c \
			signals/setup.c\
			get_data.c \
			parser/parser_utils.c \
			test/test_execute.c \

NAME_TEST = tester

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
OBJS_TEST = $(addprefix $(OBJ_DIR), $(SRCS_TEST:.c=.o))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

test: $(NAME_TEST)

$(NAME_TEST): $(OBJS_TEST) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS_TEST) -lreadline $(LIBFT_A) -o $(NAME_TEST) 

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT_A) -o $(NAME)

run: all
	valgrind --suppressions=includes/valgrind.sup --leak-check=full --show-leak-kinds=all ./minishell

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT)

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)
	rm -f $(NAME_TEST)

re: fclean all

.PHONY: all clean fclean re