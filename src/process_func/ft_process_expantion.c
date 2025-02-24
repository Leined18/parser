/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_expantion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:45:02 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 11:22:48 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_expantion - Handles expantions in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_expantion(char *input, int *i, t_mt **list)
{
	char	*token;
	t_mt	*par;

	if (!input || !i || !list)
		return (0);
	if (ft_strchr("(", input[*i + 1]) && input[*i + 1])
	{
		*i += 1;
		par = NULL;
		if (!ft_process_parentheses(input, i, &par, "$()"))
			return (0);
		return (ft_mtaddlast_right(list, par), 1);
	}
	token = ft_extract_expantion_token(input, i);
	if (!token)
		return (0);
	ft_mtaddlast_right(list, ft_newnode(token, EXPANSION));
	return (free(token), 1);
}
