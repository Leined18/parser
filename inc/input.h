#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "mt.h"

typedef enum e_state
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

e_state	transition(e_state current, char c);

// helpers
e_state	handle_start(char c);
e_state	handle_word(char c);
e_state	handle_redirection(char c);
e_state	handle_single_quote(char c);
e_state	handle_double_quote(char c);
e_state	handle_operator(char c);
e_state	handle_parentesis(char c);
// tokenizer.c
t_mt	*tokenize(const char *input, int *i);
// helpers_priority
void	set_node_priority(t_mt *node, void *param);
int		get_priority(char *str);
t_mt	*create_node(char *data, e_state state);

// helpers_parse.c
int		check_operators_mt(t_mt *op);
int		check_redirections_mt(t_mt *op);
int		check_is_close(char *input, char open, char close);
int		check_is_close_quote(char *input, char quote);
char	*ft_strjoin_free(char **s1, char **s2);
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
char	*extract_quoted_token(char *str, int *i);
char	*extract_operator_token(char *str, int *i);
char	*extract_word_token(char *str, int *i);

// process_token.c
int		process_token(char *input, int *i, t_mt **list, e_state state);

// process.c
int		process_word(char *input, int *i, t_mt **list, e_state state);
int		process_operator(char *input, int *i, t_mt **list);
int		process_parentheses(char *input, int *i, t_mt **list);
int		process_redirection(char *input, int *i, t_mt **list);
int		process_quote(char *input, int *i, t_mt **list, e_state state);

#endif // INPUT_H