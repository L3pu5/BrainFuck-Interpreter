//
//   main.
//       By L3pu5, L3pu5_Hare
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
        //Create a lexer
        initLexer(inputBuffer);
        parse();
    }
}

int main( int argc, char* argv[]) {

    //If no arg, enter interpreter mode.
    if(argc == 1){
        repl();
    }

    return 0;
}