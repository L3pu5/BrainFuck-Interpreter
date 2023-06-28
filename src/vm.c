//
//   vm.
//       By L3pu5, L3pu5_Hare
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "lexer.h"

VirtualMachine vm;


void initVM() {
    vm.memory = calloc(STACK_MEMORY_SIZE, sizeof(short));
    vm.dataPointer = vm.memory;
}

void freeVM(){
    free(vm.memory);
}

void increment() {
    *vm.dataPointer += 1;
}

void decrement() {
    *vm.dataPointer -= 1;
}

void advance() {
    vm.dataPointer++;
    if(vm.dataPointer == vm.memory + STACK_MEMORY_SIZE){
        vm.dataPointer = vm.memory;
    }
}

void retreat() {
    vm.dataPointer--;
    if(vm.dataPointer < vm.memory){
        vm.dataPointer = vm.memory + STACK_MEMORY_SIZE - 1;
    }
}

void dumpCell() {
    printf("%c", *vm.dataPointer);
}

void inputCell() {
    printf("Expecting input at (line: %u, col: %u)\n>", vm.instructionPointer->line, vm.instructionPointer->col);
    char buffer[3];
    fgets(buffer, 3, stdin);
    sscanf(buffer, "%hu", vm.dataPointer);
}

void dumpMemory() {
    for(short i = 0; i < STACK_MEMORY_SIZE; i++){
        printf("%d | %u\n", i, vm.memory[i]);
    }
}

void leftBrace(){
    //If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
    if(*vm.dataPointer == 0){
        vm.instructionPointer = vm.code + vm.instructionPointer->jumpAddress;
        vm.instructionPointer++;
    } else {
        vm.instructionPointer++;
    }
}

void rightBrace(){
    //If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.[a]
    if(*vm.dataPointer != 0){
        vm.instructionPointer =  vm.code + vm.instructionPointer->jumpAddress;
        vm.instructionPointer++;
    } else {
        vm.instructionPointer++;
    }
}

void execute(InstructionSequence* sequence) {
    //Point to the first instruction
    vm.instructionPointer = sequence->tokens;
    vm.code = sequence->tokens;
    while( (*vm.instructionPointer).tokenType != TOKEN_EOF) {
        //printf("Running instrction %u\n", vm.instructionPointer->col);
        switch(( *vm.instructionPointer).tokenType){
            case PLUS:
                increment();
                vm.instructionPointer++;
                break;
            case MINUS:
                decrement();
                vm.instructionPointer++;
                break;
            case LEFT_ARROW:
                retreat();
                vm.instructionPointer++;
                break;
            case RIGHT_ARROW:
                advance();
                vm.instructionPointer++;
                break;
            case DOT:
                dumpCell();
                vm.instructionPointer++;
                break;
            case COMMA:
                inputCell();
                vm.instructionPointer++;
                break;
            case LEFT_BRACKET:
                leftBrace();
                break;
            case RIGHT_BRACKET:
                rightBrace();
                break;
            default:
                break;
        }
    }
}