/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:23:55 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:07:42 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_u(t_format *format, va_list params)
{
	const unsigned int	n = va_arg(params, unsigned int);
	const unsigned int	n_len = intlen(n);
	int					counter;

	counter = 0;
	if (format->precision != -1 && format->flag == '0')
		format->flag = 0;
	if (format->precision > n_len && format->flag != '-')
		format->flag == '0' ?
			(counter += print_ch_n('0', format->width - format->precision)) :
			(counter += print_ch_n(' ', format->width - format->precision));
	else if (format->precision <= n_len && format->flag != '-')
		format->flag == '0' ?
			(counter += print_ch_n('0', format->width - n_len)) :
			(counter += print_ch_n(' ', format->width - n_len));
	counter += print_ch_n('0', format->precision - n_len);
	counter += print_unumber(n, format, n_len);
	if (format->precision > n_len && format->flag == '-')
		counter += print_ch_n(' ', format->width - format->precision);
	else if (format->precision <= n_len && format->flag == '-')
		counter += print_ch_n(' ', format->width - n_len);
	return (counter);
}

int	print_unumber(unsigned int n, t_format *format, int n_len)
{
	n > 0 ? ft_putunbr_fd(n, 1) : 0;
	if (format->precision != 0 && n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (format->precision == 0 && n == 0 &&
			format->flag != '0' && format->width > 0)
	{
		ft_putchar_fd(' ', 1);
		return (1);
	}
	if (format->precision == 0 && n == 0 &&
			format->flag == '0' && format->width > 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (format->precision == 0 && n == 0)
		return (0);
	return (n_len);
}
