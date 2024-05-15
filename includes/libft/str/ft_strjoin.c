/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:19:10 by shmoreno          #+#    #+#             */
/*   Updated: 2024/03/17 18:37:26 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Concatenate two strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		p;
	char	*ptr;

	i = 0;
	p = 0;
	ptr = malloc((sizeof(char)) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!s1 || !s2 || !ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[p] = s1[i];
		p++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[p] = s2[i];
		p++;
		i++;
	}
	ptr[p] = '\0';
	return (ptr);
}
