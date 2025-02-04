/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 10:20:51 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/04 12:30:47 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

e_pstate	handle_word(char c)
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
	return (WORD);
}

e_pstate	handle_quote(char c)
{
	(void)c;
	if (ft_isalpha(c))
		return (WORD);
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
	return (START);
}

e_pstate	handle_operator(char c)
{
	(void)c;
	if (ft_isalnum(c) || ft_strchr("=*!", c))
		return (WORD);
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
	return (START);
}

e_pstate	handle_parentesis(char c)
{
	if (c == '(')
		return (PARENTESIS);
	return (START);
}

e_pstate	handle_redirection(char c)
{
	(void)c;
	return (START);
}
