/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/17 17:08:10 by danpalac         ###   ########.fr       */
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
	printf("key: %s\n", (char *)list->key);
	printf("Data: %s\n", (char *)list->data);
	printf("State: %d\n", list->values.state);
}

int	main(void)
{
	char			*input;
	t_mt			*list;
	t_hash_table	*ptable;

	input = get_next_line(0);
	input[ft_strlen(input) - 1] = '\0';
	list = NULL;
	list = parse_input(input);
	if (!list)
	{
		free(input);
		ft_error("Error\n", 1);
		return (1);
	}
	//list = tree_by_priority(&list);  falta implementar
	ptable = ft_mthash_new_table(3, "parser");
	if (!ptable)
		return (1);
	ptable->methods.add_child(ptable, "tree", list);
	ft_mtiter(list, NULL, print_state);
	ptable->methods.print(ptable);
	ptable->methods.free_table(ptable);
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