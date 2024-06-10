
#include "../../includes/minishell.h"

void	redirect_heredoc(char *path, char *argv[], char **envp)
{
	int		fd_out;

	fd_out = open("heredoc.txt", O_RDWR, 0777);
	if (fd_out == -1)
	{
		perror("outfile");
		return ;
	}
	if (dup2(fd_out, STDIN_FILENO) == -1)
	{
		close(fd_out);
		perror_exit("dup2");
	}
	execve(path, argv, envp);
	close(fd_out);
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

int	heredoc_handling(char *eof, char **g_env)
{
	char		*line;
	int			heredoc;

	heredoc = open("heredoc.txt",
				O_CREAT | O_RDWR | O_TRUNC, 0777); /// VERIF FLAGS
	line = readline(">");
	while (1)
	{
		if (ft_strncmp(line, eof, ft_strlen(line)) == 0)
			break ;
		line = ft_var_env(g_env, line);
		write(heredoc, line, ft_strlen(line));
		write(heredoc, "\n", 1);
		free(line);
		line = readline(">");
	}
	close(heredoc);
	return (heredoc);
}
