NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = includes/libft/
OBJ_DIR = obj/
SRC_DIR = srcs/
READLINE_PATH = /Users/shmoreno/.local/opt/readline
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
    srcs/redirections/operator_redirects.c \
    srcs/signals/signals.c \

OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}

INCLUDE = -L $(LIBFTDIR) -lft

.c.o:
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJ_1} ${OBJ_2}
	@echo "Compiling $(NAME)..."
	@make -C $(LIBFTDIR)
	@${CC} ${FLAGS} ${CFLAGS} ${LDFLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME} ${INCLUDE}
	@echo "$(NAME) compiled successfully."

all: ${NAME}

clean:
	@echo "Cleaning object files..."
	@${RM} ${OBJ_1} ${OBJ_2} ${NAME}
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning executable..."
	@${RM} ${NAME}
	@echo "Executable cleaned."

re: fclean all

.PHONY: all clean fclean re