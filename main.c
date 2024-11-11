/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/11 01:39:34 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "memtrack.h"

int main(void)
{
	t_mt	*list;

	list = ft_mtnew("Hello, World!");
	printf("%s\n", (char *)list->data);
	free(list);
	return (0);
}
