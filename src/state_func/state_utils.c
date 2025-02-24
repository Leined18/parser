/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:28:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 10:45:12 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

e_pstate	transition(e_pstate current, char c)
{
	if (current == END || c == '\0')
		return (END);
	// Delegar la lógica a funciones específicas según el estado actual
	if (current == START)
		return (handle_start(c));
	if (current == WORD)
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

// Implementación de funciones específicas para cada estado
e_pstate	handle_start(char c)
{
	if (ft_strchr("\n \t", c))
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
	return (WORD); // Asumimos que cualquier otro carácter inicia una palabra
}

int	ft_mtcheck_state(t_mt *mt, int state)
{
	if (!mt)
		return (0);
	if (mt->values.state == state)
		return (1);
	return (0);
}
