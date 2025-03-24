/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:02:59 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/24 14:03:05 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_SIGNAL_H
# define GLOBAL_SIGNAL_H

# include <signal.h>

#define EXIT_SIGINT 42  // Código especial para SIGINT (Ctrl+C)
#define EXIT_EOF 43     // Código especial para EOF (Ctrl+D)

extern volatile sig_atomic_t	g_sig_received;

#endif // GLOBAL_SIGNAL_H