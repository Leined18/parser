/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:20:51 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/30 10:31:50 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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

e_state	handle_redirection(char c)
{
	(void)c;
	return (START);
}
