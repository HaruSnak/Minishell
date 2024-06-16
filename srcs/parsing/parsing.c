
#include "../../includes/minishell.h"

// Cette fonction sert à trouver le chemin d'accès d'une commande
// sous forme de tableau de chaînes de caractères.
char	**ft_path_envp(char **envp)
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
}
