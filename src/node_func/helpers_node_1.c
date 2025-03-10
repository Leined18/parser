/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_node_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/10 16:53:38 by mvidal-h         ###   ########.fr       */
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
	node->values.swap_checked = FALSE;
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
