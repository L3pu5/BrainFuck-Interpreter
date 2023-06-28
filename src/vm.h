//
//   vm.
//       By L3pu5, L3pu5_Hare
//
#include "lexer.h"

#ifndef BF_VM
#define BF_VM


#define STACK_MEMORY_SIZE 30000

typedef struct {
    short* memory;
    short* dataPointer;
    Token* code;
    Token* instructionPointer;
} VirtualMachine;

void initVM();
void freeVM();
void dumpMemory();
void execute(InstructionSequence* sequence);

#endif