/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:37:46 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:12:34 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	handle memory of validate machine when it's stoped.
*/

int		return_handler(int return_value, t_list *all_states,
														t_fsm_state **machine)
{
	ft_lstclear(&all_states, state_free);
	*machine = NULL;
	return (return_value);
}

/*
**	This function get next symbol from input and validate it if it proper symbol
**	of the printf() format. If it proper it will be putted in static format
**	structure.
*/

int		validate_machine(char next_symbol, t_format *format, va_list params)
{
	static t_fsm_state	*machine;
	t_list				*all_states;
	t_list				*finded_state;

	if (machine == NULL)
	{
		if (!(init_machine(&all_states)))
			return (return_handler(-2, all_states, &machine));
		machine = (t_fsm_state*)(all_states->content);
	}
	finded_state = ft_lstfind(machine->transitions, &next_symbol, cmp_symstate);
	if (finded_state != NULL)
	{
		machine = ((t_fsm_transition*)(finded_state->content))->state;
		fill_format(format, machine, next_symbol, params);
		if (!ft_strcmp(machine->state_name, "Finish"))
			return (return_handler(0, all_states, &machine));
		return (1);
	}
	return (return_handler(-1, all_states, &machine));
}

/*
**	result_processing() is chosing wich function need to be call to print params
*/

int		result_processing(int val_result, t_format **format, va_list params)
{
	int	result;

	result = 0;
	if (val_result == 0)
	{
		if ((*format)->type == '%')
			result = print_c(*format, params);
		else if ((*format)->type == 'c')
			result = print_c(*format, params);
		else if ((*format)->type == 's')
			result = print_s(*format, params);
		else if ((*format)->type == 'p')
			result = print_p(*format, params);
		else if ((*format)->type == 'd' || (*format)->type == 'i')
			result = print_id(*format, params);
		else if ((*format)->type == 'u')
			result = print_u(*format, params);
		else if ((*format)->type == 'x')
			result = print_x(*format, params, 0);
		else if ((*format)->type == 'X')
			result = print_x(*format, params, 1);
		reset_format(format);
	}
	return (result);
}

void	transition_free(void *transition)
{
	t_fsm_transition *tmp;

	tmp = (t_fsm_transition*)transition;
	ft_free(tmp->input);
	tmp->state = NULL;
	ft_free(tmp);
}

void	state_free(void *state)
{
	t_fsm_state *tmp;

	tmp = (t_fsm_state*)state;
	ft_lstclear(&(tmp->transitions), transition_free);
	ft_free(tmp->state_name);
	tmp->state_name = NULL;
	ft_free(tmp);
}
