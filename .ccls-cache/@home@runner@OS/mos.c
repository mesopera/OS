#include "memory.c"
#include "cpu.c"

void mos()
{
    switch(SI)
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