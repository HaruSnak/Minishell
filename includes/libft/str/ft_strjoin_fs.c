/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:00:04 by pcardin           #+#    #+#             */
/*   Updated: 2024/05/18 17:29:53 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_fs(char const *s1, char const *s2)
{
	char	*s_out;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	s_out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+ 2));
	if (!s_out)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		s_out[i] = s1[i];
	s_out[i] = '/';
	i++;
	while (s2[j])
		s_out[i++] = s2[j++];
	s_out[i] = '\0';
	return (s_out);
}
