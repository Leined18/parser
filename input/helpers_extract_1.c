/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_extract_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:57:04 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/12 12:14:23 by danpalac         ###   ########.fr       */
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

	if (!str || !i)
		return (NULL);
	quote = str[(*i)++]; // Guardar el tipo de comilla
	start = *i;          // Guardar el inicio del token
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote) //"_" " "
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

	if (!i || !str)
		return (NULL);
	start = *i;
	while (!is_whitespace(str[*i]) && !is_operator(str[*i])
		&& !is_quoted(str[*i]) && str[*i] && !is_redirection(str[*i])
		&& !is_parentesis(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
