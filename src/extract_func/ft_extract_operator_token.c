/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_operator_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:10:52 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 12:56:08 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_operator_token - Extrae un operador (|, >, <, >>, <<, &, &&).
 */
char	*ft_extract_operator_token(char *str, int *i)
{
	int	start;

	if (!i || !str)
		return (NULL);
	start = *i;
	if (str[*i + 1] == str[*i])
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}
