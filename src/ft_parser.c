/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/31 20:33:29 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	ft_set_priority(t_mt *list, void *param, void (*func)(t_mt *,
			void *))
{
	if (!list || !func)
		return ;
	ft_mtiter(list, param, func);
}

void	print_elements(t_mt *node, int depth)
{
	while (node)
	{
		for (int i = 1; i < depth; i++)
			ft_printf("      ");
		if (depth > 0)
			ft_printf("  |____[%s(p:%d)(e:%d)]\n", (char *)(node->data), node->values.priority, node->values.state);
		else
			ft_printf("[%s(P:%d)(e:%d)]\n", (char *)(node->data), node->values.priority, node->values.state);
		if (node->aux)
			print_elements(node->aux, depth + 1);
		node = node->vect[RIGHT];
	}
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
	return root;
}

t_mt	*ft_parse_input(const char *input)
{
	t_mt	*tokens;
	t_mt	*tree;
	int		i;
	char	*input_new;

	i = 0;
	input_new = ft_strdup(input);
	if (!ft_validate_input(input_new))
		return (free(input_new), NULL);
	if (!ft_extend(&input_new))
		return (free(input_new), NULL);
	tokens = ft_tokenize(input_new, &i); // Tokenizamos el input en nodos
	if (!tokens)
		return (free(input_new), NULL); // echo "$PATH"
	if (!ft_validate_list(tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	if (!ft_process_argument(&tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	ft_set_priority(tokens, (void *)&(int){0}, set_node_priority);
	//print_elements(tokens, 0);
	tree = ft_tree_builder(tokens);
	free(input_new);
	return (tree);
}
