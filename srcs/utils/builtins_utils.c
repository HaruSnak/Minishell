

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

int	ft_check_redir(t_parsing *parsing)
{
	int	i;

	i = -1;
	while (parsing->tkn_value[++i])
	{
		if (parsing->tkn_value[i] == IN || parsing->tkn_value[i] == OUT
			|| parsing->tkn_value[i] == APPEND
			|| parsing->tkn_value[i] == HEREDOC
			|| parsing->tkn_value[i] == PIPE)
			return (1);
	}
	return (0);
}
