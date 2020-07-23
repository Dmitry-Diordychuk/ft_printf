/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:24:26 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/22 18:11:26 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_x_precision(const char *str, int len, t_format *format,
																	int upper)
{
	int counter;

	if (format->precision == 0 && str[0] == '0' && str[1] == '\0')
		len--;
	counter = 0;
	if (format->flag != '-')
	{
		if (format->precision < len)
			counter += print_ch_n(' ', format->width - len);
		else
			counter += print_ch_n(' ', format->width - format->precision);
	}
	counter += print_ch_n('0', format->precision - len);
	print_hex(str, upper, format);
	counter += len;
	if (format->flag == '-')
	{
		if (format->precision < len)
			counter += print_ch_n(' ', format->width - len);
		else
			counter += print_ch_n(' ', format->width - format->precision);
	}
	return (counter);
}

int		print_x(t_format *format, va_list params, int upper)
{
	const char	*str = uint_to_hex((unsigned int)va_arg(params, int));
	const int	len = ft_strlen((char *)str);
	int			counter;

	counter = 0;
	if (format->precision > -1)
		counter += print_x_precision(str, (int)len, format, upper);
	else
	{
		if (format->flag != '-')
			format->flag == '0' ?
				(counter += print_ch_n('0', format->width - len)) :
				(counter += print_ch_n(' ', format->width - len));
		print_hex(str, upper, format);
		counter += len;
		if (format->flag == '-')
			counter += print_ch_n(' ', format->width - len);
	}
	ft_free((void *)str);
	return (counter);
}

void	print_hex(const char *str, int is_big, t_format *format)
{
	int i;

	if (format->precision == 0 && str[0] == '0' && str[1] == '\0')
		return ;
	if (is_big == 0)
		ft_putstr_fd((char*)str, 1);
	else
	{
		i = 0;
		while (str[i] != '\0')
		{
			ft_putchar_fd(ft_toupper(str[i]), 1);
			i++;
		}
	}
}
