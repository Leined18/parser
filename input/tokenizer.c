/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:15:25 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/02 13:30:52 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"

/**
 * tokenize - Divide una línea de entrada en tokens.
 * @str: Cadena de entrada.
 * @return: Lista de tokens.
 */
t_mt	*tokenize(char *str)
{
	t_mt	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		parse_token(str, &i, &tokens);
	return (tokens);
}
