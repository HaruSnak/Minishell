
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
# include "libft/includes/libft.h"
# include "exec.h"

# define PL fprintf(stderr, "file: %s line: %d pid: %i\n", __FILE__, __LINE__, getpid())
# define PI(s, x) fprintf(stderr, "%s: %d\n", (s), (x));
# define PS(s, x) fprintf(stderr, "%s: %s\n", (s), (x));

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

extern int g_signal;

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
	char	**tmp_env;
	char	*tkn_cpy;
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
int		ft_find_execve(char **envp, t_parsing *parsing);
int		ft_if_execve_access(t_parsing *parsing, char **envp);
char	*ft_separe_operator(char *input);
char	*ft_replace_espace(char *input, t_parsing *parsing);
void	ft_delete_espace(t_parsing *parsing);
void	ft_interpret_envp(char **envp, t_parsing *parsing);

// SIGNALS FUNCTIONS
void	ft_signal_handler(int signo);

// COMMANDS FUNCTIONS
int		ft_external_cmds(char **input, t_parsing *parsing, char **envp);
char	*ft_split_input(char *input, char *c);
int		ft_setenv(char **envp, t_parsing *parsing);

// COMMANDS CD FUNCTIONS
void	ft_handle_cd_home(t_parsing *parsing, char **envp);
void	ft_handle_cd_previous(t_parsing *parsing, char **envp);
void	ft_handle_cd_root(t_parsing *parsing, char **envp);
void	ft_handle_cd_oldpwd(t_parsing *parsing,
			char **envp, char *path, char *oldpwd);
void	ft_handle_cd_path(t_parsing *parsing, char **envp, char **input);

// COMMANDS EXPORT UNSET FUNCTIONS
int		ft_external_cmds_bis(char **input,
			t_parsing *parsing, char **envp);

// COMMANDS EXTERNALS FUNCTIONS
int		ft_handle_empty_cmd(char **input);
int		ft_handle_exit(char **input, t_parsing *parsing);
int		ft_handle_echo(char *input, t_parsing *parsing);

// REDIRECTION FUNCTIONS SHELL
int		ft_handle_verify(char **input, t_parsing *parsing, char **envp);
int		ft_exec_cmd_redirects(char **tmp, t_parsing *parsing);

// ERRORS FUNCTIONS
void	ft_end_verify(char **input, t_parsing *parsing);
void	ft_free_and_compact(char **str, int index, int size);
void	free_data(t_exec *data, t_redir *s_redir);
void	ft_free_d_ptr(void ***ptr);

// QUOTE FUNCTIONS SHELL
int		ft_check_quote(char **envp, t_parsing *parsing);

// UTILS FUNCTIONS
int		ft_count_index(char **input);
int		ft_strlen_quote(char *str, char c, int i);

#endif