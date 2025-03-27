/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:05:18 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/27 11:03:53 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "mt.h"

# define SYNTAX_ERROR "syntax error near unexpected token `%s'\n"

typedef enum t_pstate
{
	END,
	START,
	PARENTESIS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION,
	OPERATOR,
	EXPANSION,
	WILDCARD,
	ASSIGNMENT,
	WORD,
	COMMAND,
	ARGUMENT,
	COMMENT,
	MAS_PSTATE
}			t_pstate;

// state.c

int			ft_mtcheck_state(t_mt *mt, int state);
t_pstate	ft_transition(t_pstate current, char c);

// helpers
t_pstate	handle_start(char c);
t_pstate	handle_word(char c);
t_pstate	handle_redirection(char c);
t_pstate	handle_quote(char c);
t_pstate	handle_operator(char c);
t_pstate	handle_parentesis(char c);
t_pstate	handle_expantion(char c);

// manage_signals.c
void		handle_sigint(int sig);

// tokenizer.c

t_mt		*ft_tokenize(const char *input, int *i);

// helpers_priority

void		ft_set_priority(t_mt *list, void *param, void (*func)(t_mt *,
					void *));
void		ft_set_node_priority(t_mt *node, void *param);
int			ft_get_priority(char *str);
t_mt		*ft_newnode(char *data, t_pstate state);

// extend

int			ft_extend(char **input);
char		*advanced_readline(const char *prompt);

// validate

int			ft_validate_list(t_mt *list);
int			ft_validate_input(char *s);
void		ft_set_node_priority(t_mt *node, void *param);
int			ft_get_priority(char *str);
t_mt		*ft_newnode(char *data, t_pstate state);
void		ft_token_add_left(t_mt **list, t_mt *new);
void		ft_token_add_right(t_mt **list, t_mt *new);

// helpers_check.c

void		ft_check_swaps(t_mt **tokens);
int			ft_check_operators_mt(t_mt *op, int *error);
int			ft_check_redirections_mt(t_mt *op, int *error);
int			ft_check_parentesis_mt(t_mt *op, int *error);
int			ft_check_is_close(char *input, char open, char close);
int			ft_check_is_close_quote(char *input, char quote);
char		*ft_strjoin_free(char **s1, char **s2, int free_s2);
// helpers_process_1.c

int			ft_process_argument(t_mt **list);

// helpers_extract.c
char		*ft_extract_quoted_token(char *str, int *i);
char		*ft_extract_operator_token(char *str, int *i);
char		*ft_extract_word_token(char *str, int *i, char *disallow);
char		*ft_extract_parentheses_token(char *str, int *i);
char		*ft_extract_expantion_token(char *str, int *i);
char		*ft_extract_token(char *str, int *i, char *allow,
				int (*funtion)(int));
// ft_process_token.c
int			ft_process_token(char *input, int *i, t_mt **list, t_pstate state);

// ft_process.c
int			ft_process_word(char *input, int *i, t_mt **list, t_pstate state);
int			ft_process_operator(char *input, int *i, t_mt **list);
int			ft_process_parentheses(char *input, int *i, t_mt **list, char *key);
int			ft_process_redirection(char *input, int *i, t_mt **list);
int			ft_process_quote(char *input, int *i, t_mt **list, t_pstate state);
int			ft_process_expantion(char *input, int *i, t_mt **list);

// print_tree.c.c
int			print_tree(t_mt *root, int level);

// print_tokens
void		print_tokens(t_mt **tokens);

// check_follow_commands.c
void		check_follow_commands(t_mt **token);

// check_follow_redout.c
void		check_follow_redout(t_mt **token);

// ft_check_swaps.c
void		ft_check_swaps(t_mt **token);

// create_binary_tree.c
t_mt		*ft_tree_builder(t_mt *list);
int			is_ope_or_red(t_mt *node);

// endicize.c
int			endizide_nodes(t_mt *node);
int			endizide_redin_pipes(t_mt *node);

// ft_advanced_readline

char		*advanced_readline(const char *prompt);

#endif // INPUT_H