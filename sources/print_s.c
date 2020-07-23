/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:18:21 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:07:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	print_s. Precision here show how many symbols will be printed.
*/

int	print_s(t_format *format, va_list params)
{
	int		i;
	int		counter;
	char	*str;

	counter = 0;
	if (!(str = va_arg(params, char*)))
	{
		if (!(str = ft_strdup("(null)")))
			return (-1);
	}
	else if (!(str = ft_strdup(str)))
		return (-1);
	if (format->precision > (int)ft_strlen(str) || format->precision < 0)
		format->precision = ft_strlen(str);
	if (format->flag == '0')
		counter += print_ch_n('0', format->width - format->precision);
	if (format->flag == 0)
		counter += print_ch_n(' ', format->width - format->precision);
	i = -1;
	while (++i < format->precision)
		ft_putchar_fd(str[i], 1);
	if (format->flag == '-')
		counter += print_ch_n(' ', format->width - format->precision);
	ft_free((void*)str);
	return (counter + i);
}
