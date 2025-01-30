/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 11:07:02 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// Comprueba si el nodo es 5 o 6
int	is_ope_or_red(t_mt *node)
{
	if (ft_mtcheck_state(node, REDIRECTION) // probamo
		|| ft_mtcheck_state(node, OPERATOR))
		// estamos checkeando estados y no prioridades
		return (1);
	return (0);
}

// Busca el operador (5 o 6) con mayor prioridad (valodr de prioridad mas alto)
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
			if (!ope || ft_mtcheck_priority(current, p) < 0)
				// solo si es igual, pero si quieres lo comparo
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
	if (op && op->vect[LEFT]) // Romper la conexión con la parte izquierda
		ft_mtdisconnect(op, LEFT);
	if (op && op->vect[RIGHT]) // Romper la conexión con la parte derecha
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
	// Se busca el operador o redirección de menor prioridad en la lista
	operator= find_prior_operator(list);
	// Si no se encontra operador, se devuelve la lista tal cual (caso base)
	if (!operator)
		return (list);
	root = operator;
	// El primer operador encontrado será la raíz del árbol
	disconnect_operator(operator, & left, &right, list); // op redireccion
	// Construimos recursivamente los subárboles izquierdo y derecho
	/* if (ft_mtcheck_state(operator, PARENTESIS))
		operator->aux = ft_tree_builder(operator->aux); */
	root->vect[LEFT] = ft_tree_builder(left);
	root->vect[RIGHT] = ft_tree_builder(right);
	return (root);
}

t_mt	*ft_parse_input(const char *input)
{
	t_mt	*tokens;
	int		i;
	char	*input_new;

	i = 0;
	input_new = ft_strdup(input);
	if (!ft_validate_input(input_new))
		return (free(input_new), NULL);
	if (!ft_extend((char **)&input_new))
		return (free(input_new), NULL);
	tokens = ft_tokenize(input_new, &i); // Tokenizamos el input en nodos
	if (!tokens)
		return (free(input_new), NULL); // echo "$PATH"
	if (!ft_validate_list(tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	if (!ft_process_argument(&tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	free(input_new);
	return (tokens);
}
