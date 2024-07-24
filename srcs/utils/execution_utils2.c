/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:59 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 11:11:21 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		return (FALSE);
	return (TRUE);
}

char	*find_small_path(char *cmd, char **envp)
{
	char	*path;
	char	**bin_paths;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && is_cmd(cmd) == TRUE)
		return (ft_strdup(cmd));
	bin_paths = ft_path_envp(envp);
	if (!bin_paths)
		return (NULL);
	while (j < 8)
	{
		path = ft_strjoin_fs(bin_paths[j], cmd);
		malloc_error_ptr(path, "malloc : find small path");
		if (access(path, X_OK) == 0 && is_cmd(path) == TRUE)
			return (free_strs(bin_paths), path);
		else
			free(path);
		j++;
	}
	free_strs(bin_paths);
	return (NULL);
}

char	*find_cmd_path(t_cmd_list *list, t_exec *data, char *cmd)
{
	char	*path;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && is_cmd(cmd) == TRUE)
	{
		list->absolute_path = TRUE;
		return (ft_strdup(cmd));
	}
	while (j < 8)
	{
		path = ft_strjoin_fs(data->paths[j], cmd);
		malloc_error_ptr(path, "malloc : find cmd path");
		if (access(path, X_OK) == 0 && is_cmd(path) == TRUE)
			return (path);
		else
			free(path);
		j++;
	}
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

// Reset input when the next command is not found
void	handle_input(void)
{
	char	*line;

	if (STDIN_FILENO)
		line = get_next_line(STDIN_FILENO);
	else
		return ;
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	line = NULL;
}
