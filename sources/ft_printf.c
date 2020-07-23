/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:06:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:06:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	iterate trought symbols of str. When it's find % after this symbol each sym-
**	bol is going trought validation and fills format fields.
**	Then processing called to input value.
**	Format pointer on pointer because in result processing we reset this pointer
**	and as result the original pointer will free wrong memory
*/

int	main_loop(const char *str, t_format **format, va_list params)
{
	int	i;
	int	counter;
	int	val_result;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			while ((val_result = validate_machine(str[i], *format, params)) > 0)
				i++;
			val_result == -1 ? i-- : 0;
			if (val_result == -2 ||
			(counter += result_processing(val_result, format, params)) < 0)
				return (-1);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			counter++;
		}
		i++;
	}
	return (counter);
}

/*
** The printf() function writes the output under the control of a format string
** that specifies how subsequent arguments are converted for output. If there
** are insufficient arguments for the format, the behavior is undefined. If the
** format is exhausted while arguments remain, the excess arguments are evalua-
** ted (as always) but are otherwise ignored. The fprintf function returns when
** the end of the format string is encountered.
**
** The format string is composed of zero or more directives: ordinary characters
** (not %), which are copied unchanged to the output stream; and conversion spe-
** cifications, each of which results in fetching zero or more subsequent argu-
** ments, converting them, if applicable, according to the corresponding conver-
** sion specifier, and then writing the result to the output stream.
**
** Each conversion specification is introduced by the % character. After the %,
** the following appear in sequence:
**
**	o	Zero or more of the following flags:
**
**		'0'	For d, i, o, u, x, X, a, A, e, E, f, F, g, and G conversions,
**		leading zeros (following any indication of sign or base) are used to pad
**		to the field width rather than performing space padding, except when
**		converting an infinity or NaN. If the 0 and - flags both appear, the 0
**		flag is ignored. For d, i, o, u, x, and X conversions, if a precision is
**		specified, the 0 flag is ignored. For other conversions, the behavior is
**		undefined.
**
**		'-'	The result of the conversion is left-justified within the field. (It
**		 is right-justified if this flag is not specified.)
**
**	o	An optional decimal digit string specifying a minimum field width. If
**		the converted value has fewer characters that the field width, it will
**		be padded with spaces on the left (or right, if the left-adjustment flag
**		has been given) to fill out the field width. The field width takes the
**		form of an asterisk * (described later) or a nonnegative decimal integer
**
**	o	An optional precision that gives the minimum number of digits to appear
**		for the d, i, o, u, x, and X conversions, or the maximum number of bytes
**		to be written for s conversions. The precision takes the form of a pe-
**		riod (.) followed either by an asterisk * (described later) or by an op-
**		tional decimal integer; if only the period is specified, the precision
**		is taken as zero. If a precision appears with any other conversion spe-
**		cifier, the behavior is undefined.
**
**	o	A conversion specifier character that specifies the type of conversion
**		to be applied.
**
** A field width or precision, or both, may be indicated by an asterisk '*'. In
** this case, an int argument supplies the field width or precision. A negative
** field width is treated as a left adjustment flag followed by a positive field
** field width; a negative precision is treated as though it were missing.
**
** The conversion specifiers and their meanings are:
**
** di	The int argument is converted to signed decimal in the style [−]dddd.
**		The precision specifies the minimum number of digits to appear; if the
**		value being converted can be represented in fewer digits, it is expanded
**		with leading zeros. The default precision is 1. The result of converting
**		a zero value with a precision of zero is no characters.
**
** uxX	The unsigned int argument is converted to unsigned decimal (u), or un-
**		signed hexadecimal notation (x or X) in the style dddd; the letters
**		abcdef are used for x conversion and the letters ABCDEF for X conversion
**		The precision specifies the minimum number of digits to appear; if the
**		value being converted can be represented in fewer digits, it is expanded
**		with leading zeros. The default precision is 1. The result of converting
**		a zero value with a precision of zero is no characters.
**
** c	The int argument is converted to an unsigned char, and the resulting
**		character is written
**
** s	The argument shall be a pointer to the initial element of an array of
**		character type. Characters from the array are written up to (but not
**		including) the terminating null character. If the precision is specified
**		, no more than that many bytes are written. If the precision is not spe-
**		cified or is greater than the size of the array, the array shall contain
**		a null character.
**
** p	The argument shall be a pointer to void. The value of the pointer is
**		converted to a sequence of printing characters, in an implementation-de-
**		fined manner.
**
** %	A '%' is written. No argument is converted. The complete conversion spe-
**		cification is '%%'.
**
** If a conversion specification is invalid, the behavior is undefined. If any
** argument is not the correct type for the corresponding conversion specifica-
** tion, the behavior is undefined.
**
** In no case does a nonexistent or small field width cause truncation of a
** field; if the result of a conversion is wider than the field width, the field
** is expanded to contain the conversion result.
**
** RETURN VALUES
** The fprintf function returns the number of characters transmitted, or a ne-
** gative value if an output or encoding error occurred.
*/

int	ft_printf(const char *str, ...)
{
	t_format		*format;
	va_list			params;
	int				counter;

	if (str == NULL)
		return (-1);
	format = NULL;
	counter = 0;
	va_start(params, str);
	if (!(format = init_format()))
	{
		va_end(params);
		return (-1);
	}
	counter = main_loop(str, &format, params);
	ft_free(format);
	va_end(params);
	return (counter);
}
