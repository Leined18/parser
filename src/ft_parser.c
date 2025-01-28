/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 16:53:40 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*ft_parse_input(const char *input)
{
	t_mt	*tokens;
	int		i;
	char	*input_new;

	i = 0;
	input_new = ft_strdup(input);
	if (!ft_validate_input(input_new))
		return (free(input_new), NULL);
	if (!ft_extend_until_close((char **)&input_new))
		return (free(input_new), NULL);
	tokens = ft_tokenize(input_new, &i); // Tokenizamos el input en nodos
	if (!tokens)
		return (free(input_new), NULL);
	if (!ft_validate_list(tokens))
		return (ft_mtclear(&tokens), free(input_new), NULL);
	free(input_new);
	return (tokens);
}
