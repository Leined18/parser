/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 18:03:48 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * parser - Main parser function to create a hash table and organize input
 * @input: The input string
 * Returns: A hash table with the parsed data
 */

void	print_state(t_mt *list, void *a)
{
	(void)a;
	if (!list)
		return ;
	printf("\n");
	printf("key: %s\n", (char *)list->key);
	printf("Data: %s\n", (char *)list->data);
	printf("State: %d\n", list->values.state);
}

// Función auxiliar para imprimir los espacios
void print_spaces(int level)
{
	for (int i = 0; i < level; i++)
		ft_printf("   ");
}

// Función principal para imprimir el árbol binario
void print_tree(t_mt *root, int level)
{
	if (root == NULL)
	{
		print_spaces(level);
		ft_printf("NULL\n");
		return;
	}
	// Imprimir el nodo actual
	print_spaces(level);
	ft_printf("Node: %s (Priority: %d)\n", root->key, root->values.priority);

	// Imprimir hijos izquierdo y derecho
	print_spaces(level);
	ft_printf("Left:\n");
	print_tree(root->vect[LEFT], level + 1);

	print_spaces(level);
	ft_printf("Right:\n");
	print_tree(root->vect[RIGHT], level + 1);
}


int	main(void)
{
	char	*input;
	t_mt	*list;

	input = get_next_line(0);
	input[ft_strlen(input) - 1] = '\0';
	list = NULL;
	list = ft_parse_input(input);
	if (!list)
	{
		free(input);
		ft_error("Error\n", 1);
		return (1);
	}
	// ft_mtiter(list, NULL, print_state);
	print_tree(list, 0);
	ft_mtclear(&list);
	free(input);
	ft_successful("Success\n", 1);
	return (0);
}

/* t_hash_table	*parser(char *input)
{
	t_hash_table	*ptable;
	t_mt			*tree;

	if (!input)
		return (NULL);
	ptable = ft_mthash_new_table(3, "parser");
	if (!ptable)
		return (NULL);
	tree = tokenize(input);
	parse_input(input);
	if (!tree)
	{
		ft_mthash_table_free((void **)&ptable);
		return (NULL);
	}
	ptable->methods.add_child(ptable, "tree", tree);
	return (ptable);
} */