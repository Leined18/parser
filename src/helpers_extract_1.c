/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_ft_extract_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:57:04 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 09:42:38 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_quoted_token - Extrae un token delimitado por comillas.
 */
char	*ft_extract_quoted_token(char *str, int *i)
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
 * ft_extract_operator_token - Extrae un operador (|, >, <, >>, <<).
 */
char	*ft_extract_operator_token(char *str, int *i)
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
 * ft_extract_word_token - Extrae un token de palabra (sin comillas ni operadores).
 */
char	*ft_extract_word_token(char *str, int *i)
{
	int	start;

	if (!i || !str)
		return (NULL);
	start = *i;
	while (!ft_strchr("()<>\"\'| \t\n", str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
