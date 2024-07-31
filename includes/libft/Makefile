NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = includes/obj/

FILES = mem/ft_memset.c mem/ft_bzero.c mem/ft_memcpy.c mem/ft_memmove.c str/ft_striteri.c \
        mem/ft_memchr.c mem/ft_memcmp.c str/ft_strlen.c str/ft_strlcpy.c str/ft_strlcat.c \
        str/ft_strchr.c str/ft_strrchr.c str/ft_strnstr.c str/ft_strncmp.c conv/ft_atoi.c \
        char/ft_isalpha.c char/ft_isdigit.c char/ft_isalnum.c char/ft_isascii.c char/ft_isprint.c \
        char/ft_toupper.c char/ft_tolower.c mem/ft_calloc.c str/ft_strdup.c str/ft_substr.c \
        str/ft_strjoin.c str/ft_strtrim.c str/ft_split.c conv/ft_itoa.c str/ft_strmapi.c \
        put/ft_putchar_fd.c put/ft_putstr_fd.c put/ft_putendl_fd.c put/ft_putnbr_fd.c \
        gnl/get_next_line.c printf/ft_conv_primary.c str/ft_strjoin_fs.c \
        printf/ft_conv_suit.c printf/ft_printf.c put/ft_putchar.c put/ft_putnbr.c \
        put/ft_putstr.c str/ft_split_tkn.c \

BONUS_FILES = lst/ft_lstnew_bonus.c lst/ft_lstadd_front_bonus.c lst/ft_lstsize_bonus.c lst/ft_lstlast_bonus.c \
              lst/ft_lstadd_back_bonus.c lst/ft_lstdelone_bonus.c lst/ft_lstclear_bonus.c lst/ft_lstiter_bonus.c \
              lst/ft_lstmap_bonus.c \

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(FILES))
BONUS_OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(BONUS_FILES))

RM = rm -rf

vpath %.c $(sort $(dir $(FILES)))

$(OBJ_DIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $(OBJ)

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

normi: $(FILES)
	norminette $(FILES)

normib: $(BONUS_FILES)
	norminette $(BONUS_FILES)
.PHONY: all clean fclean re normi normib bonus
