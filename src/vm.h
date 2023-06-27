//
//   vm.
//       By L3pu5, L3pu5_Hare
//
#ifndef BF_VM
#define BF_VM

#define STACK_MEMORY_SIZE 5

typedef struct {
    short* memory;
    short* dataPointer;
    short* instructionPointer;
} VirtualMachine;

void initVM();
void freeVM();
void dumpMemory();

#endif