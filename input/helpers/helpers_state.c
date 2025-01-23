/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:20:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/15 19:16:31 by danpalac         ###   ########.fr       */
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
	if (c == '$')
		return (EXPANSION);
	if (is_asignation(c))
		return (ASSIGNMENT);
	return (WORD);
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
