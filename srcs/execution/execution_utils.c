
#include "../../includes/minishell.h"

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
		path = ft_strjoin_fs(parsing->path[j], parsing->tkn[i]);
		if (!path)
			return (NULL);
		accss = access(path, X_OK);
		if (accss == 0 && is_cmd(path) == TRUE)
			return (path);
		else
			free(path);
		j++;
	}
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
