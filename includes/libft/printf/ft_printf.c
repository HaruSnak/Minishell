/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:15:46 by shmoreno          #+#    #+#             */
/*   Updated: 2024/03/27 19:34:46 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// ft_conditions() is a function that takes a character
// and a va_list as arguments.
static int	ft_conditions(char c, va_list condit)
{
	if (c == 'c')
		return (ft_conv_char(condit));
	if (c == 's')
		return (ft_conv_string(condit));
	if (c == 'p')
		return (ft_conv_pointer(condit));
	if (c == '%')
		return (ft_conv_percent());
	if (c == 'u')
		return (ft_conv_unsigned(condit));
	if (c == 'd' || c == 'i')
		return (ft_conv_decimal(condit));
	if (c == 'x')
		return (ft_conv_hexa_low(condit));
	if (c == 'X')
		return (ft_conv_hexa_upper(condit));
	return (write(1, &c, 1));
}

// ft_printf() is a function that takes a string as
//an argument and a variable number of arguments.
int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	args;
	size_t	count;

	if (!format)
		return (0);
	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && (!format[i + 1]))
			break ;
		else if (format[i] == '%')
		{
			i++;
			count += ft_conditions(format[i], args);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
