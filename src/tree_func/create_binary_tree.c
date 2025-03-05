/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:25:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/03 17:07:23 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*take_word_parentesis(t_mt *list)
{
	if (!list)
		return (NULL);
	if (ft_mtcheck_state(list, PARENTESIS))
		list->aux = ft_tree_builder(list->aux);
	return (list);
}

int	is_ope_or_red(t_mt *node)
{
	if (ft_mtcheck_state(node, REDIRECTION) || ft_mtcheck_state(node, OPERATOR))
		return (1);
	return (0);
}

t_mt	*find_prior_operator(t_mt *list)
{
	t_mt	*current;
	t_mt	*ope;
	int		p;

	current = list;
	ope = NULL;
	while (current)
	{
		if (is_ope_or_red(current))
		{
			if (ope)
				p = ope->values.priority;
			if (!ope || ft_mtcheck_priority(current, p) > 0)
				ope = current;
		}
		current = current->vect[RIGHT];
	}
	return (ope);
}

void	disconnect_operator(t_mt *op, t_mt **left, t_mt **right, t_mt *list)
{
	*right = op->vect[RIGHT];
	*left = list;
	if (*left == op)
		*left = NULL;
	if (op && op->vect[LEFT])
		ft_mtdisconnect(op, LEFT);
	if (op && op->vect[RIGHT])
		ft_mtdisconnect(op, RIGHT);
}

t_mt	*ft_tree_builder(t_mt *list)
{
	t_mt	*operator;
	t_mt	*root;
	t_mt	*left;
	t_mt	*right;

	if (!list)
		return (NULL);
	root = NULL;
	operator = find_prior_operator(list);
	if (!operator)
		operator = take_word_parentesis(list);
	root = operator;
	disconnect_operator(operator, & left, &right, list);
	root->vect[LEFT] = ft_tree_builder(left);
	root->vect[RIGHT] = ft_tree_builder(right);
	return (root);
}
