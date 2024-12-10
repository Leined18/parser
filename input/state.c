/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:28:51 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/10 13:03:40 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// Función principal
e_state	transition(e_state current, char c)
{
	if (current == END || !c)
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
	default:
		return (END);
	}
}

// Implementación de funciones específicas para cada estado
e_state	handle_start(char c)
{
	if (c == ' ' || c == '\t')
		return (START);
	if (c == '\'' || c == '\"')
		return (QUOTE);
	if (c == '|' || c == '&')
		return (OPERATOR);
	if (c == '>' || c == '<')
		return (REDIRECTION);
	return (WORD); // Asumimos que cualquier otro carácter inicia una palabra
}

e_state	handle_word(char c)
{
	if (c == ' ' || c == '\t')
		return (START);
	if (c == '|' || c == '&')
		return (OPERATOR);
	if (c == '>' || c == '<')
		return (REDIRECTION);
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
	return (QUOTE);
}

e_state	handle_operator(char c)
{
	(void)c;
	return (START);
}
