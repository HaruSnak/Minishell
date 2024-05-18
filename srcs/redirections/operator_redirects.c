
#include "../../includes/minishell.h"

int	ft_handle_less_than(char **tmp, struct s_parsing *parsing, int i)
{
	int	fd;

	fd = open(tmp[i + 1], O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", tmp[i + 1]);
		parsing->exit_value = 1;
		return (-1);
		}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		parsing->exit_value = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

int	ft_handle_more_than(char **tmp, struct s_parsing *parsing, int i)
{
	int		fd;

	fd = open(tmp[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", tmp[i + 1]);
		parsing->exit_value = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		parsing->exit_value = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

int	ft_handle_here_doc(char **tmp, struct s_parsing *parsing, int i)
{
	char	*line;
	int		fd;

	fd = open("heredoc", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (tmp[i + 1] == NULL)
	{
		printf("minishell: %s: No such file or directory\n", tmp[i + 1]);
		parsing->exit_value = 1;
		return (-1);
	}
	line = readline("> ");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, tmp[i + 1], ft_strlen(tmp[i + 1])) == 0)
		{
			free(line);
			//close(fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

void	ft_condition_operator(char *input, int *i, int *k, char *tmp)
{
	if (((input[*i] == '>' || input[*i] == '<' || input[*i] == '|')
			&& (input[*i + 1] != ' ' && input[*i - 1] != ' '))
		|| (input[*i] == '<' && input[*i + 1] == '<'
			&& input[*i + 2] != ' ' && input[*i - 1] != ' ')
		|| (input[*i] == '>' && input[*i + 1] == '>'
			&& input[*i + 2] != ' ' && input[*i - 1] != ' '))
	{
		tmp[*k] = ' ';
		(*k)++;
		tmp[*k] = input[*i];
		if (input[*i + 1] == '>' || input[*i + 1] == '<')
		{
			(*k)++;
			tmp[*k] = input[*i + 1];
			(*i)++;
		}
		(*k)++;
		tmp[*k] = ' ';
		(*k)++;
	}
	else
	{
		tmp[*k] = input[*i];
		(*k)++;
	}
}

int	ft_exec_cmd_redirects(char **tmp, struct s_parsing *parsing,
	int i)
{
	if (ft_strncmp(tmp[i], "<", ft_strlen(tmp[i])) == 0)
	{
		if (ft_handle_less_than(tmp, parsing, i) == -1)
			return (-1);
	}
	else if (ft_strncmp(tmp[i], ">", ft_strlen(tmp[i])) == 0)
	{
		if (ft_handle_more_than(tmp, parsing, i) == -1)
			return (-1);
	}
	else if (ft_strncmp(tmp[i], "<<", ft_strlen(tmp[i])) == 0)
	{
		if (ft_handle_here_doc(tmp, parsing, i) == 0)
			return (2);
		else
			return (-1);
	}
	return (0);
}
