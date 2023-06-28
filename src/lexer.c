//
//   lexer.
//       By L3pu5, L3pu5_Hare
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lexer.h"


//Tokens
Token constructToken(TokenType tokentype, char* text, unsigned int length, unsigned int line, unsigned int col, unsigned int count){
    Token token = {tokentype, text, length, line, col, count, -1};
    return token;
}


// Instruction Sequence
void initSequence(InstructionSequence* sequence){
    //Alloc min array;
    sequence->tokens = calloc(DEFAULT_TOKEN_CAPACITY, sizeof(Token));
    //Set points to 0;
    sequence->tokenCapacity = DEFAULT_TOKEN_CAPACITY;
    sequence->tokenCount    = 0;
}

void freeSequence(InstructionSequence* sequence){
    free(sequence->tokens);
}

void dumpTokens(InstructionSequence* sequence){
    printf("[--Dumping Instruction Sequence--]\n");
    for(int i = 0; i <= sequence->tokenCount; i++){
        if(sequence->tokens[i].jumpAddress != -1){
            printf("%i | %u at [line: %u, col:%u, cnt:%u] [%p]->[%hu]\n", sequence->tokens[i].count, sequence->tokens[i].tokenType, sequence->tokens[i].line, sequence->tokens[i].col, sequence->tokens[i].count, &sequence->tokens[i], sequence->tokens[i].jumpAddress);
        }
        else{
            printf("%i | %u at [line: %u, col:%u, cnt:%u] [%p]\n", sequence->tokens[i].count, sequence->tokens[i].tokenType, sequence->tokens[i].line, sequence->tokens[i].col, sequence->tokens[i].count,  &sequence->tokens[i]);
        }
    }
}

void pushToken(InstructionSequence* sequence, Token token){
    if(sequence->tokenCount >= (0.5 * sequence->tokenCapacity)){
        //Double the capacity;
        sequence->tokenCapacity *= 2;
        //Grow the sequence;
        sequence->tokens = realloc(sequence->tokens, sizeof(Token)*sequence->tokenCapacity);
    }
    sequence->tokens[sequence->tokenCount] = token;
    sequence->tokenCount++;
}

// Global Lexer
Lexer lexer;

//Backtrack any ']' from the last '[' location forward.
int backTrackRightBrace(InstructionSequence* sequence){
    //Read backward until you find the first '[' to match.
    int backwardPtr = sequence->tokens[sequence->tokenCount-1].count;
    while( sequence->tokens[backwardPtr].tokenType != LEFT_BRACKET){
        backwardPtr--;
        if(backwardPtr < 0){
            printf("Illegal ']' not matching a '[' at (line: %u, col: %u).\n", lexer.line, lexer.col);
            dumpTokens(sequence);
            exit(69);
        }
    }
    return backwardPtr;
}

void initLexer(char* source) {    
    lexer.code                          = source;
    lexer.pointer                       = lexer.code;
    lexer.line                          = 0;
    lexer.col                           = 0;
    lexer.index                         = 0;
    lexer.sourcelength                  = strlen(source);
}

InstructionSequence parse() {
    assert(lexer.code);
    //Create instruction sequence
    InstructionSequence sequence;
    initSequence(&sequence);
    while(lexer.pointer < lexer.code + lexer.sourcelength){
        //printf("%c", *lexer.pointer);
        switch(*lexer.pointer){
            case '+':
                pushToken(&sequence, constructToken(PLUS, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case '-':
                pushToken(&sequence, constructToken(MINUS, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
             case '[':
                pushToken(&sequence, constructToken(LEFT_BRACKET, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case ']':
                int matchingLeftBracket = backTrackRightBrace(&sequence);
                pushToken(&sequence, constructToken(RIGHT_BRACKET, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                sequence.tokens[sequence.tokenCount-1].jumpAddress = matchingLeftBracket;
                sequence.tokens[matchingLeftBracket].jumpAddress = sequence.tokens[sequence.tokenCount-1].count;
                break;
            case '.':
                pushToken(&sequence, constructToken(DOT, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case ',':
                pushToken(&sequence, constructToken(COMMA, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case '>':
                pushToken(&sequence, constructToken(RIGHT_ARROW, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case '<':
                pushToken(&sequence, constructToken(LEFT_ARROW, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                break;
            case '\n':
                lexer.line++;
                lexer.col = -1;
                break;
            case '\0':
                dumpTokens(&sequence);
                pushToken(&sequence, constructToken(TOKEN_EOF, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
                return sequence;
            default:
                break;
        }
        lexer.index++;
        lexer.col++;
        lexer.pointer++;
    }
    pushToken(&sequence, constructToken(TOKEN_EOF, lexer.pointer, 1, lexer.line, lexer.col, sequence.tokenCount));
    return sequence;
}