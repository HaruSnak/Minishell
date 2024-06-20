/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:38 by shmoreno          #+#    #+#             */
/*   Updated: 2024/06/19 11:52:02 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_signal(struct sigaction *sa, struct sigaction *sa_quit)
{
	(*sa).sa_handler = ft_signal_handler;
	(*sa_quit).sa_handler = SIG_IGN;
	sigemptyset(&(*sa_quit).sa_mask);
	sigemptyset(&(*sa).sa_mask);
	(*sa_quit).sa_flags = 0;
	(*sa).sa_flags = 0;
}

void	ft_init_signal_block(void)
{
	struct sigaction	sa_return;
	struct sigaction	sa_quit;

	sa_return.sa_handler = ft_signal_return;
	sa_quit.sa_handler = ft_signal_quit;
	sa_quit.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_return.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGINT, &sa_return, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}
