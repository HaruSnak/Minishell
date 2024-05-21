

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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"

# define IN 0
# define OUT 1
# define APPEND 2
# define HEREDOC 3
# define PIPE 4
# define CMD 5
# define ARG 6
# define FILE 7

extern int g_signal;

struct s_parsing
{
	char	**tkn;
	int		**tkn_value;
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
};

// PARSING FUNCTIONS 
int		ft_find_execve(char **envp, struct s_parsing *parsing);
int		ft_if_execve_access(struct s_parsing *parsing, char **envp);
int		ft_token_value(struct s_parsing *parsing);
char	*ft_separe_operator(char *input);

// SIGNALS FUNCTIONS
void	ft_signal_handler(int signo);

// COMMANDS FUNCTIONS
int		ft_external_cmds(char **input, struct s_parsing *parsing, char **envp);
char	*ft_split_input(char *input, char *c);
int		ft_setenv(char **envp, struct s_parsing *parsing);

// COMMANDS CD FUNCTIONS
void	ft_handle_cd_home(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_previous(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_root(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_oldpwd(struct s_parsing *parsing,
			char **envp, char *path, char *oldpwd);
void	ft_handle_cd_path(struct s_parsing *parsing, char **envp, char **input);

// COMMANDS EXPORT UNSET FUNCTIONS
int		ft_external_cmds_bis(char **input,
			struct s_parsing *parsing, char **envp);

// COMMANDS EXTERNALS FUNCTIONS
int		ft_handle_empty_cmd(char **input);
int		ft_handle_exit(char **input, struct s_parsing *parsing);
int		ft_handle_echo(char *input, struct s_parsing *parsing);

// REDIRECTION FUNCTIONS SHELL
int		ft_handle_verify(char **input, struct s_parsing *parsing, char **envp);
int		ft_exec_cmd_redirects(char **tmp, struct s_parsing *parsing);

// ERRORS FUNCTIONS
void	ft_end_verify(char **input, struct s_parsing *parsing);
void	ft_free_and_compact(char **str, int index, int size);
void	ft_free_d_ptr(void ***ptr);

// QUOTE FUNCTIONS SHELL

// UTILS FUNCTIONS
int		ft_count_index(char **input);
char	*ft_replace_espace(char *input, struct s_parsing *parsing);
void	ft_delete_espace(struct s_parsing *parsing);

#endif