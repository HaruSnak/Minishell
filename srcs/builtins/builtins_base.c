/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:19 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/22 10:46:37 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_echo(t_parsing *data, char *tkn[], int *tkn_value, int i)
{
	int	nl;

	nl = 1;
	while (tkn[++i] && tkn_value[i] == ARG)
	{
		if (!ft_strncmp(tkn[i], "-n", 2))
			nl = 0;
		else if (tkn_value[i + 1] == ARG)
			printf("%s ", tkn[i]);
		else if (tkn_value[i + 1] != ARG)
			printf("%s", tkn[i]);
	}
	if (nl)
		printf("\n");
	data->exit_value = 0;
}

int	ft_verify_many_arg(t_parsing *parsing)
{
	if (parsing->tkn[1] != NULL && parsing->tkn[2] != NULL
		&& parsing->tkn_value[2] == ARG)
		return (printf("minishell: cd: too many arguments\n"),
			parsing->exit_value = 1, 1);
	return (0);
}

void	ft_cmd_cd(char **envp, t_parsing *parsing)
{
	char		*path;
	char		*oldpwd;

	if (ft_verify_many_arg(parsing) == 1)
		return ;
	path = NULL;
	oldpwd = NULL;
	if ((!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
			&& parsing->tkn[1] == NULL)
		|| (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
			&& !ft_strncmp(parsing->tkn[1], "~", ft_strlen(parsing->tkn[1]))))
		ft_handle_cd_home(parsing, envp);
	else if (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
		&& !ft_strncmp(parsing->tkn[1], "..", ft_strlen(parsing->tkn[1])))
		ft_handle_cd_previous(parsing, envp);
	else if (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
		&& !ft_strncmp(parsing->tkn[1], "/", ft_strlen(parsing->tkn[1])))
		ft_handle_cd_root(parsing, envp);
	else if (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
		&& !ft_strncmp(parsing->tkn[1], "-", ft_strlen(parsing->tkn[1])))
		ft_handle_cd_oldpwd(parsing, envp, path, oldpwd);
	else if (!ft_strncmp(parsing->tkn[0], "cd", 3) && parsing->tkn[1] != NULL)
		ft_handle_cd_path(parsing, envp);
}

int	builtins_exec_bis(t_parsing *parsing, char **envp)
{
	if (!ft_strncmp(parsing->tkn[0], "export", 6))
	{
		ft_handle_export(parsing, envp);
		return (0);
	}
	else if (!ft_strncmp(parsing->tkn[0], "unset", 5))
	{
		ft_handle_unset(parsing, envp);
		return (0);
	}
	else if (!ft_strncmp(parsing->tkn[0], "clear", 5))
	{
		ft_cmd_clear();
		return (0);
	}
	return (-1);
}

int	builtins_exec(t_parsing *parsing, char **envp)
{
	if (!ft_strncmp(parsing->tkn[0], "exit", 4))
	{
		ft_handle_exit(parsing);
		return (0);
	}
	else if (!ft_strncmp(parsing->tkn[0], "cd", 2))
	{
		ft_cmd_cd(envp, parsing);
		return (0);
	}
	else if ((!ft_strncmp(parsing->tkn[0], "echo", 4))
		&& !there_is_pipeline(parsing->tkn_value) && !parsing)
	{
		ft_handle_echo(parsing, parsing->tkn, parsing->tkn_value, 0);
		return (0);
	}
	else if (builtins_exec_bis(parsing, envp) == 0)
		return (0);
	return (-1);
}
