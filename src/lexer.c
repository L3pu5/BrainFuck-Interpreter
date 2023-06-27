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

Lexer lexer;

void initLexer(char* source) {    
    lexer.code          = source;
    lexer.pointer       = lexer.code;
    lexer.line          = 0;
    lexer.col           = 0;
    lexer.index         = 0;
    lexer.sourcelength  = strlen(source);
}

void parse() {
    assert(lexer.code);
    //Create instruction sequence
    InstructionSequence sequeunce;
    while(lexer.pointer < lexer.code + lexer.sourcelength){
        printf("%c", *lexer.pointer);
        lexer.pointer++;
        switch(*lexer.pointer){
            case '+':
                
            default:
                break;
        }
    }
}