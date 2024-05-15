/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:26:04 by shmoreno          #+#    #+#             */
/*   Updated: 2023/10/23 13:26:04 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Locate the last occurrence of c in the string s
char	*ft_strrchr(const char *s, int c)
{
	int	count;

	count = ft_strlen(s);
	while (count >= 0)
	{
		if (s[count] == (char)c)
			return ((char *)(s + count));
		count--;
	}
	return (NULL);
}
