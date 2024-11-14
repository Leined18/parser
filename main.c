/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/14 16:18:49 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char **argv)
{
	char	*str;
	t_mt	*cmd;

	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}
	cmd = NULL;
	str = ft_strdup(argv[1]);
	tokenize(str, &cmd);
	ft_mtprint(cmd, 1, "\n");
	if (!parser(&cmd))
		return (1);
	ft_mtprint_n(cmd, 1, "\n");
	ft_mtprint(cmd, 1, "\n");
	(void)str;
	return (0);
}
