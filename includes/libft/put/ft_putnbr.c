/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:17:31 by shmoreno          #+#    #+#             */
/*   Updated: 2024/03/27 19:31:18 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_base(unsigned long long nb, const char *base)
{
	unsigned long long	len;
	int					count;

	count = 0;
	len = ft_strlen(base);
	if (nb >= len)
		count += ft_putnbr_base(nb / len, base);
	count += ft_putchar(base[nb % len]);
	return (count);
}
