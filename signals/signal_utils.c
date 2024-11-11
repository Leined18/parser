/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:54:40 by danpalac          #+#    #+#             */
/*   Updated: 2024/10/30 10:05:48 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * sigaction_setup - Configura el manejador de señales avanzado
 * @function: Puntero a la función manejadora de señales que recibe
 *            parámetros adicionales de información de la señal.
 *
 * Esta función configura varios manejadores de señal usando `sigaction`
 * con `SA_SIGINFO` habilitado para obtener información extra sobre cada señal.
 */
void	sigaction_setup(void (*function)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	act.sa_sigaction = function;
	act.sa_flags = SA_SIGINFO; // Habilita siginfo_t para el manejador avanzado
	sigemptyset(&act.sa_mask); // Vacía la máscara de señales durante el manejo
	// Configurar señales comunes
	sigaction(SIGINT, &act, NULL);  // Ctrl+C
	sigaction(SIGTERM, &act, NULL); // Terminación solicitada
	sigaction(SIGUSR1, &act, NULL); // Señal de usuario 1
	sigaction(SIGUSR2, &act, NULL); // Señal de usuario 2
	sigaction(SIGALRM, &act, NULL); // Alarma temporizada
	sigaction(SIGCHLD, &act, NULL); // Cambio en el estado del hijo
}

/**
 * signal_setup - Configuración básica de manejadores de señal
 * @function: Puntero a la función manejadora de señales
 *
 * Esta función configura un manejador para señales comunes
 * usando `signal` sin soporte para `siginfo_t`.
 */
void	signal_setup(void (*function)(int))
{
	signal(SIGUSR1, function);
	signal(SIGUSR2, function);
	signal(SIGINT, function);
	signal(SIGTERM, function);
}

/**
 * send_signal - Envía una señal a un proceso específico
 * @pid: ID del proceso destino
 * @signal: Señal a enviar
 *
 * Retorna TRUE si la señal fue enviada exitosamente, o FALSE en caso de error.
 */
int	send_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		return (FALSE);
	return (TRUE);
}
