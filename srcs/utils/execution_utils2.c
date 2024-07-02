
#include "../../includes/minishell.h"

char	*find_small_path(char *cmd, char **envp)
{
	char	*path;
	char	**bin_paths;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && is_cmd(cmd) == TRUE)
		return (ft_strdup(cmd));
	bin_paths = ft_path_envp(envp);
	while (j < 8)
	{
		path = ft_strjoin_fs(bin_paths[j], cmd);
		if (!path)
			malloc_error("malloc : find small path");
		if (access(path, X_OK) == 0 && is_cmd(path) == TRUE)
		{
			free_strs(bin_paths);
			return (path);
		}
		else
			free(path);
		j++;
	}
	free_strs(bin_paths);
	return (NULL);
}

int	cmd_count(char **tkn, int *tkn_value, char **envp)
{
	char	*path;
	int		cmd;
	int		i;

	cmd = 0;
	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == CMD)
		{
			path = find_small_path(tkn[i], envp);
			if (path && access(path, X_OK) == 0)
			{
				cmd++;
				free(path);
			}
		}
	}
	return (cmd);
}

void	handle_input(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	line = NULL;
}
