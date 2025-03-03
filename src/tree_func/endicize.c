/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endicize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:07:08 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:07 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	endizide_nodes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	node->values.state = END;
	if (node->vect[LEFT])
		endizide_nodes(node->vect[LEFT]);
	if (node->vect[RIGHT])
		endizide_nodes(node->vect[RIGHT]);
	return (0);
}


// Bash obvia todo lo que haya mas allá del ultimo comando de una serie 
// de tuberias antes de una redirección de entrada. Usamos esta función para
// marcar como END todos los nodos que no sean el último comando de una serie
// de tuberias antes de una redirección de entrada.
int	endizide_redin_pipes(t_mt *node)
{
	if (!node || node->values.state == END)
		return (0);
	if (ft_mtsearch_key(node, "<") && ft_mtsearch_key(node->vect[LEFT], "|"))
		endizide_nodes(node->vect[LEFT]);
	if (node->vect[LEFT])
		endizide_redin_pipes(node->vect[LEFT]);
	if (node->vect[RIGHT])
		endizide_redin_pipes(node->vect[RIGHT]);
	return (0);
}
