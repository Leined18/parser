/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/14 10:37:18 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	tokenize(char *str, t_mt **list)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok(str, " ");
	return (0);
	while (token)
	{
		printf("Token %d: %s\n", i, token);
		ft_mtpush_data(list, token);
		token = ft_strtok(NULL, " ");
		i++;
	}
	return (0);

}

int	main(void)
{
	char	*str;
	t_mt	*tracker;

	str = ft_strdup("Hello world");
	tokenize(str, &tracker);

	ft_mtprint(tracker, 0);
	(void)str;
	(void)tracker;
	return (0);
}
