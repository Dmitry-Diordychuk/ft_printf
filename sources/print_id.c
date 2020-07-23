/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:22:36 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/23 02:16:09 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_id_precision(long int n, long int n_len, t_format *format)
{
	int	counter;

	counter = 0;
	if (n < 0)
		format->precision++;
	if (format->flag != '-')
	{
		if (format->precision >= n_len)
			counter += print_ch_n(' ', format->width - format->precision);
		else if (format->precision < n_len)
			counter += print_ch_n(' ', format->width - n_len);
	}
	if (n < 0)
		ft_putchar_fd('-', 1);
	counter += print_ch_n('0', format->precision - n_len);
	counter += print_number(n, format, n_len);
	if (format->flag == '-')
	{
		if (format->precision >= n_len)
			counter += print_ch_n(' ', format->width - format->precision);
		else if (format->precision < n_len)
			counter += print_ch_n(' ', format->width - n_len);
	}
	return (counter);
}

int	print_id_zero(long int n, long int n_len, t_format *format)
{
	int counter;

	counter = 0;
	if (n < 0)
		ft_putchar_fd('-', 1);
	if (format->flag != '-')
		counter += print_ch_n('0', format->width - n_len);
	counter += print_number(n, format, n_len);
	if (format->flag == '-')
		counter += print_ch_n('0', format->width - n_len);
	return (counter);
}

int	print_id(t_format *format, va_list params)
{
	const long int	n = va_arg(params, int);
	long int		n_len;
	int				counter;

	n_len = intlen(n);
	if (n == 0 && format->precision == 0)
		n_len = 0;
	counter = 0;
	if (format->precision > -1)
		counter = print_id_precision(n, n_len, format);
	else if (format->flag == '0')
		counter = print_id_zero(n, n_len, format);
	else
	{
		if (format->flag != '-')
			counter += print_ch_n(' ', format->width - n_len);
		if (n < 0)
			ft_putchar_fd('-', 1);
		counter += print_number(n, format, n_len);
		if (format->flag == '-')
			counter += print_ch_n(' ', format->width - n_len);
	}
	return (counter);
}

int	print_number(int n, t_format *format, long int n_len)
{
	if (n > 0)
		ft_putnbr_fd(n, 1);
	if (n < 0 && n != -2147483648)
		ft_putnbr_fd(-n, 1);
	if (n == -2147483648)
		ft_putstr_fd("2147483648", 1);
	if (format->precision != 0 && n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	return (n_len);
}
