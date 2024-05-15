/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:38 by shmoreno          #+#    #+#             */
/*   Updated: 2024/05/15 11:19:30 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (g_signal == 0)
		{
			rl_on_new_line();
			//rl_clear_history();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
}
