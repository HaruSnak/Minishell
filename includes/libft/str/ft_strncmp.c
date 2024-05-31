/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:24:04 by shmoreno          #+#    #+#             */
/*   Updated: 2023/10/23 13:24:04 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Compare the first n bytes of two strings s1 and s2
int	ft_strncmp(const char *s1, const char *s2, int size)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && size != 0)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (2);
		size--;
		i++;
	}
	return (0);
}
