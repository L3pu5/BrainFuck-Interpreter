//
//   lexer.
//       By L3pu5, L3pu5_Hare
//
#ifndef lexer
#define lexer

typedef struct {
    char* code;
    char* pointer;
} Lexer;

typedef struct {

} InstructionSequence;

typedef enum {

} TokenType;

void initLexer(char* source);


#endif