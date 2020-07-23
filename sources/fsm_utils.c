/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:03:13 by kdustin           #+#    #+#             */
/*   Updated: 2020/07/20 20:03:54 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	This functio creates new s_fsm_transition structure and init it's fields.
*/

t_fsm_state			*create_state(const char *state_name)
{
	t_fsm_state	*new_state;

	if (!(new_state = (t_fsm_state*)ft_malloc(sizeof(t_fsm_state), NULL)))
		return (NULL);
	if (!(new_state->state_name = ft_strdup(state_name)))
	{
		ft_free(new_state);
		return (NULL);
	}
	new_state->transitions = NULL;
	return (new_state);
}

/*
**	This functio creates new s_fsm_state structure and init it's fields.
*/

t_fsm_transition	*create_transition(t_fsm_state *state, const char *input)
{
	t_fsm_transition	*new_trans;

	if (!(new_trans = (t_fsm_transition*)ft_malloc(sizeof(t_fsm_transition),
																		NULL)))
		return (NULL);
	if (!(new_trans->input = ft_strdup(input)))
	{
		ft_free(new_trans);
		return (NULL);
	}
	new_trans->state = state;
	return (new_trans);
}

/*
**	This function adds transition in list of trantions in structure t_fsm_state.
*/

int					add_transition(t_list **list, char *state_name,
													char *to_state, char *input)
{
	t_fsm_state	*from;
	t_fsm_state	*to;
	t_list		*tmp;

	from = (t_fsm_state*)(ft_lstfind(*list, state_name,
													cmp_state_name)->content);
	to = (t_fsm_state*)(ft_lstfind(*list, to_state, cmp_state_name)->content);
	if (!(tmp = ft_lstnew(create_transition(to, input))))
		return (0);
	ft_lstadd_back(&(from->transitions), tmp);
	return (1);
}

/*
**	This funcion used by lstfind to search name of current state name.
*/

int					cmp_state_name(char *searched_name, t_fsm_state *state)
{
	return (ft_strcmp(searched_name, state->state_name));
}

/*
**	This function is trying to find symbol in posible state inputs.
*/

int					cmp_symstate(char *symbol, t_fsm_transition *cur)
{
	if (*symbol == '\0')
		return (-1);
	if (ft_strchr(cur->input, *symbol))
		return (0);
	return (-1);
}
