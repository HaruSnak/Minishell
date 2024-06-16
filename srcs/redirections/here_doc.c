
#include "../../includes/minishell.h"

void	ft_delete_file_heredoc()
{
	pid_t	pid;
	char	**envp;
	int		status;

	envp = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", (char *[]){"rm", "obj/srcs/redirections/heredoc.txt", NULL}, envp);
	waitpid(pid, &status, 0);
}

char	*ft_find_null(char *line, char *env_var, int *i)
{
	char	*tmp_after;
	char	*tmp_before;

	tmp_after = ft_substr(line, 0, (*i));
	tmp_before = ft_strjoin(tmp_after,
			line + ft_strlen(tmp_after) + ft_strlen(env_var) + 1);
	free(line);
	line = ft_strdup(tmp_before);
	free(tmp_after);
	free(tmp_before);
	(*i) -= 1;
	return (line);
}

// Find the environment variable in the input
// Replace the environment variable with the value in the input
char	*ft_find_var_env(char *line, char **envp, int *i, char *env_var)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp_before;
	int		p;

	p = -1;
	while (envp[++p] != NULL)
	{
		if (ft_strncmp(envp[p], env_var, ft_strlen(env_var)) == 0)
		{
			tmp_after = ft_substr(line, 0, (*i));
			tmp_env = ft_strjoin(tmp_after, envp[p] + ft_strlen(env_var) + 1);
			tmp_before = ft_strjoin(tmp_env, line + ft_strlen(tmp_env) + 1);
			free(line);
			line = ft_strdup(tmp_before);
			free(tmp_after);
			free(tmp_env);
			free(tmp_before);
			p = -1;
			break ;
		}
	}
	if (p != -1)
		line = ft_find_null(line, env_var, i);
	return (line);
}

char	*ft_var_env(char **envp, char *line)
{
	char	*env_var;
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			env_var = ft_substr(line, i + 1,
					ft_strlen_quote(line, ' ', i + 1));
			line = ft_find_var_env(line, envp, &i, env_var);
			free(env_var);
		}
	}
	return (line);
}

void	heredoc_handling(char *eof, char **g_env)
{
	char	*line;
	int		heredoc;

	heredoc = open("obj/srcs/redirections/heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777); /// VERIF FLAGS
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, eof, ft_strlen(line)) == 0)
			break ;
		line = ft_var_env(g_env, line);
		write(heredoc, line, ft_strlen(line));
		write(heredoc, "\n", 1);
		free(line);
	}
	close(heredoc);
	heredoc = open("obj/srcs/redirections/heredoc.txt", O_CREAT | O_RDONLY, 0777); /// VERIF FLAGS
	if (dup2(heredoc, STDIN_FILENO) == -1)
	{
		perror("redir_heredoc");
		close(heredoc);
		return ; // error handling
	}
	close(heredoc);
}
