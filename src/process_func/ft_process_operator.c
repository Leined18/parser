/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:31:42 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 11:31:52 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_operator - Handles operators in the input
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_operator(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, OPERATOR));
		free(token);
	}
	return (1);
}
