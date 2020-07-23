/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:12:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:00:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	init_format function malloc t_format and fill it with starting values.
*/

t_format	*init_format(void)
{
	t_format	*format;

	if (!(format = (t_format*)ft_malloc(sizeof(t_format), NULL)))
		return (NULL);
	format->flag = '\0';
	format->width = -1;
	format->precision = -1;
	format->type = '\0';
	return (format);
}

/*
**	reset_format() function free t_format and malloc it in init_format() again.
*/

int			reset_format(t_format **format)
{
	ft_free(*format);
	if (!(*format = init_format()))
		return (0);
	return (1);
}

/*
**	add_digit_nextposition(number, digit). Example (21, '1') -> 211
*/

int			add_digit_nextposition(int number, char digit)
{
	if (number == 0 || number == -1)
		return (digit - 48);
	return ((number * 10) + (digit - 48));
}

/*
**	fill_format. Get symbol and add it in suitable field of t_format
*/

void		fill_format(t_format *format, t_fsm_state *cur_state, char ch,
																va_list params)
{
	if (ch == ' ')
		return ;
	if (cur_state->state_name[0] == 'f' && !(format->flag == '-'))
		format->flag = ch;
	if (cur_state->state_name[0] == 'W')
	{
		if (ch == '*')
			if ((format->width = va_arg(params, int)) < 0)
			{
				format->width = -(format->width);
				format->flag = '-';
			}
		if (ch != '*')
			format->width = add_digit_nextposition(format->width, ch);
	}
	if (cur_state->state_name[0] == 'P')
	{
		ch == '.' ? format->precision = 0 : 0;
		if (ch == '*')
			if ((format->precision = va_arg(params, int)) < 0)
				format->precision = -1;
		if (ch != '*' && ch != '.')
			format->precision = add_digit_nextposition(format->precision, ch);
	}
	cur_state->state_name[0] == 'F' ? format->type = ch : 0;
}
