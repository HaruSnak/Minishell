/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_cd_built_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:31:38 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/24 15:47:48 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle the cd command when the previous directory is the root
// out_cd_built.c
void	ft_cd_previous_bis(t_parsing *parsing, char **envp, char *path)
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
