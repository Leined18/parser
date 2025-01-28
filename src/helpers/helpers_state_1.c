/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:16:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/15 19:16:43 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

e_state	handle_single_quote(char c)
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
	if (c == '$')
		return (EXPANSION);
	return (SINGLE_QUOTE);
}

e_state	handle_double_quote(char c)
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
	if (c == '$')
		return (EXPANSION);
	return (DOUBLE_QUOTE);
}