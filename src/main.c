//
//   Main Program for brainfuck interpreter..
//       By L3pu5, L3pu5_Hare
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "vm.h"
#include "lexer.h"
#include "helper.h"

void repl() {
    //Instantiate up VM
    initVM();

    printf("Entering brainfuck by L3pu5 repl loop.\n");
    bool keepReplAlive = true;
    while(keepReplAlive){ 
        char inputBuffer[1000]; 
        prompt();
        fgets(inputBuffer, 1000, stdin);
        if(strcmp(inputBuffer, "quit\n") == 0){
            exit(0);
        }
        //Create a lexer with the string buffer
        initLexer(inputBuffer);
        //Create the sequence of tokens
        InstructionSequence sequence = parse();
        //Execute the sequence in the VM
        execute(&sequence);
        freeSequence(&sequence);
    }
}

void runFile(const char* filePath) {
    //read file
    FILE* fileHandle = fopen(filePath, "r");
    fseek(fileHandle, 0, SEEK_END);
    int length = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);
    char* soureCode = malloc(sizeof(char) * (length + 1)); 
    fread(soureCode, sizeof(char), length, fileHandle);
    soureCode[length] = '\0';
    fclose(fileHandle);
    //Instantiate up VM
    initVM();
    initLexer(soureCode);
    InstructionSequence sequence = parse();
    execute(&sequence);  
    freeSequence(&sequence);
    free(soureCode);
}

int main( int argc, char* argv[]) {

    //If no arg, enter interpreter mode.
    if(argc == 1){
        repl();
    }
    
    if(argc == 2){
        runFile(argv[1]);
    }

    return 0;
}