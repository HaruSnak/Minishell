/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_suit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:16:12 by shmoreno          #+#    #+#             */
/*   Updated: 2024/03/27 19:30:54 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_conv_decimal(va_list ap)
{
	long long	n;
	int			negativ_int;

	n = va_arg(ap, int);
	negativ_int = 0;
	if (n < 0)
	{
		n *= -1;
		negativ_int++;
		write(1, "-", 1);
	}
	return (ft_putnbr_base(n, "0123456789") + negativ_int);
}

int	ft_conv_hexa_low(va_list ap)
{
	unsigned int	n;

	n = va_arg(ap, unsigned int);
	return (ft_putnbr_base(n, "0123456789abcdef"));
}

int	ft_conv_hexa_upper(va_list ap)
{
	unsigned int	n;

	n = va_arg(ap, unsigned int);
	return (ft_putnbr_base(n, "0123456789ABCDEF"));
}
