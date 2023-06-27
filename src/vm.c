//
//   vm.
//       By L3pu5, L3pu5_Hare
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

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
        vm.dataPointer = vm.memory + STACK_MEMORY_SIZE;
    }
}

void dumpMemory() {
    for(short i = 0; i < STACK_MEMORY_SIZE; i++){
        printf("%d | %u\n", i, vm.memory[i]);
    }
}