/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:34:20 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/24 16:07:30 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_is_pipe_arg(char *p)
{
	char	*tmp;
	int		i;

	if (ft_strchr(p, '|'))
	{
		tmp = ft_strchr(p, '|');
		i = 1;
		while (tmp[i] && ft_strchr("\t\v\n", tmp[i]))
			i++;
		if (ft_isascii(tmp[i]) && tmp[i])
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	ft_is_all_closed(char *p)
{
	if (!p)
		return (0);
	if (!ft_check_is_close(p, '(', ')') || !ft_check_is_close(p, '{', '}')
		|| !ft_check_is_close_quote(p, '\'') || !ft_check_is_close_quote(p,
			'\"') || !ft_is_pipe_arg(p))
		return (0);
	return (1);
}

static int	ft_is_open(char *p)
{
	if (!p)
		return (0);
	if ((ft_check_is_close(p, '(', 0) && ft_check_is_close(p, '{', 0))
		&& (ft_check_is_close_quote(p, '\'') && ft_check_is_close_quote(p,
				'\"')) && ft_is_pipe_arg(p))
		return (0);
	return (1);
}

char	*advanced_readline(const char *prompt)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[BUFFER_SIZE];
	char	*line;
	int		status;
	ssize_t	nbytes;

	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, handle_sigint);
		close(pipefd[0]);
		line = readline(prompt);
		if (!line)
			exit(EXIT_EOF);
		if (!*line)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		nbytes = strlen(line) + 1;
		if (write(pipefd[1], line, nbytes) == -1)
		{
			perror("write");
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		nbytes = read(pipefd[0], buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			perror("read");
			close(pipefd[0]);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SIGINT)
		{
			g_sig_received = SIGINT;
			return (NULL);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_EOF)
			return (NULL);
		if (nbytes == 0)
			return (ft_strdup(""));
		return (strdup(buffer));
	}
}

int	ft_extend(char **input)
{
	char	*add;
	char	*ptr;

	if (!input || !*input)
		return (0);
	ptr = *input;
	if (!ft_is_open(ptr))
		return (1);
	while (!ft_is_all_closed(ptr))
	{
		add = advanced_readline("> ");
		if (!add)
			return (ft_printf(SYNTAX_ERROR3, ptr), 0);
		if (*add == '\0')
		{
			//stroin a ptr un \n. No pedo hacer ptr = ft_strjoin_free(&ptr, &"\n");
			continue ;
		}
		ptr = ft_strjoin_free(&ptr, &add);
		if (!ptr)
			return (0);
		*input = ptr;
	}
	return (*input = ptr, 1);
}
