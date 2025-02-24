/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_parentheses_token.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:09:42 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 12:43:32 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_parentheses_token
 * 	- Extrae un token de un parentesis (sin los parentesis '()')
 **/

char	*ft_extract_parentheses_token(char *str, int *i)
{
	int	start;

	if (!i || !str)
		return (NULL);
	if (str[*i] == '(')
		*i += 1;
	start = *i;
	while (str[*i] != ')' && str[*i])
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
