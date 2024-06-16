
#include "../../includes/minishell.h"

void	ft_setenv_last(char **envp, t_parsing *parsing, int i)
{
	char				*tmp_equal;
	static int			j;

	if (parsing->tmp_env == NULL)
		parsing->tmp_env = malloc(sizeof(char *) * 100);
	//if ()
	tmp_equal = ft_strjoin(parsing->n_senv, "=");
	parsing->tmp_env[j] = ft_strjoin(tmp_equal, parsing->v_senv);
	parsing->tmp_env[j + 1] = NULL;
	envp[i + 1] = parsing->tmp_env[j];
	envp[i + 2] = NULL;
	j++;
	free(tmp_equal);
}

int	ft_setenv(char **envp, t_parsing *parsing)
{
	char	*tmp;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], parsing->n_senv,
				ft_strlen(parsing->n_senv)) == 0)
		{
			tmp = ft_strnstr(envp[i], "\n", ft_strlen(envp[i]));
			if (tmp != NULL)
				ft_memmove(envp[i], tmp + 1, ft_strlen(tmp) - 1);
			tmp = ft_strjoin(parsing->n_senv, "=");
			parsing->tmp = ft_strjoin(tmp, parsing->v_senv);
			ft_strlcpy(envp[i], parsing->tmp, ft_strlen(parsing->tmp) + 1);
			free(parsing->tmp);
			free(tmp);
			return (0);
		}
		else if (envp[i + 1] == NULL)
			return (ft_setenv_last(envp, parsing, i), 0);
	}
	for (int k = 0; k < i; k++)
		printf("envp[%d]: %s\n", k, envp[k]);
	return (-1);
}

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
	path = malloc(sizeof(char) * ft_strlen(input) + 100);
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

int	ft_external_cmds(t_parsing *parsing, char **envp)
{
	if (!ft_strncmp(parsing->tkn[0], "exit", ft_strlen(parsing->tkn[0])))
		ft_handle_exit(parsing);
	if (!ft_strncmp(parsing->tkn[0], "cd", ft_strlen(parsing->tkn[0]))
		&& ft_cmd_cd(envp, parsing) == 0)
	{
		return (0);
	}
	if (ft_external_cmds_bis(parsing, envp) == 0)
		return (0);
	return (-1);
}
