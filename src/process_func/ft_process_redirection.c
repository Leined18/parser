/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:31:27 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 11:31:32 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_process_redirection(char *input, int *i, t_mt **list)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_operator_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, REDIRECTION));
		free(token);
	}
	return (1);
}
