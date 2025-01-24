/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/24 15:59:31 by mvidal-h         ###   ########.fr       */
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

static int	pred(t_mt *lst, void *p)
{
	if (!lst)
		return (-1);
	if (lst->values.priority == *(int *)p)
	{
		lst->ptr_aux = "FOUND";
		return (1);
	}
	return (0);
}

t_mt	*ft_token_add_avalible(t_mt **tree, t_mt *new)
{
	if (!(*tree) || !new)
		return (NULL);
	if ((*tree)->values.priority <= new->values.priority && new->values.state != WORD)
	{
		if ((*tree)->vect[LEFT])
			return (ft_token_add_avalible(&(*tree)->vect[LEFT], new));
		return (ft_token_add_left(tree, new), NULL);
	}
	else
	{
		if ((*tree)->vect[RIGHT])
			return (ft_token_add_avalible(&(*tree)->vect[RIGHT], new));
		return (ft_token_add_right(tree, new), NULL);
	}
	return (NULL);
}

void	print_elements(t_mt *node, int depth)
{
	while (node)
	{
		for (int i = 1; i < depth; i++)
			ft_printf("      ");
		if (depth > 0)
			ft_printf("  |____[%s(%d)]\n", (char *)(node->data), node->values.priority);
		else
			ft_printf("[%s(%d)]\n", (char *)(node->data), node->values.priority);
		if (node->aux)
			print_elements(node->aux, depth + 1);
		node = node->vect[RIGHT];
	}
}

// t_mt	*ft_tree_builder(t_mt *tokens, t_mt **tree, int i)
// {
// 	t_mt	*aux[4];
// 	t_mt	*sub[2];

// 	if (!tokens) // Condición base para detener la recursión
// 		return (NULL);
// 	aux[0] = ft_mtsearch(tokens, &i, pred);
// 	if (!aux[0])
// 		return (ft_tree_builder(tokens, tree, i + 1));
// 	if (!tree)
// 	{
// 		sub[1] = ft_mtnew("ROOT", NULL, NONE);
// 		tree = &sub[1];
// 	}
// 	sub[0] = ft_mtsub(&tokens, aux[0]);
// 	aux[1] = ft_token_add_avalible(tree, sub[0]);
// 	if (sub[0]->values.state == PARENTESIS)
// 	{
// 		aux[2] = ft_tree_builder(sub[0]->aux, NULL, 0);
// 		if (aux[2])
// 			ft_token_add_avalible(tree, aux[2]);
// 	}
// 	if (!ft_tree_builder(tokens, tree, i))
// 		return (*tree);
// 	return (*tree);
// }


t_mt	*ft_tree_builder(t_mt *tokens, t_mt **tree, int i)
{
	t_mt	*aux[4];
	t_mt	*sub[2];

	if (!tokens) // Lista vacía, no hay árbol que construir
		return (NULL);
	print_elements(tokens, 0);
	while (tokens)
	{
		aux[0] = ft_mtsearch(tokens, &i, pred);// Buscar el nodo con la prioridad actual
		if (!aux[0])
		{
			ft_printf("BORRAR - nodo no encontrado, prioridad %d\n", i);
			i++; // Avanzar a la siguiente prioridad si no se encontró el nodo
			continue;
		}
		ft_printf("BORRAR - nodo encontrado = %s\n", aux[0]->data);
		if (!tree) // Crear la raíz del árbol si no existe
		{
			sub[1] = ft_mtnew("ROOT", NULL, NONE);
			tree = &sub[1];
			ft_printf("nodo tree creado = %s, prioridad %d\n", (*tree)->key, (*tree)->values.priority);
		}
		// Extraer el nodo actual y añadirlo al árbol
		sub[0] = ft_mtsub(&tokens, aux[0]); //SUSTRAER NO JUNTA BIEN LOS VECINOS (revisar)
		ft_printf("nodo extraido = %s, prioridad %d\n", sub[0]->data, i);
		print_elements(tokens, 0);
		aux[1] = ft_token_add_avalible(tree, sub[0]);
		if (sub[0]->values.state == PARENTESIS) // Si el nodo actual tiene paréntesis, construir su subárbol
		{
			aux[2] = ft_tree_builder(sub[0]->aux, NULL, 0);
			if (aux[2])
				ft_token_add_avalible(tree, aux[2]);
		}
	}
	return (*tree);
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
	tree = ft_tree_builder(tokens, NULL, 0);
	free(input_new);
	return (tree);
}
