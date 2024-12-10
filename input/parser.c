/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/10 12:43:31 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_mt	*parse_input(const char *input)
{
	e_state	state;
	t_mt	*list;
	char	*str;
	int		i;

	i = 0;
	state = START;
	list = NULL;
	str = ft_strdup(input);
	while (str[i])
	{
		state = transition(state, str[i]);
		if (state == END)
			break ;
		else if (state == WORD)
			process_word(str, &i, &list);
		else if (state == QUOTE)
			process_quote(str, &i, &list);
		else if (state == OPERATOR)
			process_operator(str, &i, &list);
		else if (state == REDIRECTION)
			process_redirection(str, &i, &list);
		else
			i++;
	}
	free(str);
	return (list);
}
