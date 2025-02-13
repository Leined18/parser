/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/13 11:29:04 by mvidal-h         ###   ########.fr       */
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

int	need_redirection_swap(t_mt *tokens)
{
	if (!ft_mtcheck_key(tokens->vect[RIGHT], "<"))
		return (1);
	if (!ft_mtcheck_key(tokens->vect[RIGHT], ">"))
		return (1);
	if (!ft_mtcheck_key(tokens->vect[RIGHT], ">>"))
		return (1);
	return (0);
}

/**
 * @brief intercambia los nodos curr y el de la direccion indicada
 *
 */

int	ft_mtexchange(t_mt **lst, t_mt *curr, t_direction direction)
{
	t_mt	*prev;
	t_mt	*next;
	t_mt	*n_direc;
	int		oposite;

	if (!curr || !curr->vect[direction])
		return (1);
	n_direc = curr->vect[direction];
	if (*lst == curr || *lst == n_direc)
		ft_mtswap(lst, RIGHT);
	else
	{
		oposite = ft_mtoposite_direction(direction);
		next = n_direc->vect[direction];
		prev = curr->vect[oposite];
		curr->vect[direction] = next;
		n_direc->vect[direction] = curr;
		n_direc->vect[oposite] = prev;
		curr->vect[oposite] = n_direc;
		if (prev)
			prev->vect[direction] = n_direc;
		if (next)
			next->vect[oposite] = curr;
	}
	return (0);
}


void	check_swaps(t_mt **tokens)
{
	t_mt	*cur;

	if (!tokens || !*tokens)
		return ;
	if (ft_mtcheck_state(*tokens, COMMAND) && need_redirection_swap(*tokens))
	{
		ft_mtswap(tokens, RIGHT);
		//ft_printf("Cambio swap primeros. Ahora tokens es %s\n", (*tokens)->key);
		//print_tokens(*tokens, 0);
	}
	cur = *tokens;
	while (cur)
	{
		//ft_printf("while curr es %s\n", cur->key);
		if (!ft_mtcheck_key(cur, "<"))
		{
			//ft_printf("encontrado <\n");
			if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
			{
			//	ft_printf("left es command asi que entro en exchange\n");
				ft_mtexchange(tokens, cur, LEFT);
			//	print_tokens(*tokens, 0);
			}
			//else
			//	ft_printf("left NO es command asi que avanzo\n");
		}
		cur = cur->vect[RIGHT];
	}
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
		return (free(input_new), NULL);
	if (!ft_validate_list(tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	if (!ft_process_argument(&tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	ft_set_priority(tokens, (void *)&(int){0}, set_node_priority);
	//check_swaps(&tokens);
	//print_tokens(tokens, 0);
	tree = ft_tree_builder(tokens);
	//ft_printf("\n\n\n");
	//print_tree(tree, 0);
	return (free(input_new), tree);
}
