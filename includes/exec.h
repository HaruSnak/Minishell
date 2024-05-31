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

// EXECUTION
void	execution(char *argv[], char **envp, t_parsing *parsing);
void	child_exec(char **envp,  t_exec **data, int i, char *path);
void	single_cmd_execution(t_exec **data, t_redir *s_redir,
			char **envp, char *tkn[]);

// Execution Utils
char	**ft_path_envp(char **envp);
void	wait_pidz(t_exec **data);
void	check_err_fork(pid_t pid);
char	*find_cmd_path(t_exec **data, char *cmd);
int		is_cmd(char *path);
void	init_data(t_exec **data, t_redir **s_redir, t_parsing *parsing);
int		cmd_count(int *tkn_value);
bool	there_is_pipeline(int *tkn_value);

// REDIRECTION
void	check_for_redirection(char **tkn, int *tkn_value,
			t_exec **data, t_redir **s_redir);
void	redirect_output(t_exec **data, t_redir *s_redir);

#endif