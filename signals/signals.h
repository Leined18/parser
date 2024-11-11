#ifndef SIGNALS_H
# define SIGNALS_H

// Include any necessary headers here
# include "config.h"
# include "minishell.h"
# include <signal.h>

// Declare your function prototypes here
void	signal_handler(int signal);
void	sigaction_handler(int signal, siginfo_t *info, void *context);
void	sigaction_setup(void (*function)(int, siginfo_t *, void *));
void	signal_setup(void(funtion)(int signal));
int		send_signal(int pid, int signal);

#endif // SIGNALS_H