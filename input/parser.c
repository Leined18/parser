/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/23 14:52:23 by mvidal-h         ###   ########.fr       */
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


static void	ft_set_priority(t_mt *list, void *param, void (*func)(t_mt *, void *))
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
		return (1);
	return (0);
}

t_mt	**ft_token_add_avalible(t_mt *token, t_mt *new)
{
	if (!token || !new)
		return NULL;
	if (!token->vect[LEFT])
		ft_token_add_left(token, new);
	else
		ft_token_add_right(token, new);
	return &new;
}


t_mt *ft_tree_builder(t_mt *tokens, t_mt **tree, int *i)
{
    t_mt    *current;
    t_mt    *aux[2];
    t_mt    *sub;

    if (!tokens) // Condición base para detener la recursión
        return NULL;
    current = tokens;
	i = 0;
	if (!*tree)
    	(*tree) = ft_mtnew("ROOT",NULL, NONE);
    aux[0] = ft_mtsearch(current, &i, pred);
	if (!aux[0])
		return (ft_tree_builder(current, tree, &i + 1));
	sub = ft_mtsub(current, aux[0]);
	if (sub->values.state == PARENTESIS)
	{
		aux[1] = ft_tree_builder(sub->aux, NULL, &i);
		ft_mtdelete(&sub);
		ft_token_add_avalible(tree, aux[1]);
	}
	else
		return (ft_tree_builder(current, ft_token_add_avalible(tree, sub), &i));
    return tree;
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
	tree = ft_tree_builder(tokens, NULL, &i);
	free(input_new);
	return (tree);
}
