/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:56:17 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/26 11:23:58 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	handle_sigint(int sig)
{
	g_sig_received = sig;
	if (g_sig_received == SIGINT)
		exit(EXIT_SIGINT);
}
