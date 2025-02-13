/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:32:14 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/13 11:42:23 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_process_word - Handles words and non-operator tokens
 * @input: The input string
 * @i: Pointer to the current index
 * @list: Pointer to the root of the list
 */

int	ft_process_word(char *input, int *i, t_mt **list, e_pstate state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_word_token(input, i, " \t\n|&;=<>\"'`$");
	if (!token)
		return (0);
	if (ft_strchr(token, '=')) // Si el token contiene un '='
	{
		ft_mtaddlast_right(list, ft_newnode(token, ASSIGNMENT));
		return (free(token), 1);
	}
	else
		ft_mtaddlast_right(list, ft_newnode(token, state));
	free(token);
	return (1);
}
