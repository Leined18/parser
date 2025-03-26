/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/26 11:29:42 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*ft_parse_input(const char *input)
{
	t_mt	*tokens;
	t_mt	*tree;
	int		i;
	char	*input_new;

	i = 0;
	input_new = ft_strtrim(input, "\n\v\t ");
	if (!ft_validate_input(input_new))
		return (free(input_new), NULL);
	tokens = ft_tokenize(input_new, &i);
	if (!tokens)
		return (free(input_new), NULL);
	if (!ft_validate_list(tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	if (!ft_process_argument(&tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	ft_set_priority(tokens, (void *)&(int){0}, ft_set_node_priority);
	ft_check_swaps(&tokens);
	tree = ft_tree_builder(tokens);
	endizide_redin_pipes(tree);
	return (free(input_new), tree);
}
