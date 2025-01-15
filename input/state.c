/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:28:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/15 19:17:18 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

e_state	transition(e_state current, char c)
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
	if (current == SINGLE_QUOTE)
		return (handle_single_quote(c));
	if (current == DOUBLE_QUOTE)
		return (handle_double_quote(c));
	if (current == OPERATOR)
		return (handle_operator(c));
	if (current == PARENTESIS)
		return (handle_parentesis(c));
	if (current == EXPANSION)
		return (START);
	if (current == ASSIGNMENT)
		return (START);
	return (END);
}

// Implementación de funciones específicas para cada estado
e_state	handle_start(char c)
{
	if (is_whitespace(c))
		return (START);
	if (is_parentesis(c))
		return (PARENTESIS);
	if (is_single_quoted(c))
		return (SINGLE_QUOTE);
	if (is_double_quoted(c))
		return (DOUBLE_QUOTE);
	if (is_operator(c))
		return (OPERATOR);
	if (is_redirection(c))
		return (REDIRECTION);
	if (is_asignation(c))
		return (ASSIGNMENT);
	if (c == '$')
		return (EXPANSION);
	return (WORD); // Asumimos que cualquier otro carácter inicia una palabra
}
