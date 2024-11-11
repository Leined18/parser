/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:33:24 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/11 10:39:14 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "input.h"

int	parse_arguments(t_memory *mem, int ac, char **av, char **ev)
{
	if (ac >= 3)
	{
		write(1, "Usage: ./minishell\n", 19);
		return (0);
	}
	if (!init_memory(mem, ac, av, ev))
		return (0);
	return (1);
}
