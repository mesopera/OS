#include "mos.c" // Include MOS for master mode 

char general_register[4]; // General purpose register
char instruction_register[4]; // Instruction register 
int program_counter; // Program Counter
bool toggle; // Toggle for true/false

// Initialise Cpu
void cpu_init(){

   SI = 0;
   TI = 0;
   PI = 0;
   H = 0;
   program_counter = 0;
   TTC = 0;
   LLC = 0;
   toggle = false;
   memset(instruction_register,'-',4);
   memset(general_register,'-',4);

}

//Function to load instruction from memory to instruction register
void load_instruction(){

    for(int i=0;i<4;i++){

        int RealAddress = calRealAddress(program_counter) + program_counter%10;
        instruction_register[i] = memory[RealAddress][i];

    }
    program_counter++;
}

// Function to load data in general purpose register
void load_register(int virtual_address){

    char* data;
    int realAddress = calRealAddress(virtual_address) + virtual_address%10;
    data = get_data(realAddress);

    for(int i=0;i<4;i++){
        general_register[i] = data[i];
    }
    free(data);
}

// Compare the data in regiter with data in memory at given location
bool compare_register(int virtual_address, char* general_register){

    int realAddress = calRealAddress(virtual_address) + virtual_address%10;
    char* data = get_data(realAddress);
    for(int i = 0; i < 4 ; i++){
        if(data[i] != general_register[i]){
            return false;
            break;
        }
    }
    return true;
}

// Function to store data from general purpose register to memory
void store_register(int virtual_address){

    if(!checkPTREntry(virtual_address)){                     // Valid page fault (Allocates space and create page table entry)
            int blockAddress = randomAddressGenerator();
            int ptrAddress = PTR*10 + virtual_address/10;
            char address[4];
            itoa(blockAddress,address,10);
            memory[ptrAddress][2] = address[0];
            if(address[1]!='\0')
            memory[ptrAddress][3] = address[1];
            store_data(virtual_address,general_register);
        }
        else
        store_data(virtual_address, general_register);
}

// Funtion to decode the instruction in instruction register
void decode_instruction(){

    //Handling the intrupt
    if (strncmp(instruction_register,"GD",2)==0){
        SI=1;
        TTC+=2;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else
        MOS(instruction_register);
    }
    else if (strncmp(instruction_register,"PD",2)==0){
        SI=2;
        TTC++;
        LLC++;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else
        MOS(instruction_register);
    }
    else if (strncmp(instruction_register,"H",1)==0){
        SI=3;
        TTC++;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else
        MOS(instruction_register);
    }
    else if(strncmp(instruction_register,"LR",2)==0){
        TTC++;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else{
            int virtual_address = String_to_address(instruction_register);
            if(isValidAddress(virtual_address)){                            // Checks for valid syntax
                if(checkPageFault(virtual_address)){                        // Checks for Page fault
                    load_register(virtual_address);
                }
                else{
                    PI = 3;
                    SI = 0;
                    MOS(instruction_register);
                }
            }
            else{                                                            // Operand Error
                PI = 2;
                SI = 0;
                MOS(instruction_register);
            }
        }
        
    }
    else if(strncmp(instruction_register,"SR",2)==0){
        TTC+=2;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else{
            int virtual_address = String_to_address(instruction_register);
            if(isValidAddress(virtual_address)){
                store_register(virtual_address);
            }
            else{                                                               // Operand Error
                PI = 2;
                SI = 0;
                MOS(instruction_register);
            }
        }
    }
    else if(strncmp(instruction_register,"CR",2)==0){
        TTC++;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else{
            int virtual_address = String_to_address(instruction_register);
            if(isValidAddress(virtual_address)){
                if(checkPageFault(virtual_address)){
                    toggle = compare_register(virtual_address, general_register);
                }
                else{
                    PI = 3;
                    SI = 0;
                    MOS(instruction_register);
                }
            }
            else{                                                                     // Operand Error
                PI = 2;
                SI = 0;
                MOS(instruction_register);
            }
        }
    }
    else if(strncmp(instruction_register,"BT",2)==0){
        TTC++;
        if(TTC>PCB[1]){
            TI = 2;
            MOS(instruction_register);
        }
        else{
            int virtual_address = String_to_address(instruction_register);
            if(isValidAddress(virtual_address)){
                if(checkPageFault(virtual_address)){
                    if(toggle){
                        program_counter = virtual_address - 1;
                    }
                }
                else{
                    PI = 3;
                    SI = 0;
                    MOS(instruction_register);
                }
            }
            else{                                                               // Operand Error
                PI = 2;
                SI = 0;
                MOS(instruction_register);
            }
        }
    }
    else {                                                                     // Opcode Error
        PI = 1;
        SI = 0;
        MOS(instruction_register);
    }
}

// Cpu starts working here
void cpu(){

    memory_init(); // Initialise memory
    PTR = create_PageTable(); // Creates Page Table 
    Instructions_To_buffer(); // Load instructions in main memory
    cpu_init(); // Initialise Cpu

    // Load decode instruction until Halt
    while(SI!=3 && H != 1){
        load_instruction();
        decode_instruction();
    }
    
    // If next job exists again call cpu
    if(nextJob){
      cpu();
    }

}

