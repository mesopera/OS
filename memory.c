#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

static int blockCounter = 0; // Keeps the count of current block
char memory[100][4]; // Main memory
char buffer[40]; // Buffer memory


// Function to load the contents of buffer to main memory
void buffer_To_Memory(char *buffer) {
    int k = 0;
    for(int i = blockCounter * 10; i < (blockCounter * 10) + 10; i++) {
        for(int j = 0; j < 4; j++) {
            if(buffer[k]=='\n')
            continue;
            memory[i][j] = buffer[k];
            k++;    
        }
    }
    blockCounter++;
}

// Function to load data to main memory
void data_To_Memory(char *buffer,int memory_address) {

    if(memory_address > blockCounter){
        int k = 0;
        for(int i = memory_address; i < memory_address + 10; i++) {
          for(int j = 0; j < 4; j++) {
            if(buffer[k]=='\n')
            continue;
            memory[i][j] = buffer[k];
            k++;
        }
    }
   }
   else{
    int k = 0;
    for(int i = blockCounter * 10; i < (blockCounter * 10) + 10; i++) {
        for(int j = 0; j < 4; j++) {
            if(buffer[k]=='\n')
            continue;
            memory[i][j] = buffer[k];
            k++;
        }
    }
         blockCounter++;
   }
    
    
}

// Function to load the contents main memory to buffer
void memory_to_buffer(char *buffer, int block) {
    int k = 0;
    for(int i = block; i < block + 10; i++) {
        for(int j = 0; j < 4; j++) {
            buffer[k] = memory[i][j];
            k++;
        }
    }
    blockCounter++;
}

//Function to check memory
void checkMemory() {
    for(int i = 0; i < 100; i++)  {
        printf("%c | %c | %c | %c \n", memory[i][0], memory[i][1], memory[i][2], memory[i][3]);
    }
}

// To check Buffer
void checkBuffer(){

    for(int i = 0 ; i < 40 ; i++){
        printf("%c", buffer[i]);
    }
}

// To initialise memory
void init() {

    memset(memory,'-',400);

}

// Flush buffer 
void flush_Buffer(){
    memset(buffer,'#',40);
}


