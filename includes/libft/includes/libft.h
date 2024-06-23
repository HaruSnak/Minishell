/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:15:32 by shmoreno          #+#    #+#             */
/*   Updated: 2023/10/27 11:15:32 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include <sys/wait.h>

# define BUFFER_SIZE 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_pipex
{
	int		pipe[2];
	int		*status;
	int		file_source;
	int		file_dest;
	pid_t	children1;
	pid_t	children2;
}	t_pipex;

/*LIBFT functions*/
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_fs(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *str, const char *to_find, size_t size);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_strncmp(const char *str, const char *compare_str, int size);
int		ft_strlen(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num_elements, size_t element_size);
void	*ft_memchr(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*LIBFT BONUS*/
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

/*GET_NEXT_LINE*/
char	*get_next_line(int fd);

/*PRINTF*/
int		ft_putchar(char c);
void	ft_putstr(const char *s);
int		ft_putnbr_base(unsigned long long nb, const char *base);
int		ft_conv_char(va_list ap);
int		ft_conv_string(va_list ap);
int		ft_conv_pointer(va_list cp);
int		ft_conv_percent(void);
int		ft_conv_unsigned(va_list ap);
int		ft_conv_decimal(va_list ap);
int		ft_conv_hexa_low(va_list ap);
int		ft_conv_hexa_upper(va_list ap);
int		ft_printf(const char *format, ...);

// ERRORS FUNCTIONS
void	ft_free_char(char **str);
void	ft_errors(int value, char *filename);

// FIND PATH FUNCTIONS
int		ft_execve(char *argv[], char **envp);

// PIPEX FUNCTIONS
void	ft_children1(char **argv, char **envp, t_pipex *pipex);
void	ft_children2(char **argv, char **envp, t_pipex *pipex);

#endif
