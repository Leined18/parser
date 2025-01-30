/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_word_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:10:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 12:18:57 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_word_token
	- Extrae un token de palabra (sin comillas ni operadores).
 */
char	*ft_extract_word_token(char *str, int *i)
{
	int	start;

	if (!i || !str)
		return (NULL);
	start = *i;
	while (!ft_strchr("()<>\"\'| \t\n$", str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
