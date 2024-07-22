/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:43 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 11:22:19 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_and_fetch_exit_value(pid_t pid, t_exec *data)
{
	int	status;
	
	if (!waitpid(pid, &status, 0))
	{
		perror("waitpid");
		exit(OUT_OF_MEMORY);
	}
	if (WIFEXITED(status))
		data->parsing_ptr->exit_value = WEXITSTATUS(status);
}

int	get_argv_len(int i, int *tkn_value)
{
	int	argv_len;

	argv_len = 0;
	while (tkn_value[i] && (tkn_value[i] == CMD || tkn_value[i] == ARG))
	{
		argv_len++;
		i++;
	}
	return (argv_len);
}

char	**set_argv(char *tkn[], int *tkn_value)
{
	char	**argv;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (tkn_value[++i] != CMD)
		;
	argv = malloc((get_argv_len(i, tkn_value) + 1) * sizeof(char *));
	malloc_error_dbl_ptr(argv, "malloc : set_argv");
	while (tkn_value[i] && (tkn_value[i] == ARG || tkn_value[i] == CMD))
	{
		argv[j] = ft_strdup(tkn[i]);
		malloc_error_ptr(argv[j], "malloc : set_argv");
		i++;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

char	**find_path_set_argv(t_exec *data, t_cmd_list *list,
	int *tkn_value, char **tkn)
{
	char	*cmd_path;
	char	**argv;
	int		i;

	i = -1;
	cmd_path = NULL;
	while (list && !list->is_cmd)
		list = list->next;
	while (tkn[++i])
	{
		if (tkn_value[i] == CMD)
			cmd_path = find_cmd_path(list, data, tkn[i]);
	}
	if (cmd_path)
	{
		free(cmd_path);
		argv = set_argv(tkn, tkn_value);
		return (argv);
	}
	else
		return (NULL);
}
