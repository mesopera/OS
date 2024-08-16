#include "memory.c"
#include <string.h>

char generaRegister[4];
char instructionRegister[4];
int program_counter=0;
int toggle = 0;
int systemInterrupt;

void mos()
{
    switch(systemInterrupt)
    {
        case 1:
        {
            Read(int memory_address);
            break;
        }
        case 2:
        {
            Write(int memory_address);
            break;
        }
        case 3:
        {
            Halt();
            break;
        }
    }
}

void load_Instruction()
{
    for(int i=0;i<4;i++)
    {
        instructionRegister[i]=memory[program_counter][i];
    }
    program_counter++;
}

void decode_instruction()
{
    if (strncmp(instruction_register,"GD",2)==0)
    {
        SI=1;
        MOS();
    }
    if (strncmp(instruction_register,"PD",2)==0)
    {
        SI=2;
        MOS();
    }
    if (strncmp(instruction_register,"H",1)==0)
    {
        SI=3;
        MOS();
    }
    if (strncmp(instruction_register,"",2)==0)
    {
        SI=1;
        MOS();
    }
    if (strncmp(instruction_register,"PD",2)==0)
    {
        SI=2;
        MOS();
    }
    if (strncmp(instruction_register,"H",1)==0)
    {
        SI=3;
        MOS();
    }
}

// Calculates the nth number in the Fibonacci sequence
int fibonacci(int n) {

    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}