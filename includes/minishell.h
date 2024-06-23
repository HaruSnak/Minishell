
#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "libft/includes/libft.h"
# include "exec.h"

# define PL fprintf(stderr, "file: %s line: %d pid: %i\n", __FILE__, __LINE__, getpid())
# define PI(x) fprintf(stderr, "PI: %d\n", (x));
# define PI2(s, x) fprintf(stderr, "%s: %d\n", (s), (x));
# define PS(x) fprintf(stderr, "PS: %s\n", (x));
# define PS2(s, x) fprintf(stderr, "%s: %s\n", (s), (x));

# define PROMPT "\001\033[0;32m\002minishell\001\033[0m\002\xF0\x9F\x90\x9A "

# define TRUE 1
# define FALSE 0

# define IN 1
# define OUT 2
# define APPEND 3
# define HEREDOC 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define FILE 8

typedef struct s_quote
{
	bool	check_s;
	bool	check_d;
	int		p;
}	t_quote;

typedef struct s_parsing
{
	char	**tkn;
	int		*tkn_value;
	char	**path;
	char	**tmp_env; // modifier name
	char	**tmp_setenv;
	char	*tkn_cpy; //delete ?
	char	*n_senv;
	char	*v_senv;
	char	*cmd_path;
	char	*input;
	char	*pwd;
	char	*tmp;
	int		exit_value;
	int		status;
	t_quote	*quote;
}	t_parsing;

// PARSING FUNCTIONS 
char	*ft_separe_operator(char *input);
char	*ft_replace_espace(char *input, t_parsing *parsing);
void	ft_delete_espace(t_parsing *parsing);
void	ft_interpret_envp(char **envp, t_parsing *parsing);
int		ft_token_value(t_parsing *parsing);
int		ft_check_odd_quote(char *input);
int		ft_return_value_echo(t_parsing *parsing, int k);

// SIGNALS FUNCTIONS
void	ft_signal_handler(int signo);
void	ft_signal_quit(int signum);
void	ft_signal_return(int signum);
void	ft_init_signal(struct sigaction *sa, struct sigaction *sa_quit);
void	ft_init_signal_block(void);

// BUILTINS FUNCTIONS
int		builtins_exec(t_parsing *parsing, char **envp);
char	*ft_split_input(char *input, char *c);
int		ft_setenv(char **envp, t_parsing *parsing);

// BUILTINS CD FUNCTIONS
void	ft_handle_cd_home(t_parsing *parsing, char **envp);
void	ft_handle_cd_previous(t_parsing *parsing, char **envp);
void	ft_handle_cd_root(t_parsing *parsing, char **envp);
void	ft_handle_cd_oldpwd(t_parsing *parsing,
			char **envp, char *path, char *oldpwd);
void	ft_handle_cd_path(t_parsing *parsing, char **envp);

// BUILTINS EXPORT UNSET FUNCTIONS
int		ft_handle_unset(t_parsing *parsing, char **envp);
void	ft_handle_export(t_parsing *parsing, char **envp);

// BUILTINS EXTERNALS FUNCTIONS
int		ft_handle_empty_cmd(char **input);
int		ft_handle_exit(t_parsing *parsing);
bool	is_builtins(char *cmd, t_parsing *data, char **envp);

// REDIRECTION FUNCTIONS SHELL
int		ft_handle_verify(char **input, t_parsing *parsing, char **envp);

// ERRORS FUNCTIONS
void	ft_end_verify(t_parsing *parsing);
void	ft_free_and_compact(char **str, int index, int size);
void	ft_free_data(t_exec *data);
void	ft_free_d_ptr(void ***ptr);
int		ft_error_operator(t_parsing *parsing);

// QUOTE FUNCTIONS SHELL
int		ft_check_quote(char **envp, t_parsing *parsing);

// UTILS FUNCTIONS
int		ft_count_index(char **input);
int		ft_strlen_quote(char *str, char c, int i);

#endif