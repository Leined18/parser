/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:20:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 12:38:12 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Defines the role of handlers in the state machine.
 *
 * @details Handlers determine the next state after processing a token.
 * When a token is fully parsed, the handler evaluates the next character
 * and returns the appropriate state transition.
 *
 * @example handle_word:
 * - Whitespace -> START
 * - Operator -> OPERATOR
 * - Otherwise -> WORD
 *
 * This approach ensures dynamic transitions and robust parsing.
 */

e_pstate	handle_word(char c)
{
	if (ft_strchr(" \v\t\n", c))
		return (START);
	if (ft_strchr("|", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("\'", c))
		return (SINGLE_QUOTE);
	if (ft_strchr("\"", c))
		return (DOUBLE_QUOTE);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr("*", c))
		return (WILDCARD);
	return (WORD);
}

e_pstate	handle_quote(char c)
{
	if (ft_strchr(" \v\t\n", c))
		return (START);
	if (ft_strchr("|", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr("*", c))
		return (WILDCARD);
	if (ft_isascii(c))
		return (WORD);
	return (START);
}

e_pstate	handle_operator(char c)
{
	if (ft_strchr("|&", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("\'", c))
		return (SINGLE_QUOTE);
	if (ft_strchr("\"", c))
		return (DOUBLE_QUOTE);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr(" \v\t\n", c))
		return (START);
	if (ft_strchr("*", c))
		return (WILDCARD);
	if (ft_isascii(c))
		return (WORD);
	return (START);
}

e_pstate	handle_parentesis(char c)
{
	if (c == '(')
		return (PARENTESIS);
	if (ft_strchr("|&", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("\'", c))
		return (SINGLE_QUOTE);
	if (ft_strchr("\"", c))
		return (DOUBLE_QUOTE);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr(" \v\t\n", c))
		return (START);
	if (ft_strchr("*", c))
		return (WILDCARD);
	if (ft_isascii(c))
		return (WORD);
	return (START);
}

e_pstate	handle_redirection(char c)
{
	if (ft_strchr("|&", c))
		return (OPERATOR);
	if (ft_strchr("><", c))
		return (REDIRECTION);
	if (ft_strchr("()", c))
		return (PARENTESIS);
	if (ft_strchr("\'", c))
		return (SINGLE_QUOTE);
	if (ft_strchr("\"", c))
		return (DOUBLE_QUOTE);
	if (ft_strchr("$", c))
		return (EXPANSION);
	if (ft_strchr(" \v\t\n", c))
		return (START);
	if (ft_strchr("*", c))
		return (WILDCARD);
	if (ft_isascii(c))
		return (WORD);
	return (START);
}
