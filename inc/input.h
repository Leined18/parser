#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "mt.h"

typedef enum e_state
{
	START,       // Estado inicial
	WORD,        // Procesando una palabra (comando o argumento)
	REDIRECTION, // Procesando redirecciones: >, >>
	QUOTE,       // Procesando contenido entre comillas
	OPERATOR,    // Operadores como |, &&, ||
	ASSIGNMENT,  // Procesando una asignación (VAR=value)
	PARENTESIS,  // Procesando paréntesis
	ARGUMENT,    // Procesando un argumento
	END          // Estado final
}				e_state;

typedef struct t_automation
{
	e_state		current_state;
	char		current_char;
	e_state		(*transition)(e_state, char);
}				t_automation;

// state.c

e_state			transition(e_state current, char c);
e_state			handle_start(char c);
e_state			handle_word(char c);
e_state			handle_redirection(char c);
e_state			handle_quote(char c);
e_state			handle_operator(char c);
// parser.c

t_hash_table	*parser(char *input);
t_mt			*tokenize(const char *input, int *i);

/* Add a node to the binary tree */
t_mt			*create_node(char *data, e_state state);

/* Parse a token and add it to the tree */
void			parse_token(char *input, int *i, t_mt **tree);
t_mt			*parse_input(const char *input);

/* Helpers */

int				has_higher_precedence(char *op1, char *op2);
int				is_whitespace(char c);
int				is_quoted(char c);
int				is_operator(char c);
int				is_redirection(char c);
int				is_asignation(char c);
int				is_parentesis(char c);

char			*extract_quoted_token(char *str, int *i);
char			*extract_operator_token(char *str, int *i);
char			*extract_word_token(char *str, int *i);

int				process_token(char *input, int *i, t_mt **tree, e_state state);
int				process_word(char *input, int *i, t_mt **tree, e_state state);
int				process_operator(char *input, int *i, t_mt **tree);
int				process_parentheses(char *input, int *i, t_mt **tree);
int				process_redirection(char *input, int *i, t_mt **tree);
int				process_quote(char *input, int *i, t_mt **tree);
int				process_argument(char *input, int *i, t_mt **tree);

#endif // INPUT_H