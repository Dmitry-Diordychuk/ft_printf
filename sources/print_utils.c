/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:39:00 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/22 18:07:55 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	addchar() function adds char to s1. It's free old s1 and malloc new.
*/

char		*addchar(char *s1, char const s2)
{
	char	*str_from_char;
	char	*result;

	if (!(str_from_char = (char*)ft_calloc(2, sizeof(char))))
		return (NULL);
	str_from_char[0] = s2;
	if (!(result = ft_strjoin(s1, str_from_char)))
	{
		ft_free(str_from_char);
		ft_free(s1);
		return (NULL);
	}
	ft_free(str_from_char);
	ft_free(s1);
	return (result);
}

/*
**	Converts digit from 10 base to 16 base.
*/

char		digittohex(unsigned int digit)
{
	if (digit <= 9)
		return (48 + digit);
	else if (digit == 10)
		return ('a');
	else if (digit == 11)
		return ('b');
	else if (digit == 12)
		return ('c');
	else if (digit == 13)
		return ('d');
	else if (digit == 14)
		return ('e');
	else if (digit == 15)
		return ('f');
	return (-1);
}

/*
**	uint_to_hex make from n an str i wich we have hex symbols.
*/

char		*uint_to_hex(int long n)
{
	char	*hex;

	if (!(hex = ft_strdup("")))
		return (NULL);
	if (n == 0)
	{
		if (!(hex = addchar(hex, '0')))
			return (NULL);
		return (hex);
	}
	while (n != 0)
	{
		if (!(hex = addchar(hex, digittohex(n % 16))))
			return (NULL);
		n = n / 16;
	}
	hex = ft_strrotate(hex);
	return (hex);
}

/*
**	print_ch_n()
*/

int			print_ch_n(char c, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
	return (i);
}

/*
**	intlen() count how many digits and sign in int value.
*/

long int	intlen(long int n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
