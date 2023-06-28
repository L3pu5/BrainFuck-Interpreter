//
//   lexer.
//       By L3pu5, L3pu5_Hare
//
#ifndef BF_LEXER
#define BF_LEXER

#define DEFAULT_TOKEN_CAPACITY 32

typedef enum {
    RIGHT_ARROW,
    LEFT_ARROW,
    PLUS,
    MINUS,
    DOT,
    COMMA,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType tokenType;
    char* text;
    unsigned int length;
    unsigned int line;
    unsigned int col;
    unsigned int count;
    unsigned int jumpAddress;
} Token;

Token constructToken(TokenType tokentype, char* text, unsigned int length, unsigned int line, unsigned int col,  unsigned int count);

typedef struct {
    Token* tokens;
    unsigned int tokenCapacity;
    unsigned int tokenCount;
} InstructionSequence;

void initSequence(InstructionSequence* sequence);
void pushToken(InstructionSequence* sequence, Token token);
void dumpTokens(InstructionSequence* sequence);
void freeSequence(InstructionSequence* sequence);

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
InstructionSequence parse();


#endif