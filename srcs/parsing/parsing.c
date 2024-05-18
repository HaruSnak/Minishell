
#include "../../includes/minishell.h"

// Cette fonction sert à trouver le chemin d'accès d'une commande
// sous forme de tableau de chaînes de caractères.
char	**ft_path_envp(char **envp)
{
	int		i;
	char	*path;
	char	**path_f;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");
			break ;
		}
		i++;
	}
	path_f = ft_split(path, ':');
	free(path);
	return (path_f);
}

void	ft_interpret_envp(char **envp, struct s_parsing *parsing)
{
	int		i;
	char	*env_cmd;

	i = 0;
	if (parsing->tkn[1] != NULL
		&& ft_strchr(parsing->tkn[1], '$')
		&& ft_strnstr(parsing->tkn[0], "echo",
			ft_strlen(parsing->tkn[0])))
	{
		env_cmd = ft_substr(parsing->tkn[1], 1,
				ft_strlen(parsing->tkn[1]) - 1);
		while (envp[i] != NULL)
		{
			if (ft_strncmp(envp[i], env_cmd, ft_strlen(env_cmd)) == 0)
			{
				parsing->tkn[1] = ft_strdup(envp[i]
						+ ft_strlen(env_cmd) + 1);
				break ;
			}
			else
				parsing->tkn[1] = ft_strdup("");
			i++;
		}
	}
}

// Cette fonction sert à exécuter une commande.
// En reprenant les chemins d'acces trouvés par ft_path_envp,
// elle exécute la commande passée en paramètre.
int	ft_if_execve_access(struct s_parsing *parsing, char **envp, bool check)
{
	pid_t	pid;
	int		pipefd[2];
	//int 	fd;

	pipe(pipefd);
	// printf("%dpath: %s\n", __LINE__, parsing->cmd_path);
	if (access(parsing->cmd_path, F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (check)
			{
				if (ft_exec_cmd_redirects(parsing->test, parsing, parsing->k) == -1)
					return (0); // ---> A checker et rediriger directement depuis le parsing.
				/*else if (ft_exec_cmd_redirects(parsing->test, parsing, parsing->k) == 2)
				{
					printf("heredoc\n");
					fd = open("heredoc", O_RDONLY);
					dup2(fd, STDIN_FILENO);
					close(fd);
					close(pipefd[0]);
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
					printf("ICI\n");
				}*/
			}
			// printf("ICI2\n");
			ft_interpret_envp(envp, parsing);
			execve(parsing->cmd_path, parsing->tkn, envp);
			// printf("cmd_path--: %s\n", parsing->cmd_path);
			// printf("tkn[0]--: %s\n", parsing->tkn[0]);
			// printf("tkn[1]--: %s\n", parsing->tkn[1]);
			return (0);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (-1);
		}
		else
		{
			g_signal = 1;
			//close(pipefd[0]);
			//close(pipefd[1]);
			waitpid(pid, &parsing->status, 0);
			parsing->exit_value = WEXITSTATUS(parsing->status);
			g_signal = 0;
		}
	}
	else
		return (-1);
	return (0);
}

// Cette fonction sert à exécuter une commande.
// En reprenant les chemins d'acces trouvés par ft_path_envp,
// elle exécute la commande passée en paramètre.
int	ft_find_execve(char *argv[], char **envp, struct s_parsing *parsing, bool check)
{
	int		i;
	char	*tmp;

	i = -1;
	parsing->path = ft_path_envp(envp);
	if (parsing->path == NULL)
		return (-1);
	parsing->tkn = ft_split(argv[0], ' ');
	for (i = -1; parsing->tkn[++i] != NULL;)
		printf("tkn[%d]: %s\n", i, parsing->tkn[i]);
	i = -1;
	while (parsing->path[++i] != NULL)
	{
		tmp = ft_strjoin(parsing->path[i], "/");
		parsing->cmd_path = parsing->tkn[0];
		printf("path: %s\n", parsing->cmd_path);
		if (ft_strchr(parsing->tkn[0], '/') == NULL)
			parsing->cmd_path = ft_strjoin(tmp, parsing->tkn[0]);
		free(tmp);
		if (ft_if_execve_access(parsing, envp, check) == 0) // Change to multipipes execution
		{
			if (ft_strchr(parsing->tkn[0], '/') == NULL)
				free(parsing->cmd_path);
			ft_free_char(parsing->tkn);
			return (ft_free_char(parsing->path), 0);
		}
		if (ft_strchr(parsing->tkn[0], '/') == NULL)
			free(parsing->cmd_path);
	}
	ft_free_char(parsing->tkn);
	return (ft_free_char(parsing->path), -1);
}
