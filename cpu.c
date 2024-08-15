#include "mos.c" // Include MOS for master mode

char general_register[4]; // General purpose register
char instruction_register[4]; // Instruction register 
static int program_counter; // Program Counter
bool toggle; // Toggle for true/false

// Initialise Cpu
void cpu_init(){
   program_counter = 0;
   memset(instruction_register,'-',4);
   memset(general_register,'-',4);
   toggle = false;
}
//Function to load instruction from memory to instruction register
void load_instruction()
{
    for(int i=0;i<4;i++)
    {
        instruction_register[i]=memory[program_counter][i];
    }
    program_counter++;
}

// Funtion to decode the instruction in instruction register
void decode_instruction()
{   
    //Handling the intrupt
    if (strncmp(instruction_register,"GD",2)==0)
    {
        SI=1;
        MOS(instruction_register);
    }
    if (strncmp(instruction_register,"PD",2)==0)
    {
        SI=2;
        MOS(instruction_register);
    }
    if (strncmp(instruction_register,"H",1)==0)
    {
        SI=3;
       // MOS();
    }

}

// Cpu starts working here
void cpu(){

    while(SI!=3){
        load_instruction();
        decode_instruction();
    }
}
