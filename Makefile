NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror #-g #-fsanitize=address
LIBFTDIR = includes/libft
OBJ_DIR = obj/
SRC_DIR = srcs/
READLINE_PATH = /Users/pcardin/.local/opt/readline
CFLAGS = -I$(READLINE_PATH)/include
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

SRC_1 = srcs/minishell.c \

SRC_2 =	srcs/commands/cmds_external.c \
	srcs/commands/export_unset_cmds.c \
	srcs/commands/out_cd_cmds.c \
	srcs/commands/out_env_cmds.c \
	srcs/errors/errors.c \
	srcs/parsing/parsing.c \
	srcs/parsing/verify_operators.c \
	srcs/parsing/token_value.c \
	srcs/parsing/redirect_quote.c \
	srcs/redirections/operator_redirects.c \
	srcs/signals/signals.c \
	srcs/quote/quote.c \
	srcs/utils/function_utils.c \
	srcs/execution/execution.c srcs/execution/child_exec.c \
	srcs/execution/single_execution.c srcs/execution/execution_utils.c \
	srcs/execution/execution_utils2.c \
	srcs/redirections/redirection.c srcs/redirections/here_doc.c \

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
	@echo "Cleaning object files..."
	@${RM} ${OBJ_1} ${OBJ_2}
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning executable..."
	@${RM} ${NAME}
	@rm -rf ${OBJ_DIR}
	@clear
	@echo "Executable cleaned."

re: fclean all

.PHONY: all clean fclean re