/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:03 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/21 13:39:04 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Handle signals for the minishell program
void	ft_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_number = signum;
	}
}

void	ft_signal_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
		g_signal_number = signum;
	}
}

void	ft_signal_return(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_signal_number = signum;
	}
}
