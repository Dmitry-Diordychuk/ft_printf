/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:20:54 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/22 18:22:46 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_p_precision(const char *str, int len, t_format *format)
{
	int counter;

	if (format->precision == 0 && str[0] == '0' && str[1] == '\0')
		len--;
	counter = 0;
	if (format->flag != '-')
	{
		if (format->precision < (len - 2))
			counter += print_ch_n(' ', format->width - len);
		else
			counter += print_ch_n(' ', format->width - (format->precision + 2));
	}
	ft_putstr_fd("0x", 1);
	counter += print_ch_n('0', format->precision - (len - 2));
	if (!(format->precision == 0 && str[0] == '0' && str[1] == '\0'))
		ft_putstr_fd((char *)str, 1);
	counter += len;
	if (format->flag == '-')
	{
		if (format->precision < (len - 2))
			counter += print_ch_n(' ', format->width - len);
		else
			counter += print_ch_n(' ', format->width - (format->precision + 2));
	}
	return (counter);
}

int	print_p(t_format *format, va_list params)
{
	const char	*str = uint_to_hex((unsigned long)va_arg(params, void*));
	const int	len = ft_strlen((char *)str) + 2;
	int			counter;

	counter = 0;
	if (format->precision > -1)
		counter += print_p_precision(str, (int)len, format);
	else
	{
		if (format->flag != '-')
			format->flag == '0' ?
				(counter += print_ch_n('0', format->width - len)) :
				(counter += print_ch_n(' ', format->width - len));
		ft_putstr_fd("0x", 1);
		ft_putstr_fd((char *)str, 1);
		counter += len;
		if (format->flag == '-')
			counter += print_ch_n(' ', format->width - len);
	}
	ft_free((void *)str);
	return (counter);
}
