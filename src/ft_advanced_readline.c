/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_readline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:22:19 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/26 11:29:25 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*a_parent(int *pipefd, int pid)
{
	int		status;
	ssize_t	nbytes;
	char	buffer[BUFFER_SIZE];

	close(pipefd[1]);
	nbytes = read(pipefd[0], buffer, BUFFER_SIZE);
	if (nbytes == -1)
		return (perror("read"), close(pipefd[0]), NULL);
	(close(pipefd[0]), waitpid(pid, &status, 0));
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SIGINT)
		return (g_sig_received = SIGINT, NULL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_EOF)
		return (NULL);
	if (nbytes == 0)
		return (ft_strdup(""));
	buffer[nbytes - 1] = 0;
	return (strdup(buffer));
}

static void	a_child(int *pipefd, char *prompt)
{
	char	*line;
	ssize_t	nbytes;

	(signal(SIGQUIT, SIG_DFL), signal(SIGINT, handle_sigint));
	close(pipefd[0]);
	line = readline(prompt);
	if (!line)
		exit(EXIT_EOF);
	if (!*line)
		(free(line), exit(EXIT_SUCCESS));
	nbytes = strlen(line) + 1;
	if (write(pipefd[1], line, nbytes) == -1)
		(perror("write"), free(line), exit(EXIT_FAILURE));
	(free(line), close(pipefd[1]));
	exit(EXIT_SUCCESS);
}

char	*advanced_readline(const char *prompt)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), NULL);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), NULL);
	if (pid == 0)
		return (a_child(pipefd, (char *)prompt), NULL);
	else
		return (a_parent(pipefd, pid));
	return (NULL);
}
