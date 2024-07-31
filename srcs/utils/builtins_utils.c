/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:43 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/31 16:59:19 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction qui split le path en fonction du /
// et qui renvoie le path sans le dernier element
// exemple: /home/user/42/minishell -> /home/user/42
char	*ft_split_input(char *input, char *c)
{
	char	**tmp_split;
	char	*tmp;
	char	*path;
	int		i;

	tmp_split = ft_split(input, '/');
	path = malloc(sizeof(char) * ft_strlen(input) + 1);
	malloc_error_ptr(path, "malloc : ft_split_input");
	path[0] = '\0';
	i = 0;
	while (tmp_split[i] != NULL)
	{
		if (tmp_split[i + 1] == NULL && c != NULL)
		{
			ft_free_d_ptr((void ***)&tmp_split);
			return (path);
		}
		tmp = ft_strjoin("/", tmp_split[i]);
		ft_strlcat(path, tmp, ft_strlen(path) + ft_strlen(tmp) + 1);
		free(tmp);
		i++;
	}
	ft_free_d_ptr((void ***)&tmp_split);
	return (path);
}

void	reset_std_out(t_parsing *parsing_ptr)
{
	if (dup2(parsing_ptr->stdout_cpy, STDOUT_FILENO) == -1)
	{
		perror("redir outfile");
		parsing_ptr->exit_value = DUP_FAILURE;
	}	
}

void	redirect_outfile(char *file, int redir, t_parsing *parsing_ptr)
{
	int	fd;

	if (redir == OUT)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir == APPEND)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("outfile");
		parsing_ptr->exit_value = PERMISSION_DENY;
		return ;
	}
	if (file && access(file, F_OK | R_OK) == -1)
	{
		perror("access");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("redir outfile");
		parsing_ptr->exit_value = DUP_FAILURE;
	}
	close(fd);
}

int	find_redir_file(int *tkn_value)
{
	int	i;

	i = -1;
	while (tkn_value[++i])
	{
		if (tkn_value[i] == OUT || tkn_value[i] == APPEND)
			return (i);
	}
	return (-1);
}

void	ft_check_redir(t_parsing *parsing)
{
	int	i;

	if (!ft_strncmp(parsing->tkn[0], "echo", 4)
		|| !ft_strncmp(parsing->tkn[0], "pwd", 3)
		|| !ft_strncmp(parsing->tkn[0], "env", 3))
	{
		i = find_redir_file(parsing->tkn_value);
		if (i == -1)
			return ;
		redirect_outfile(parsing->tkn[i + 1], parsing->tkn_value[i], parsing);
	}	
}
