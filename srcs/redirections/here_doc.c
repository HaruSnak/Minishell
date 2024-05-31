
#include "../../includes/minishell.h"

int	heredoc_handling(char *eof)
{
	char 		*line;
	int			heredoc;

	heredoc = open("obj/srcs/redirections/heredoc.txt",
				O_CREAT | O_RDWR | O_APPEND, 777); /// error handling
	// PS(eof);
	while (ft_strncmp(line, eof, ft_strlen(line)) != 0)
	{
		// PL;
		if (ft_strncmp(line, eof, ft_strlen(line)))
			break ; 
		line = readline(">");
		write(heredoc, line, sizeof(line));
		free(line);
	}
	return (heredoc);
}
