/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:15:25 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 11:23:35 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * tokenize - Divide una línea de entrada en tokens.
 * @str: Cadena de entrada.
 * @return: Lista de tokens.
 */
t_mt	*tokenize(const char *input, int *i)
{
	e_state	state;
	t_mt	*list;
	char	*str;

	if (!input)
		return (NULL);
	state = START;
	list = NULL;
	str = ft_strdup(input);
	while (str[*i])
	{
		state = transition(state, str[*i]);
		if (state == END)
			break ;
		process_token(str, i, &list, state);
	}
	free(str);
	return (list);
}
