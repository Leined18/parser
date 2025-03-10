/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_parentheses_token.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:09:42 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/10 10:47:44 by danpalac         ###   ########.fr       */
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
	int	open;

	if (!i || !str)
		return (NULL);
	open = 0;
	if (str[(*i)++] == '(')
		open = 1;
	start = *i;
	while (str[*i] && open > 0)
	{
		if (str[*i] == '(')
			open += 1;
		else if (str[*i] == ')')
			open -= 1;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start - 1));
}
