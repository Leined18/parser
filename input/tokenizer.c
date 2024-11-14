/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:15:25 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/14 12:15:35 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	tokenize(char *str, t_mt **list)
{
	char *token;
	int i;

	i = 0;
	if (!str || !list)
		return (1);
	token = ft_strtok(str, " ");
	while (token)
	{
		ft_mtpush_data(list, token);
		token = ft_strtok(NULL, " ");
		i++;
	}
	return (0);
}
