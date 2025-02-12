/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_binary_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:25:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/02/12 19:32:52 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	endizide_nodes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	node->values.state = END;
	if (node->vect[LEFT])
		endizide_nodes(node->vect[LEFT]);
	if (node->vect[RIGHT])
		endizide_nodes(node->vect[RIGHT]);
	return (0);
}

int	endizide_redin_pipes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	if (ft_mtsearch_key(node, "<") && ft_mtsearch_key(node->vect[LEFT], "|"))
		endizide_nodes(node->vect[LEFT]);
	if (node->vect[LEFT])
		endizide_redin_pipes(node->vect[LEFT]);
	if (node->vect[RIGHT])
		endizide_redin_pipes(node->vect[RIGHT]);
	return (0);
}

t_mt	*take_word_parentesis(t_mt *list)
{
	if (!list)
		return (NULL);
	if (ft_mtcheck_state(list, PARENTESIS))
		list->aux = ft_tree_builder(list->aux);
	return (list);
}

//Comprueba si el nodo es OPERATOR o REDIRECTION
int	is_ope_or_red(t_mt *node)
{
	if (ft_mtcheck_state(node, REDIRECTION)
	|| ft_mtcheck_state(node, OPERATOR))
		return (1);
	return (0);
}

//Busca el operador (5 o 6) con mayor prioridad (valodr de prioridad mas alto)
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
			if (!ope || ft_mtcheck_priority(current, p) > 0) // solo si es igual, pero si quieres lo comparo
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
	if (op && op->vect[LEFT])// Romper la conexión con la parte izquierda
		ft_mtdisconnect(op, LEFT);
	if (op && op->vect[RIGHT]) // Romper la conexión con la parte derecha
		ft_mtdisconnect(op, RIGHT);
}

t_mt *ft_tree_builder(t_mt *list)
{
	t_mt	*operator;
	t_mt	*root;
	t_mt	*left;
	t_mt	*right;

	if (!list)
		return NULL;
	root = NULL;
	// Se busca el operador o redirección de menor prioridad en la lista
	operator = find_prior_operator(list);
	// Si no se encontra operador, se devuelve la lista tal cual (caso base)
	if (!operator)
		operator = take_word_parentesis(list);
	root = operator; // El primer operador encontrado será la raíz del árbol
	disconnect_operator(operator, &left, &right, list); // op redireccion
	// Construimos recursivamente los subárboles izquierdo y derecho
	root->vect[LEFT] = ft_tree_builder(left);
	root->vect[RIGHT] = ft_tree_builder(right);
	endizide_redin_pipes(root);
	return root;
}