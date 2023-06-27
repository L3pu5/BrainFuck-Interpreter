# Brainfuck-Interpreter

This project shows a C program that interprets brainfuck or allows for the exeuction of brainfuck as a script.

## Usage
Call the binary from the command line to start a repl, or call a path to a script using the command line to execute a script file. All outputs are pushed to stdout.
```
    .\brainfuck [script] 
```

## Brainfuck
---

>Brainfuck is an esoteric programming language created in 1993.
>
>-- <cite>[Wikipedia](https://en.wikipedia.org/wiki/Brainfuck#:~:text=Brainfuck%20is%20an%20esoteric%20programming,pointer%20and%20an%20instruction%20pointer.)</cite>

Brainfuck as a language has eight instructions, a data pointer, an instruction pointer, and a designated 30,000 bytes of memory. All other inputs are treated as comments and discarded by the interpreter.

---
## Features:

### Memory/Virtual machine

A 30,000 byte array is used in the virtual machine along with two pointers.

### Instructions
|Character |	Meaning|
| ---   | --- |
|>|	Increment the data pointer by one (to point to the next cell to the right).|
|<|	Decrement the data pointer by one (to point to the next cell to the left).
|+|	Increment the byte at the data pointer by one.
|-|	Decrement the byte at the data pointer by one.
|.|	Output the byte at the data pointer.
|,|	Accept one byte of input, storing its value in the byte at the data pointer.
|[|	If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
|]|	If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
