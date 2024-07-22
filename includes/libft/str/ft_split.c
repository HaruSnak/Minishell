/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:08:32 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/11 15:10:30 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Count the number of words in a string
static int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(n + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	**allocate_words(const char *s, char *c_star, int count)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == *c_star)
			s++;
		result[i] = ft_strndup(s, strcspn(s, c_star));
		if (!result[i])
		{
			while (i >= 0)
				free(result[i--]);
			free(result);
			return (NULL);
		}
		s += strcspn(s, c_star);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**result;
	char	c_str[2];

	c_str[0] = c;
	c_str[1] = '\0';
	if (!s)
		return (NULL);
	count = word_count(s, c);
	result = allocate_words(s, c_str, count);
	return (result);
}
