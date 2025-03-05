/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:15:25 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/03 09:14:50 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * tokenize - Divide una línea de entrada en tokens.
 * @str: Cadena de entrada.
 * @return: Lista de tokens.
 */

t_mt	*ft_tokenize(const char *input, int *i)
{
	t_pstate	state;
	t_mt		*list;
	char		*str;

	if (!input)
		return (NULL);
	state = START;
	list = NULL;
	str = ft_strdup(input);
	while (str[*i])
	{
		state = ft_transition(state, str[*i]);
		if (state == END)
			break ;
		if (!ft_process_token(str, i, &list, state))
			return (NULL);
	}
	return (free(str), list);
}
