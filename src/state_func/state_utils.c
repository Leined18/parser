/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:28:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/03 09:05:53 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Manages state ft_transitions in the state machine.
 *
 * @param current The current state.
 * @param c The input character.
 * @return The next state based on the input.
 *
 * Delegates logic to state-specific handlers, ensuring modularity
 * and adaptability. Returns END if the state is END or the character is '\0'.
 */

t_pstate	ft_transition(t_pstate current, char c)
{
	if (current == END || c == '\0')
		return (END);
	if (current == START)
		return (handle_start(c));
	if (current == WORD || current == WILDCARD)
		return (handle_word(c));
	if (current == REDIRECTION)
		return (handle_redirection(c));
	if (current == SINGLE_QUOTE || current == DOUBLE_QUOTE)
		return (handle_quote(c));
	if (current == OPERATOR)
		return (handle_operator(c));
	if (current == PARENTESIS)
		return (handle_parentesis(c));
	if (current == EXPANSION)
		return (handle_expantion(c));
	return (END);
}

t_pstate	handle_start(char c)
{
	if (ft_strchr("\n \t\v", c))
		return (START);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("\'", c))
		return (SINGLE_QUOTE);
	if (ft_strchr("\"", c))
		return (DOUBLE_QUOTE);
	if (ft_strchr("|&", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr("*", c))
		return (WILDCARD);
	return (WORD);
}

int	ft_mtcheck_state(t_mt *mt, int state)
{
	if (!mt)
		return (0);
	if (mt->values.state == state)
		return (1);
	return (0);
}
