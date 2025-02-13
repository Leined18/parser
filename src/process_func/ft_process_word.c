/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:32:14 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/13 10:34:40 by danpalac         ###   ########.fr       */
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
	t_mt	*mt_token;
	t_mt	*add;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_word_token(input, i, " \t\n|&;=<>\"'`$");
	if (!token)
		return (0);
	add = NULL;
	if (input[*i] == '=') // guarda el token como ASSIGNMENT si tiene '='
	{
		(*i)++;
		ft_process_token(input, i, &add, transition(START, input[*i]));
		mt_token = ft_newnode(token, ASSIGNMENT);
		ft_mtpush_last(&mt_token->aux, &add, RIGHT);
		ft_mtaddlast_right(list, mt_token);
		return (free(token), 1);
	}
	else
		ft_mtaddlast_right(list, ft_newnode(token, state));
	free(token);
	return (1);
}
