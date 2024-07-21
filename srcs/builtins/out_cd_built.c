/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_cd_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:40:05 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 17:52:01 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_cd_home(t_parsing *parsing,
	char **envp)
{
	if (chdir(getenv("HOME")) == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = ft_strdup(getenv("PWD"));
		malloc_error_ptr(parsing->v_senv, "malloc : ft_handle_cd_home PWD");
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->n_senv = "PWD";
		parsing->v_senv = ft_strdup(getenv("HOME"));
		malloc_error_ptr(parsing->v_senv, "malloc : ft_handle_cd_home HOME");
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: ~: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_previous(t_parsing *parsing, char **envp)
{
	char	*path;

	if (chdir("..") == 0)
	{
		parsing->v_senv = ft_strdup(getenv("PWD"));
		malloc_error_ptr(parsing->v_senv, "malloc : ft_handle_cd_previous");
		if (ft_strncmp(parsing->v_senv, "/", ft_strlen(parsing->v_senv)) == 0)
		{
			path = ft_strdup("/");
			malloc_error_ptr(path, "malloc : ft_handle_cd_previous");
		}
		else
			path = ft_split_input(parsing->v_senv, "/");
		parsing->n_senv = "OLDPWD";
		(ft_setenv(envp, parsing), free(parsing->v_senv));
		parsing->n_senv = "PWD";
		parsing->v_senv = ft_strdup(path);
		malloc_error_ptr(parsing->v_senv, "malloc : ft_handle_cd_previous");
		(ft_setenv(envp, parsing), free(parsing->v_senv), free(path));
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: ..: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_root(t_parsing *parsing,
	char **envp)
{
	if (chdir("/") == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = getenv("PWD");
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = "/";
		ft_setenv(envp, parsing);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: /: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_oldpwd(t_parsing *parsing,
	char **envp, char *path, char *oldpwd)
{
	if (chdir(getenv("OLDPWD")) == 0)
	{
		path = ft_strdup(getenv("OLDPWD"));
		malloc_error_ptr(path, "malloc : ft_handle_cd_oldpwd");
		oldpwd = ft_strdup(getenv("PWD"));
		malloc_error_ptr(oldpwd, "malloc : ft_handle_cd_oldpwd");
		parsing->pwd = path;
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = oldpwd;
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = path;
		ft_setenv(envp, parsing);
		free(path);
		free(oldpwd);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n", oldpwd);
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_path(t_parsing *parsing, char **envp)
{
	if (chdir(parsing->tkn[1]) == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = parsing->pwd;
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = malloc(sizeof(char) * ft_strlen(parsing->tkn[1]) + 1);
		malloc_error_ptr(parsing->v_senv, "malloc : ft_handle_cd_path");
		getcwd(parsing->v_senv, ft_strlen(parsing->tkn[1]) + 1);
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n",
			parsing->tkn[1]);
		parsing->exit_value = 1;
	}
}
