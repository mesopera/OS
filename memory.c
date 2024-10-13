#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static int blockCounter = 0; // Keeps the count of current block
char memory[300][4]; // Main memory
char buffer[42]; // Buffer memory
int PTR; // Page Table Register
int BlockManager[30] = {0};

int randomAddressGenerator(){
    srand(time(0));
    int blockAddress = rand()%30;
    while(1){
        if(BlockManager[blockAddress] == 0 && blockAddress != PTR)
        break;
        blockAddress = rand()%30;
    }
    BlockManager[blockAddress] = 1;
    return blockAddress;
}

// Function to load the contents of buffer to main memory
void Instructions_To_Memory(char *buffer) {

    int blockAddress = randomAddressGenerator();
    int ptrAddress = PTR*10 + blockCounter;
    char address[4];
    itoa(blockAddress,address,10);
    memory[ptrAddress][2] = address[0];
    if(address[1]!='\0')
    memory[ptrAddress][3] = address[1];

    int k = 0;
    for(int i = blockAddress * 10; i < (blockAddress * 10) + 10; i++) {
        for(int j = 0; j < 4; j++) {
            if(buffer[k] == '\n'||buffer[k] == '\0'){
                memory[i][j] = ' ';
                k++;
                continue;
            }

            memory[i][j] = buffer[k];
            k++;    
        }
    }

    blockCounter++;
}

// Function to load data to main memory
void data_To_Memory(char *buffer,int virtual_address) {

    int blockAddress = randomAddressGenerator();
    int ptrAddress = PTR*10 + virtual_address/10;
    char address[4];
    itoa(blockAddress,address,10);
    memory[ptrAddress][2] = address[0];
    if(address[1]!='\0')
    memory[ptrAddress][3] = address[1];

    int k = 0;
    for(int i = blockAddress * 10; i < (blockAddress * 10) + 10; i++) {
        for(int j = 0; j < 4; j++) {
            if(buffer[k] == '\n'||buffer[k] == '\0'){
                memory[i][j] = ' ';
                k++;
                continue;
            }
            memory[i][j] = buffer[k];
            k++;
        }
    }

    blockCounter++;
}
    
// Function to load the contents main memory to buffer
void memory_to_buffer(char *buffer, int block) {
    int k = 0;
    block = block - block%10;
    for(int i = block; i < block + 10; i++) {
        for(int j = 0; j < 4; j++) {
            buffer[k] = memory[i][j];
            k++;
        }
    }
}


// Function to extract memory address from instruction
int String_to_address(char* instruction){

    char s[3];
    s[0] = instruction[2];
    if(instruction[3]!='#'){
        s[1] = instruction[3];
        s[2] = '\0';
    }
    else{
        s[1] = '\0';
    }
    return atoi(s);
}

bool checkPTREntry(int virtualAddress){
    int PTR_Entry = PTR*10 + virtualAddress/10;
    for(int i = 0; i < 4; i++){
        if(memory[PTR_Entry][i]!='#'){
            return true;
            break;
        }
    }

    return false;
}

int calRealAddress(int virtualAddress){
    int PTR_Entry = PTR*10 + virtualAddress/10;
    if(checkPTREntry(virtualAddress)){
        int RealAdress = String_to_address(memory[PTR_Entry]);
        return RealAdress*10;
    }
    else 
    return -1;
}

// Function to store data from memory to general purpose register
char* get_data(int realAddress){

    char* data = (char*)malloc(4);
    for(int i = 0; i < 4 ; i++){
        data[i] = memory[realAddress][i];
    }
    return data;
}

// Function to store data from general purpose register to memory
void store_data(int virtual_address, char* general_register){

    int realAddress = calRealAddress(virtual_address) + virtual_address%10;
    for(int i = 0; i < 4 ; i++){
        memory[realAddress][i] = general_register[i];
    }

}

//Function to check memory
void checkMemory() {
    for(int i = 0; i < 300; i++)  {
        printf("%c | %c | %c | %c \n", memory[i][0], memory[i][1], memory[i][2], memory[i][3]);
    }
}

// To check Buffer
void checkBuffer(){

    for(int i = 0 ; i < 42 ; i++){
        printf("%c", buffer[i]);
    }
}

// Flush buffer 
void flush_Buffer(){
    memset(buffer,' ',42);
}

// To initialise memory
void memory_init() {
    
    blockCounter = 0;
    memset(memory,'-',1200);
    flush_Buffer();
}

int create_PageTable(){

    srand(time(0));
    int ptr = rand()%30;

    for(int i = ptr*10; i < ptr*10 + 10; i++){
        memory[i][0] = '#';
        memory[i][1] = '#';
        memory[i][2] = '#';
        memory[i][3] = '#';
    }

    return ptr;
}
