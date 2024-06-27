

#include "../../includes/minishell.h"

void	ft_cmd_clear(void)
{
	printf("\033[H\033[J");
}

int	ft_cmd_cd(char **envp, t_parsing *parsing)
{
	char		*path;
	char		*oldpwd;

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
	return (0);
}

int	builtins_exec_bis(t_parsing *parsing, char **envp)
{
	if (ft_strncmp(parsing->tkn[0], "export", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_handle_export(parsing, envp);
		return (0);
	}
	if (ft_strncmp(parsing->tkn[0], "unset", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_handle_unset(parsing, envp);
		return (0);
	}
	if (ft_strncmp(parsing->tkn[0], "clear", ft_strlen(parsing->tkn[0])) == 0)
	{
		ft_cmd_clear();
		return (0);
	}
	return (-1);
}

int	builtins_exec(t_parsing *parsing, char **envp)
{
	if (!ft_strncmp(parsing->tkn[0], "exit", ft_strlen(parsing->tkn[0])))
	{
		ft_handle_exit(parsing);
		return (0);
	}
	if (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
		&& ft_cmd_cd(envp, parsing) == 0)
	{
		return (0);
	}
	if (builtins_exec_bis(parsing, envp) == 0)
		return (0);
	return (-1);
}
