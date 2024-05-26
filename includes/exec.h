#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

typedef struct s_parsing t_parsing;

typedef	struct	s_redir
{
	bool	redir_in;
	bool	redir_out;
	bool	here_doc;
	bool	append;
}	t_redir;

typedef struct	s_exec
{
	t_redir		*redir_ptr;
	t_parsing	*parsing_ptr;
	char		*outfile;
	int			fds[2];
	int			prevpipe;
	pid_t		*pidz;
}	t_exec;

typedef struct s_cmd_list
{
	char	*elem;
	bool	pipe;
	bool	cmd;
	bool	builtin;
	bool	arg;
	void	*next;
}	t_cmd_list;

// EXECUTION
void	execution(char *argv[], char **envp, t_parsing *parsing);
void	child_exec(char **envp,  t_exec **data, int i, char *path);
void	single_cmd_execution(t_exec **data, t_redir *s_redir,
			char **envp, char *tkn[]);

// Execution Utils
void	init_data(t_exec **data, t_redir **s_redir, t_parsing *parsing);
void	check_err_fork(pid_t pid);
void	wait_pidz(t_exec **data);
char	*find_cmd_path(t_exec **data, char *cmd);
char	**set_argv(char *tkn[], int *tkn_value);
char	**ft_path_envp(char **envp);
int		cmd_count(int *tkn_value);
int		is_cmd(char *path);
bool	there_is_pipeline(int *tkn_value);
t_cmd_list	*set_cmd_list(char **tkn, int *tkn_value);

// REDIRECTION
void	check_for_redirection(char **tkn, int *tkn_value,
			t_exec **data, t_redir **s_redir);
void	redirect_output(t_exec **data, t_redir *s_redir);

#endif