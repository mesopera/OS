#include "mos.c" // Include MOS for master mode

char general_register[4]; // General purpose register
char instruction_register[4]; // Instruction register 
static int program_counter; // Program Counter
bool toggle; // Toggle for true/false

// Initialise Cpu
void cpu_init(){
   SI = 0;
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

// Function to load data in general purpose register
void load_register(int block_address){

    char* data = (char*)malloc(4); 
    data = get_data(block_address);

    for(int i=0;i<4;i++){
        general_register[i] = data[i];
    }
    free(data);
}

// Compare the data in regiter with data in memory at given location
bool compare_register(int block_address, char* general_register){

    char* data = get_data(block_address);
    for(int i = 0; i < 4 ; i++){
        if(data[i] != general_register[i]){
            return false;
            break;
        }
    }
    return true;
}

// Function to store data from general purpose register to memory
void store_register(int block_address){

    store_data(block_address, general_register);
}

// Funtion to decode the instruction in instruction register
void decode_instruction()
{   
    //Handling the intrupt
    if (strncmp(instruction_register,"GD",2)==0){
        SI=1;
        MOS(instruction_register);
    }
    if (strncmp(instruction_register,"PD",2)==0){
        SI=2;
        MOS(instruction_register);
    }
    if (strncmp(instruction_register,"H",1)==0){
        SI=3;
        MOS(instruction_register);
    }
    if(strncmp(instruction_register,"LR",2)==0){
        int block_address = String_to_address(instruction_register);
        load_register(block_address); 
    }
    if(strncmp(instruction_register,"SR",2)==0){
        int block_address = String_to_address(instruction_register);
        store_register(block_address);
    }
    if(strncmp(instruction_register,"CR",2)==0){
        int block_address = String_to_address(instruction_register);
        toggle = compare_register(block_address, general_register);
       
    }
    if(strncmp(instruction_register,"BT",2)==0){
        int block_address = String_to_address(instruction_register);
        if(toggle){
            program_counter = block_address - 1;
        }
    }

}

// Cpu starts working here
void cpu(){

    memory_init(); // Initialise memory
    Instructions_To_buffer(); // Load instructions in main memory
    cpu_init(); // Initialise Cpu

    // Load decode instruction untill Halt
    while(SI!=3){
        load_instruction();
        decode_instruction();
    }

    // If next job exist again call cpu
    if(Halt()){
      cpu();
    }
}

