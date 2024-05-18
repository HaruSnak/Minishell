
#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PL
#  define PL printf("file:%s line: %d\n", __FILE__, __LINE__)
# endif

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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"

# define TRUE 1
# define FALSE 0

extern int g_signal;

struct s_parsing
{
	char	**tkn;
	// char	**tkn_value;
	char	**paths;
	char	**tmp_env;
	char	**test;
	char	*n_senv;
	char	*v_senv;
	char	*cmd_path;
	char	*input;
	char	*pwd;
	char	*tmp;
	int		blocking_cmd;
	int		exit_value;
	int		status;
	int		k;

	char	*infile;
	char	*outfile;
	int		fds[2];
	int		prevpipe;
	pid_t	*pidz;
};

// typedef struct s_exec
// {
// 	struct s_parsing	s_prsng_ptr;
// 	char				**cmd_ptr;
// 	int					fds[2];
// 	int					prevpipe;
// 	pid_t				*pidz;
// }	t_exec;

// NEW EXEC

void	execution(char *argv[], char **envp, struct s_parsing *parsing,
			bool check);
void	child_exec(char **envp,  struct s_parsing *parsing, int i, char *path);
void	check_err_fork(pid_t pid);
void	wait_pidz(struct s_parsing *parsing);
void	extract_bin_paths(char **envp, struct s_parsing *parsing);

// PARSING FUNCTIONS 

char	*find_cmd_path(struct s_parsing *parsing, int i);
// int		ft_find_execve(char *argv[], char **envp, struct s_parsing *parsing,
			// bool check);
int		ft_if_execve_access(struct s_parsing *parsing, char **envp, bool check);

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
int		ft_exec_cmd_redirects(char **tmp, struct s_parsing *parsing,
			int i);
void	ft_condition_operator(char *input, int *i, int *k, char *tmp);

#endif
