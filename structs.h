#ifndef MY_STRUCT
#define MY_STRUCT

/**
 * struct my_token - categorizes a token
 * @id: id of token from MY_TOKEN_ macros
 * @str: token
 * @prec: the prec
 */
typedef struct my_token
{
    int id;
    char *str;
    int prec;
} my_token_t;

/**
 * struct my_tokens - struct for tokenizing string
 * @tokens: array of my_token_t structs with tokenized strings and ids
 * @tokensN: amount of tokens parsed
 *
 * NOTE: do not deallocate everything from here until the full parse tree
 * deallocation because AST will use tokens from this structure!
 */
typedef struct my_tokens
{
    my_token_t *tokens;
    unsigned int tokensN;
} my_tokens_t;

/**
 * struct my_token_id - baby token
 * @token_id: numerical id
 * @token_str: the exact token string to be compared with
 * @token_descr: for debugging
 * @precedence: the precedence
 */
typedef struct my_token_id
{
    int token_id;
    const char *token_str;
    const char *token_descr;
    int precedence;
} my_token_types;

/* ... (Rest of the struct definitions unchanged) */

#endif