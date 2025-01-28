/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/28 17:30:00 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	extend_until_close(char **input)
{
	char	*add;
	char	*ptr;

	if (!input || !*input)
		return (0);
	if ((check_is_close(*input, '(', 0) && check_is_close(*input, '{', 0))
		&& (check_is_close_quote(*input, '\'') && check_is_close_quote(*input,
				'\"')))
		return (1);
	ptr = *input;
	while (!check_is_close(ptr, '(', ')') || !check_is_close(ptr, '{', '}')
		|| !check_is_close_quote(ptr, '\'') || !check_is_close_quote(ptr, '\"'))
	{
		ft_printf("> ");
		add = get_next_line(0);
		if (!add)
			return (0);
		ptr = ft_strjoin_free(&ptr, &add);
		if (!ptr)
			return (0);
		*input = ptr; // Actualizamos el input con el nuevo contenido
	}
	return (1); // Paréntesis balanceados
}

static int	validate_list(t_mt *list)
{
	t_mt	*current;
	int		res;

	if (!list)
		return (0);
	current = list;
	res = 0;
	while (current)
	{
		if (current->values.state == REDIRECTION)
			res = check_redirections_mt(current);
		if (current->values.state == OPERATOR)
			res = check_operators_mt(current);
		if (current->values.state == PARENTESIS)
		{ // Paréntesis
			if (!current->aux)
				return (ft_printf("syntax error near unexpected token `)'\n"),
					0);
			res = !validate_list(current->aux);
		}
		current = current->vect[RIGHT];
	}
	return (res == 0);
}

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

t_mt	*find_parentesis_tree(t_mt *list)
{
	t_mt	*current;

	if (!list)
		return (NULL);
	current = list;
	while (current)
	{
		if (ft_mtcheck_state(current, PARENTESIS) == 0)
			current->aux = ft_tree_builder(current->aux);
		current = current->vect[RIGHT];
	}
	return (list);
}

//Comprueba si el nodo es 5 o 6
int	is_ope_or_red(t_mt *node)
{
	if (ft_mtcheck_state(node, REDIRECTION) == 0 // probamo
	|| ft_mtcheck_state(node, OPERATOR) == 0) // estamos checkeando estados y no prioridades
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
			if (!ope || ft_mtcheck_priority(current, p) < 0) // solo si es igual, pero si quieres lo comparo
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
		return (find_parentesis_tree(list));
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
	if (!extend_until_close((char **)&input_new))
		return (NULL);
	tokens = tokenize(input_new, &i); // Tokenizamos el input en nodos
	if (!tokens)
		return (free(input_new), NULL);
	if (!validate_list(tokens))
		(ft_mtclear(&tokens), tokens = NULL);
	ft_set_priority(tokens, (void *)&(int){0}, set_node_priority);
	print_elements(tokens, 0);
	tree = ft_tree_builder(tokens);
	free(input_new);
	return (tree);
}
