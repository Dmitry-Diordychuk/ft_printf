/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:13:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/22 18:14:53 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct		s_format
{
	char			flag;
	long int		width;
	long int		precision;
	char			type;
}					t_format;

typedef struct		s_fsm_state
{
	char			*state_name;
	t_list			*transitions;
}					t_fsm_state;

typedef struct		s_fsm_transition
{
	t_fsm_state		*state;
	char			*input;
}					t_fsm_transition;

int					ft_printf(const char *str, ...);
int					main_loop(const char *str, t_format **format,
																va_list params);

t_fsm_state			*create_state(const char *state_name);
t_fsm_transition	*create_transition(t_fsm_state *state, const char *input);
int					add_transition(t_list **list, char *state_name,
												char *to_state, char *input);
int					cmp_state_name(char *searched_name, t_fsm_state *state);
int					cmp_symstate(char *symbol, t_fsm_transition *cur);

int					init_transition_none(t_list **all_states);
int					init_transition_f(t_list **all_states);
int					init_transition_w(t_list **all_states);
int					init_transition_p(t_list **all_states);
int					init_machine(t_list **all_states);

t_format			*init_format(void);
int					reset_format(t_format **format);
int					add_digit_nextposition(int number, char digit);
void				fill_format(t_format *format, t_fsm_state *cur_state,
													char ch, va_list params);

int					print_c(t_format *format, va_list params);

void				transition_free(void *transition);
void				state_free(void *state);
int					validate_machine(char next_symbol, t_format *format,
																va_list params);
int					result_processing(int val_result, t_format **format,
																va_list params);
int					return_handler(int return_value, t_list *all_states,
														t_fsm_state **machine);

int					print_id(t_format *format, va_list params);
int					print_number(int n, t_format *format, long int n_len);
int					print_id_precision(long int n, long int	n_len,
															t_format *format);
int					print_id_zero(long int n, long int	n_len,
															t_format *format);

int					print_p(t_format *format, va_list params);
int					print_p_precision(const char *str, int len,
															t_format *format);

int					print_u(t_format *format, va_list params);
int					print_unumber(unsigned int n, t_format *format, int n_len);

int					print_x(t_format *format, va_list params, int upper);
void				print_hex(const char *str, int is_big, t_format *format);
int					print_x_precision(const char *str, const int len,
												t_format *format, int upper);

char				*addchar(char *s1, char const s2);
int					print_ch_n(char c, int n);
char				digittohex(unsigned int digit);
char				*strrotate(char *str);
char				*uint_to_hex(int long n);
long int			intlen(long int n);

int					print_s(t_format *format, va_list params);

int					ft_printf(const char *str, ...);

#endif
