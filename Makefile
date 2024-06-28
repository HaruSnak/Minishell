NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFTDIR = includes/libft
OBJ_DIR = obj/
SRC_DIR = srcs/
READLINE_PATH = /Home/pcardin/.local/Homebrew/opt/readline
CFLAGS = -I$(READLINE_PATH)/include
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

SRC_1 = srcs/minishell.c \

SRC_2 =	srcs/builtins/built_external.c \
	srcs/builtins/export_unset_built.c \
	srcs/builtins/out_cd_built.c \
	srcs/builtins/out_env_built.c \
	srcs/builtins/builtins_base.c \
	srcs/builtins/builtins_utils.c \
	srcs/errors/errors_operators.c \
	srcs/errors/errors.c \
	srcs/parsing/verify_operators.c \
	srcs/parsing/token_value.c \
	srcs/parsing/redirect_quote.c \
	srcs/parsing/quote.c \
	srcs/parsing/var_env.c \
    srcs/signals/signals.c \
	srcs/signals/signals_handle.c \
	srcs/signals/signals_heredoc.c \
	srcs/quote/quote.c srcs/utils/set_cmd_list.c \
	srcs/utils/function_utils.c srcs/utils/execution_utils2.c \
	srcs/utils/execution_utils.c srcs/execution/execution.c \
	srcs/execution/sub_exec.c srcs/execution/single_execution.c \
	srcs/redirections/redirection.c srcs/redirections/here_doc.c \
	srcs/utils/execution_utils3.c srcs/errors/free.c \
	srcs/utils/builtins_utils.c srcs/redirections/here_doc_bis.c \
	srcs/redirections/redirection_utils.c srcs/utils/free_utils.c \

OBJ_1 = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC_1))
OBJ_2 = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC_2))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

INCLUDE = -L $(LIBFTDIR) -lft -lreadline

.c.o:
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJ_1} ${OBJ_2}
	@echo "Compiling $(NAME)..."
	@make -C $(LIBFTDIR)
	@${CC} ${FLAGS} ${CFLAGS} ${LDFLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME} ${INCLUDE}
	@clear
	@echo "$(NAME) compiled successfully."

all: ${NAME}

clean:
	@echo "Cleaning libft object files..."
	@make -C $(LIBFTDIR) clean
	@echo "Cleaning project object files..."
	@${RM} ${OBJ_1} ${OBJ_2}
	@clear
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning libft..."
	@make -C $(LIBFTDIR) fclean
	@echo "Cleaning executable..."
	@${RM} ${NAME}
	@rm -rf ${OBJ_DIR}
	@clear
	@echo "Executable and libft cleaned."

re: fclean all

.PHONY: all clean fclean re