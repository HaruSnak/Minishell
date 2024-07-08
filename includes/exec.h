
#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define READ 0
# define WRIT 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define PERMISSION_DENY 1
# define OUT_OF_MEMORY 3
# define OPEN_FAILURE 5
# define FORK_FAILURE 6
# define DUP_FAILURE 7
# define PIPE_FAILURE 8

typedef struct s_parsing	t_parsing;

typedef struct s_redir
{
	bool	redir_in;
	bool	redir_denied;
	bool	redir_out;
	bool	here_doc;
	bool	append;
}	t_redir;

typedef struct s_exec
{
	t_redir		*redir_ptr;
	t_parsing	*parsing_ptr;
	char		**paths;
	char		*outfile;
	int			cmd_count;
	int			stdin_cpy;
	int			stdout_cpy;
	int			fds[2];
	int			check_signal;
	pid_t		*pidz;
	int			pid_i;
}	t_exec;

typedef struct s_cmd_list
{
	char				*elem;
	int					index;
	bool				absolute_path;
	bool				is_cmd;
	bool				cmd_found;
	bool				pipe;
	bool				arg;
	struct s_cmd_list	*next;
}	t_cmd_list;

// EXECUTION
bool		execution(char *argv[], char **envp, t_parsing *parsing);
void		child_exec(char **envp, t_exec *data, t_cmd_list *list, char *path);
void		parent_exec(t_exec *data);
void		single_cmd_execution(t_cmd_list *list, t_exec *data, char **envp, char *tkn[]);
char		**set_argv(char *tkn[], int *tkn_value);
char		**ft_path_envp(char **envp);
void		init_data(t_exec *data, t_redir *s_redir,
				t_parsing *parsing, char **envp);
void		ft_handle_echo(t_parsing *data, char *tkn[], int *tkn_value, int i);

// Execution Utils
bool		no_such_file(t_parsing *data, char *tkn[], int *tkn_value);
void		check_err_fork(pid_t pid);
void		malloc_error(char *str);
void		wait_pidz(t_exec *data);
void		handle_input(void);
void		handle_input(void);
void		reset_and_free(t_exec *data);
void		free_data(t_exec *data);
void		free_list(t_cmd_list *list);
void		free_single_list(t_cmd_list *list);
void		free_strs(char **strs);

// LISTS
t_cmd_list	*set_cmd_list(t_exec *data, char **tkn, int *tkn_value);
char		**set_argv_lst(t_cmd_list *list, char *cmd);
char		*find_cmd_path(t_cmd_list *list, t_exec *data, char *cmd);
int			cmd_count(char **tkn, int *tkn_value, char **envp);
bool		there_is_pipeline(int *tkn_value);

// REDIRECTION
int			check_for_redirection(t_exec *data, char **envp);
void		redirect_output(t_exec *data, t_redir *s_redir);
void		heredoc_handling(t_exec *data, char *eof, char **g_env);
void		ft_dup_heredoc(int heredoc);
int			ft_g_signal_exit(char *line, int heredoc);
void		ft_write_heredoc(int heredoc, char *line,
				char **g_env, t_exec *data);
int			ft_line_null_msg(char *line, int count);
char		*ft_var_env(char **envp, char *line);
void		reset_outfile(t_exec *data, int i);
void		print_output(int fd);

// Redirection Utils
void		ft_delete_file_heredoc(void);
void		redirect_infile(t_exec *data, int *fd, char *path);

#endif