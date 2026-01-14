NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I.
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a

SRCS = minishell.c \
		lexer/lexer.c \
		lexer/token_functions.c \
		lexer/free_tokens.c \
		parser/parser.c

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR), $(SRCS_BONUS:.c=.o))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT_A) -o $(NAME)

run: all
	valgrind --suppressions=valgrind.sup --leak-check=full --show-leak-kinds=all ./minishell

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT)

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re