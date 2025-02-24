/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_node_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/24 13:03:07 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*ft_newnode(char *data, t_pstate state)
{
	t_mt	*node;

	node = ft_mtnew(data, ft_strdup(data), STRING);
	if (!node)
		return (NULL);
	node->values.state = state;
	return (node);
}

void	ft_token_add_right(t_mt **list, t_mt *new)
{
	t_mt	*tmp;

	if (!list || !new || (*list)->vect[RIGHT])
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	tmp->vect[RIGHT] = new;
}

void	ft_token_add_left(t_mt **list, t_mt *new)
{
	t_mt	*tmp;

	if (!list || !new || (*list)->vect[LEFT])
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	tmp->vect[LEFT] = new;
}
