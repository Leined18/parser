/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_state-1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:15:31 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 13:03:07 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_pstate	handle_expantion(char c)
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
