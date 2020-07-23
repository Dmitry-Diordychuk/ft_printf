/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:19:45 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:06:50 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_format *format, va_list params)
{
	int		counter;
	char	ch;

	counter = 1;
	if (format->type == '%')
		ch = '%';
	else
		ch = (char)va_arg(params, int);
	format->precision = 1;
	if (format->flag == '0')
		counter += print_ch_n('0', format->width - format->precision);
	if (format->flag == 0)
		counter += print_ch_n(' ', format->width - format->precision);
	ft_putchar_fd(ch, 1);
	if (format->flag == '-')
		counter += print_ch_n(' ', format->width - format->precision);
	return (counter);
}
