
#include "../../includes/minishell.h"

// Cette fonction sert à trouver le chemin d'accès d'une commande
// sous forme de tableau de chaînes de caractères.
/*char	**ft_path_envp(char **envp)
{
	int		i;
	char	*path;
	char	**path_f;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strjoin(envp[i] + 5, "/usr/bin:/bin");
			break ;
		}
		i++;
	}
	path_f = ft_split(path, ':');
	free(path);
	return (path_f);
}*/

void	ft_count_espace_echo(t_parsing *parsing, char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[++i] != NULL)
	{
		if (!ft_strncmp(input[i], "echo", ft_strlen(input[i])))
		{
			i++;
			while (input[i] != NULL)
			{
				count++;
				i++;
			}
		}
	}
	return (count);
}

void	ft_espace_parsing(t_parsing *parsing)
{
	int	i;
	//int	k;
	int	count;

	i = 0;
	count = 0;
	while (parsing->tkn[++i] != NULL)
	{
		if (!ft_strncmp(parsing->tkn[i], "echo", ft_strlen(parsing->tkn[i])))
		{
			i++;
			while (parsing->tkn_value[i] == ARG)
			{
				count++;
				i++;
			}
		}
	}
	return (count);
}
