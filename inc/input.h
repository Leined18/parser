#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "mt.h"

# define SYNTAX_ERROR "syntax error near unexpected token `%s'\n"

typedef enum e_pstate
{
	END,          // Estado final
	START,        // Estado inicial
	PARENTESIS,   // Procesando paréntesis
	SINGLE_QUOTE, // Procesando contenido entre comillas
	DOUBLE_QUOTE, // Procesando contenido entre comillas dobles
	REDIRECTION,  // Procesando redirecciones: >, >>, << (heredoc incluido)
	OPERATOR,     // Operadores como |, &&, ||
	EXPANSION,    // Procesando expansiones como $, ${}
	ASSIGNMENT,   // Procesando una asignación (VAR=value)
	WORD,         // Procesando una palabra (comando o argumento)
	ARGUMENT,     // Procesando un argumento
	COMMENT       // Ignorar contenido después de un #

}		e_state;

// state.c

int			ft_mtcheck_state(t_mt *mt, int state);
e_pstate	transition(e_pstate current, char c);

// helpers
e_pstate	handle_start(char c);
e_pstate	handle_word(char c);
e_pstate	handle_redirection(char c);
e_pstate	handle_quote(char c);
e_pstate	handle_operator(char c);
e_pstate	handle_parentesis(char c);
e_state	handle_start(char c);
e_state	handle_word(char c);
e_state	handle_redirection(char c);
e_state	handle_single_quote(char c);
e_state	handle_double_quote(char c);
e_state	handle_operator(char c);
e_state	handle_parentesis(char c);
// tokenizer.c
t_mt		*ft_tokenize(const char *input, int *i);
// helpers_priority
void		set_node_priority(t_mt *node, void *param);
int			ft_get_priority(char *str);
t_mt		*ft_newnode(char *data, e_pstate state);

// extend

int			ft_extend_until_close(char **input);

// validate

int			ft_validate_list(t_mt *list);
int			ft_validate_input(char *s);
void	set_node_priority(t_mt *node, void *param);
int		get_priority(char *str);
t_mt	*create_node(char *data, e_state state);
void	ft_token_add_left(t_mt **list, t_mt *new);
void	ft_token_add_right(t_mt **list, t_mt *new);

// helpers_parse.c
int			ft_check_operators_mt(t_mt *op, int *error);
int			ft_check_redirections_mt(t_mt *op, int *error);
int			ft_check_is_close(char *input, char open, char close);
int			ft_check_is_close_quote(char *input, char quote);
char		*ft_strjoin_free(char **s1, char **s2);
// helpers_process_1.c

void	process_sublist(char *input, int *i, t_mt **sublist);
t_mt	*create_parentheses_node(t_mt *sublist);
int		process_argument(char *input, int *i, t_mt **list);

// helpers_is_1.c
int		is_double_quoted(char c);
int		is_single_quoted(char c);
int		is_operator(char c);
int		is_redirection(char c);
int		has_higher_precedence(char *op1, char *op2);

// helpers_is_2.c
int		is_whitespace(char c);
int		is_asignation(char c);
int		is_parentesis(char c);

// helpers_extract.c
char		*ft_extract_quoted_token(char *str, int *i);
char		*ft_extract_operator_token(char *str, int *i);
char		*ft_extract_word_token(char *str, int *i);

// ft_process_token.c
int			ft_process_token(char *input, int *i, t_mt **list, e_pstate state);

// ft_process.c
int			ft_process_word(char *input, int *i, t_mt **list, e_pstate state);
int			ft_process_operator(char *input, int *i, t_mt **list);
int			ft_process_parentheses(char *input, int *i, t_mt **list);
int			ft_process_redirection(char *input, int *i, t_mt **list);
int			ft_process_quote(char *input, int *i, t_mt **list, e_pstate state);

#endif // INPUT_H