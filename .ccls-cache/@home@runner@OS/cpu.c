#include "memory.c"
#include <string.h>

char genera_register[4];
int program_counter=0;
char instruction_register[4];
// bool toggle;
// static int SI=0;

// void mos()
// {
//     switch(SI)
//     {
//         case 1:
//         {
//             Read(int memory_address);
//             break;
//         }
//         case 2:
//         {
//             Write(int memory_address);
//             break;
//         }
//         case 3:
//         {
//             Halt();
//             break;

//         }
//     }
// }

// void load_instruction()
// {
//     for(int i=0;i<4;i++)
//     {
//         instruction_register[i]=memory[program_counter][i];
//     }
//     program_counter++;
// }

// void decode_instruction()
// {
//     if (strncmp(instruction_register,"GD",2)==0)
//     {
//         SI=1;
//         MOS();
//     }
//     if (strncmp(instruction_register,"PD",2)==0)
//     {
//         SI=2;
//         MOS();
//     }
//     if (strncmp(instruction_register,"H",1)==0)
//     {
//         SI=3;
//         MOS();
//     }

// }
