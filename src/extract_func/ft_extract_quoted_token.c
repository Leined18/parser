/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_quoted_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:15 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 11:11:24 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_quoted_token - Extrae un token delimitado por comillas.
 */

char	*ft_extract_quoted_token(char *str, int *i)
{
	char quote;
	int start;

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
