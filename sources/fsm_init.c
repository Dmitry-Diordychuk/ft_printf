/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:09:18 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:02:27 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Add all transitions from first state. State without conventions.
**	Also inits Start state from wich we begin.
*/

int	init_transition_none(t_list **all_states)
{
	if (!add_transition(all_states, "Start", "None", "%") ||
		!add_transition(all_states, "None", "None", " ") ||
		!add_transition(all_states, "None", "Wa", "*") ||
		!add_transition(all_states, "None", "Wn", "123456789") ||
		!add_transition(all_states, "None", "f0", "0") ||
		!add_transition(all_states, "None", "fm", "-") ||
		!add_transition(all_states, "None", "P", ".") ||
		!add_transition(all_states, "None", "Finish", "diuxXscp%"))
		return (0);
	return (1);
}

/*
**	Adds all transitions between flag states.
*/

int	init_transition_f(t_list **all_states)
{
	if (!add_transition(all_states, "f0", "Wa", "*") ||
		!add_transition(all_states, "f0", "Wn", "123456789") ||
		!add_transition(all_states, "f0", "f0", "0 ") ||
		!add_transition(all_states, "f0", "fm", "-") ||
		!add_transition(all_states, "f0", "P", ".") ||
		!add_transition(all_states, "f0", "Finish", "diuxXs%") ||
		!add_transition(all_states, "fm", "Wa", "*") ||
		!add_transition(all_states, "fm", "Wn", "123456789") ||
		!add_transition(all_states, "fm", "fm", "-0 ") ||
		!add_transition(all_states, "fm", "P", ".") ||
		!add_transition(all_states, "fm", "Finish", "diuxXscp%"))
		return (0);
	return (1);
}

/*
**	Adds all transitions between width states.
*/

int	init_transition_w(t_list **all_states)
{
	if (!add_transition(all_states, "Wa", "Wa", " ") ||
		!add_transition(all_states, "Wa", "P", ".") ||
		!add_transition(all_states, "Wa", "Finish", "diuxXscp%") ||
		!add_transition(all_states, "Wn", "Wn", "0123456789 ") ||
		!add_transition(all_states, "Wn", "P", ".") ||
		!add_transition(all_states, "Wn", "Finish", "diuxXscp%"))
		return (0);
	return (1);
}

/*
**	Adds all transitions between precision states.
*/

int	init_transition_p(t_list **all_states)
{
	if (!add_transition(all_states, "P", "P", " ") ||
		!add_transition(all_states, "P", "Pa", "*") ||
		!add_transition(all_states, "P", "Pn", "0123456789") ||
		!add_transition(all_states, "P", "Pm", "-") ||
		!add_transition(all_states, "P", "Finish", "diuxXscp%") ||
		!add_transition(all_states, "Pa", "Pa", " ") ||
		!add_transition(all_states, "Pa", "Finish", "diuxXscp%") ||
		!add_transition(all_states, "Pn", "Pn", "0123456789 ") ||
		!add_transition(all_states, "Pn", "Finish", "diuxXscp%") ||
		!add_transition(all_states, "Pm", "Pm", " ") ||
		!add_transition(all_states, "Pm", "Pn", "123456789") ||
		!add_transition(all_states, "Pm", "Finish", "diuxXscp%"))
		return (0);
	return (1);
}

/*
** Creates all states and all transitions between them.
**+------+-----+-----+----+------+----+-----+---+----+------+----+-----------+
**|      |Start|None | Wa |  Wn  | f0 |  fm | P | Pa | Pn   | Pm |  Finish   |
**+------+-----+-----+----+------+----+-----+---+----+------+----+-----------+
**|Start |     | '%' |    |      |    |     |   |    |      |    |           |
**|None  |     | ' ' |'*' |'1-9' | '0'| '-' |'.'|    |      |    |'diuxXscp%'|
**|Wa    |     |     |' ' |      |    |     |'.'|    |      |    |'diuxXscp%'|
**|Wn    |     |     |    |'0-9 '|    |     |'.'|    |      |    |'diuxXscp%'|
**|f0    |     |     |'*' |'1-9' |'0 '| '-' |'.'|    |      |    |'diuxXscp%'|
**|fm    |     |     |'*' |'1-9' |    |'-0 '|'.'|    |      |    |'diuxXscp%'|
**|P     |     |     |    |      |    |     |' '|'*' |'1-9' |'-' | 'diuxXs%' |
**|Pa    |     |     |    |      |    |     |   |' ' |      |    | 'diuxXs%' |
**|Pn    |     |     |    |      |    |     |   |    |'0-9 '|    | 'diuxXs%' |
**|Pm    |     |     |    |      |    |     |   |    |'1-9' |' ' | 'diuxXs%' |
**|Finish|     |     |    |      |    |     |   |    |      |    |           |
**+------+-----+-----+----+------+----+-----+---+----+------+----+-----------+
*/

int	init_machine(t_list **all_states)
{
	*all_states = ft_lstnew(create_state("Start"));
	ft_lstadd_back(all_states, ft_lstnew(create_state("None")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Wa")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Wn")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("f0")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("fm")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("P")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Pa")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Pn")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Pm")));
	ft_lstadd_back(all_states, ft_lstnew(create_state("Finish")));
	if (ft_lstsize(*all_states) != 11)
		return (0);
	if (!(init_transition_none(all_states)))
		return (0);
	if (!(init_transition_f(all_states)))
		return (0);
	if (!(init_transition_w(all_states)))
		return (0);
	if (!(init_transition_p(all_states)))
		return (0);
	return (1);
}
