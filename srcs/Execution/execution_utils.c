
#include "../../includes/minishell.h"

void	extract_bin_paths(char **envp, struct s_parsing *parsing)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (!str)
	{
		str = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		i++;
	}
	parsing->paths = ft_split(str, ':');
	if (!parsing->paths)
	{
		perror("split");
		exit(0);
	}
}

int	is_cmd(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		return (FALSE);
	return (TRUE);
}

char	*find_cmd_path(struct s_parsing *parsing, int i)
{
	char	*path;
	int		accss;
	int		j;

	j = 0;
	while (j < 8)
	{
		printf("%s\n", parsing->paths[j]);
		path = ft_strjoin(parsing->paths[j], parsing->tkn[i]);
		if (!path)
			return (NULL);
		accss = access(path, X_OK);
		if (accss == 0 && is_cmd(path) == TRUE)
			return (path);
		else
			free(path);
		j++;
	}
	PL;
	return (NULL);
}

void	wait_pidz(struct s_parsing *parsing)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	while (parsing->pidz[i])
	{
		result = waitpid(parsing->pidz[i], &status, 0);
		if (result == -1)
			perror("waitpid");
		i++;
	}
}

void	check_err_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(0);
	}
}
