


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

void	ft_interpret_envp(char **envp, t_parsing *parsing)
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
int	ft_if_execve_access(t_parsing *parsing, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	//int 	fd;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (ft_exec_cmd_redirects(parsing->tkn, parsing) == -1)  // ICI ATTENTION, FONCTION QUI DOIT COMPORTER UN INDEX QUE J'AI SUPP POUR LE MOMENT
			return (0);
		/*else if (ft_exec_cmd_redirects(parsing->test, parsing) == 2)
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
		printf("ICI2\n");
		if (access(parsing->cmd_path, F_OK) == 0)
		{
			ft_interpret_envp(envp, parsing);
			execve(parsing->cmd_path, parsing->tkn, envp);
		}
		else
			return (-1);
		printf("cmd_path: %s\n", parsing->cmd_path);
		printf("cmd_extract[0]: %s\n", parsing->tkn[0]);
		printf("cmd_extract[1]: %s\n", parsing->tkn[1]);
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
	return (0);
}

// Cette fonction sert à exécuter une commande.
// En reprenant les chemins d'acces trouvés par ft_path_envp,
// elle exécute la commande passée en paramètre.
int	ft_find_execve(char **envp, t_parsing *parsing)
{
	int		i;
	int		k;
	char	*tmp;

	i = -1;
	k = -1;
	parsing->path = ft_path_envp(envp);
	if (parsing->path == NULL)
		return (-1);
	while (parsing->tkn[++k] != NULL)
	{
		if (parsing->tkn_value[k] == CMD)
		{
			while (parsing->path[++i] != NULL)
			{
				printf("path[%d]: %s\n", i, parsing->path[i]);
				tmp = ft_strjoin(parsing->path[i], "/");
				parsing->cmd_path = parsing->tkn[0];
				//printf("cmd_extract[0]: %s\n", parsing->tkn[0]);
				if (ft_strchr(parsing->tkn[0], '/') == NULL)
					parsing->cmd_path = ft_strjoin(tmp, parsing->tkn[0]);
				free(tmp);
				if (ft_if_execve_access(parsing, envp) == 0)
				{
					if (ft_strchr(parsing->tkn[0], '/') == NULL)
						free(parsing->cmd_path);
					ft_free_d_ptr((void ***)&parsing->tkn);
					return (ft_free_d_ptr((void ***)&parsing->path), 0);
				}
				if (ft_strchr(parsing->tkn[0], '/') == NULL)
					free(parsing->cmd_path);
			}
		}
		i = -1;
	}
	ft_free_d_ptr((void ***)&parsing->tkn);
	return (ft_free_d_ptr((void ***)&parsing->path), -1);
}
