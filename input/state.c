/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:28:51 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/17 17:08:37 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

e_state	handle_parentesis(char c);
// Función principal
e_state	transition(e_state current, char c)
{
	if (current == END || c == '\0')
		return (END);
	// Delegar la lógica a funciones específicas según el estado actual
	switch (current)
	{
	case START:
		return (handle_start(c));
	case WORD:
		return (handle_word(c));
	case REDIRECTION:
		return (handle_redirection(c));
	case QUOTE:
		return (handle_quote(c));
	case OPERATOR:
		return (handle_operator(c));
	case PARENTESIS:
		return (handle_parentesis(c));
	default:
		return (END);
	}
}
// Implementación de funciones específicas para cada estado
e_state	handle_start(char c)
{
	if (is_whitespace(c))
		return (START);
	if (is_parentesis(c))
		return (PARENTESIS);
	if (is_quoted(c))
		return (QUOTE);
	if (is_operator(c))
		return (OPERATOR);
	if (is_redirection(c))
		return (REDIRECTION);
	if (is_asignation(c))
		return (ASSIGNMENT);
	return (WORD); // Asumimos que cualquier otro carácter inicia una palabra
}

e_state	handle_word(char c)
{
	if (is_whitespace(c))
		return (START);
	if (is_operator(c))
		return (OPERATOR);
	if (is_redirection(c))
		return (REDIRECTION);
	if (is_parentesis(c))
		return (PARENTESIS);
	return (WORD);
}

e_state	handle_redirection(char c)
{
	(void)c;
	return (START);
}

e_state	handle_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (START); // Cierra las comillas
	if (is_whitespace(c))
		return (START);
	if (ft_isalnum(c))
		return (WORD);
	if (is_operator(c))
		return (OPERATOR);
	if (is_redirection(c))
		return (REDIRECTION);
	if (is_parentesis(c))
		return (PARENTESIS);
	return (QUOTE);
}

e_state	handle_operator(char c)
{
	(void)c;
	return (START);
}

e_state	handle_parentesis(char c)
{
	if (c == '(')
		return (PARENTESIS);
	return (START);
}
