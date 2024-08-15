#include "memory.c" // include memory for memory related operation

int dataLineNo = 1; //Count for number of data lines readed before

// Function to Load Instructions to main memory
void Instructions_To_buffer(){

    FILE *file = fopen("input.txt", "r");

    while(EOF){                              // Gets the line that starts with $AMJ

        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$AMJ",4)==0)
        break;  

    }
   while(1){                                // Reads the instruction from the next line
        flush_Buffer();
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$DATA",5)==0)
        break;
        buffer_To_Memory(buffer);
    }

    fclose(file);
}

// Function to load data to main memory
void Data_To_Buffer(int memory_address){

    FILE *file = fopen("input.txt", "r");
    int i = 1;

    while(EOF){                             // Gets the line that starts with $DATA

        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$DATA",5)==0)
        break;  
    }

    while(strncmp(buffer,"$END",4)!=0){    // Reads 40 bytes of data at a time 
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$END",4)==0)
        break;
        if(i!=dataLineNo){
             i++;
            continue;
        }
        
        data_To_Memory(buffer,memory_address);
        break;
        
    }

    dataLineNo++;                           // Data line counter increments

    fclose(file);
  
}

// Function to write data into output file
void Buffer_To_OutputFile(int memory_address){

    FILE *file = fopen("result.txt", "a");
    int block_address = memory_address - memory_address % 10;       // Nearest 10 block of address
    
    memory_to_buffer(buffer,block_address);                         // Loads the data from memory to buffer

    for(int i = 0 ; buffer[i]!='-'; i++){                           // Printing the data in output file
        fputc(buffer[i],file);
    }
    fputc('\n',file);
    fputc('\n',file);

    fclose(file);

}