/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tkn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:08:32 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/11 15:37:37 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Count the number of words in a string
static int	word_count(const char *s, char c)
{
	bool	d_quote;
	bool	s_quote;
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	d_quote = false;
	s_quote = false;
	while (*s)
	{
		if (*s == '\"' && !s_quote)
			d_quote = !d_quote;
		else if (*s == '\'' && !d_quote)
			s_quote = !s_quote;
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word && !d_quote && !s_quote)
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

static int	find_word_end(const char *s, char *c_star)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (s[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (s[i] == *c_star && !in_single_quote && !in_double_quote)
			break ;
		i++;
	}
	return (i);
}

static char	**allocate_words(const char *s, char *c_star, int count)
{
	char	**result;
	int		i;
	int		word_len;

	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		while (*s == *c_star)
			s++;
		word_len = find_word_end(s, c_star);
		result[i] = ft_strndup(s, word_len);
		if (!result[i])
		{
			while (i >= 0)
				free(result[i--]);
			return (free(result), NULL);
		}
		s += word_len;
		while (*s == *c_star)
			s++;
	}
	return (result[i] = NULL, result);
}

char	**ft_split_tkn(char const *s, char c)
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
