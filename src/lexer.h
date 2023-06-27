//
//   lexer.
//       By L3pu5, L3pu5_Hare
//
#ifndef BF_LEXER
#define BF_LEXER

typedef enum {
    RIGHT_ARROW,
    LEFT_ARROW,
    PLUS,
    MINUS,
    DOT,
    COMMA,
    LEFT_BRACKET,
    RIGHT_BRACKET
} TokenType;

typedef struct {
    TokenType type;
    char* text;
    unsigned int line;
    unsigned int col;
} Token;

typedef struct {
    Token* tokens;
} InstructionSequence;

typedef struct {
    char* code;
    char* pointer;
    unsigned int line;
    unsigned int col;
    unsigned int index;
    unsigned int sourcelength;
    InstructionSequence sequence;
} Lexer;

void initLexer(char* source);
void parse();


#endif