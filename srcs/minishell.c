/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:11:04 by shmoreno          #+#    #+#             */
/*   Updated: 2024/05/15 14:28:53 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int g_signal = 0;

void	ft_init_main(struct s_parsing *parsing,
	char **envp, int argc)
{
	parsing->exit_value = 0;
	parsing->pwd = getenv("PWD");
	parsing->tmp = NULL;
	parsing->tmp_env = NULL;
	parsing->n_senv = "OLDPWD";
	parsing->v_senv = "";
	parsing->k = 0;
	//parsing->blocking_cmd = 0;
	ft_setenv(envp, parsing);
	(void)argc; 
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	struct sigaction	sa;
	struct termios		term;
	struct s_parsing	parsing;
	//static int			blocking_cmd;
	cc_t vquit_default;

	ft_init_main(&parsing, envp, argc);
	(void)argv;
	sa.sa_handler = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	tcgetattr(STDIN_FILENO, &term);
	vquit_default = term.c_cc[VQUIT];
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		//sigaction(SIGQUIT, &sa, NULL);
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		input = readline("\033[0;32mminishell$ \033[0m");
		if (!input)
			break ;
		if (ft_handle_verify(&input, &parsing, envp) == 0)
			continue ;
		if (ft_external_cmds(&input, &parsing, envp) == 0) // RETURN VERIFY_OPERATORS.C
			continue ;
		if (ft_find_execve(&input, envp, &parsing, false) == -1)
		{
			printf("%s: command not found\n", input);
		}
		add_history(input);
		free(input);
		//printf("blocking_cmd = %d\n", parsing.blocking_cmd);
		//printf("g_signal = %d\n", g_signal);
		/*if (g_signal == 1)
		{
			printf("COUCOU");
			term.c_cc[VQUIT] = vquit_default;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
			sigaction(SIGQUIT, &sa, NULL);
		}*/
	}
	return (0);
}
