/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/27 11:34:03 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_mt	*create_tree(char *name_root, int argc, ...)
{
	t_mt	*root;
	t_mt	*node;
	va_list	args;

	va_start(args, argc);
	root = ft_mtnew(name_root, NULL, BRANCH);
	while (argc--)
	{
		node = va_arg(args, t_mt *);
		ft_mtadd_child(root, node);
	}
	va_end(args);
	return (root);
}

t_hash_table	*parser(char *input)
{
	t_hash_table	*ptable;
	t_mt			*list;

	if (!input)
		return (NULL);
	ptable = ft_mtnew_hash_table(3);
	if (!ptable)
		return (NULL);
	list = NULL;
	list = ft_splitmt(input, ' ');
	ptable->put(ptable, "input", list, BRANCH);
	list = NULL;
	list = create_tree("CHR", 6, ft_mtnew("Description",
				ft_strdup("Este nodo es para descripciones\naqui puedes guardar para es el arbol\n por ejemplo CHR significa CommandHierarchyRoot"),
				LEAF), ft_mtnew("AliasBranch", NULL, LEAF),
			ft_mtnew("KeywordBranch", NULL, LEAF), ft_mtnew("FunctionsBranch",
				NULL, LEAF), ft_mtnew("BuiltinsBranch", NULL, LEAF),
			ft_mtnew("PathCommandsBranch", NULL, LEAF));
	ptable->add(ptable, list);
	return (ptable);
}

int	main(int argc, char **argv)
{
	t_hash_table	*ptable;

	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}
	ptable = parser(argv[1]);
	if (!ptable)
		return (1);
	ptable->replace_key(ptable, "Description", "description1");
	ptable->print(ptable);
	printf("%s\n", (char *)ptable->get_data(ptable, "description1"));
	ptable->free_table(ptable);
	return (0);
}
