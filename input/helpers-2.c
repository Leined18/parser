/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:57:04 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/09 13:22:45 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * extract_quoted_token - Extrae un token delimitado por comillas.
 */
char	*extract_quoted_token(char *str, int *i)
{
	char	quote;
	int		start;

	if (!str[*i])
		return (NULL);
	quote = str[(*i)++];
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	// Saltar el cierre de la comilla
	return (ft_substr(str, start, *i - start - 1)); // Excluye las comillas
}

/**
 * extract_operator_token - Extrae un operador (|, >, <, >>, <<).
 */
char	*extract_operator_token(char *str, int *i)
{
	int	start;

	if (!i || !str)
		return (NULL);
	start = *i;
	if (str[*i + 1] == str[*i]) // Detectar operadores dobles (>>, <<)
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * extract_word_token - Extrae un token de palabra (sin comillas ni operadores).
 */
char	*extract_word_token(char *str, int *i)
{
	int	start;

	if (!str[*i])
		return (NULL);
	start = *i;
	while (!is_whitespace(str[*i]) && !is_operator(str[*i])
		&& !is_quoted(str[*i]) && str[*i])
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
