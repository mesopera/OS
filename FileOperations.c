#include "memory.c" // include memory for memory related operation

int dataLineNo = 1; // Count for number of data lines readed before
static int current_line_Counter = 1; // Keeps count of current line in the code
static int job_no = 1; // Keeps count of current job
int PCB[3]; // Stores the info of current job

// Function to extract current job no.
int jobNo(char* buffer){
    char job[5];
    job[0] = buffer[4];
    job[1] = buffer[5];
    job[2] = buffer[6];
    job[3] = buffer[7];
    job[4] = '\0';
    return atoi(job);
}

// Function to extract units of time required
int no_of_cpuCycles(char* buffer){
    char job[5];
    job[0] = buffer[8];
    job[1] = buffer[9];
    job[2] = buffer[10];
    job[3] = buffer[11];
    job[4] = '\0';
    return atoi(job);
}

// Function to extract number of lines
int no_of_linesToPrint(char* buffer){
    char job[5];
    job[0] = buffer[12];
    job[1] = buffer[13];
    job[2] = buffer[14];
    job[3] = buffer[15];
    job[4] = '\0';
    return atoi(job);
}

// Function call to extract job info
void extract_jobinfo(char* buffer){
    PCB[0] = jobNo(buffer);
    PCB[1] = no_of_cpuCycles(buffer);
    PCB[2] = no_of_linesToPrint(buffer);
}

// Function to Load Instructions to main memory
void Instructions_To_buffer(){

    FILE *file = fopen("input.txt", "r");

    int Linecounter = 1;

    while(Linecounter < current_line_Counter){ // Finds the line where the current job begins
        fgets(buffer,sizeof(buffer),file);
        flush_Buffer();
        Linecounter++;
    }

    while(EOF){                              // Gets the line that starts with $AMJ
        flush_Buffer();
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$AMJ",4)==0){
            extract_jobinfo(buffer);
            if(PCB[0]==job_no){
                current_line_Counter++;
                break;
            }
           
        }

    }

   while(1){                                // Reads the instruction from the next line
        flush_Buffer();
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$DATA",5)==0)
        break;
        Instructions_To_Memory(buffer);
        current_line_Counter++;
    }

    fclose(file);
}

// Function to load data to main memory
void Data_To_Buffer(int memory_address){

    FILE *file = fopen("input.txt", "r");
    int i = 1;
    int Linecounter = 1; 
   
        while(Linecounter < current_line_Counter){   // Finds the data line of current job
            fgets(buffer,sizeof(buffer),file);
            flush_Buffer();
            Linecounter++;
       
         }

    while(EOF){                             // Gets the line that starts with $DATA
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$DATA",5)==0 && PCB[0] == job_no){
            break;  
        }
       
    }

    while(1){    // Reads 40 bytes of data at a time 
       flush_Buffer();
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
    dataLineNo++;                   // Data line counter increments
    fclose(file);
  
}

// Function to write data into output file
void Buffer_To_OutputFile(int block_address){

    FILE *file = fopen("output.txt", "a");
    memory_to_buffer(buffer,block_address);                         // Loads the data from memory to buffer

    for(int i = 0 ;i<40; i++){                      

        if(buffer[i]=='-'){                                          // Printing the data in output file
            fputc(' ',file);
            continue;
        }

        fputc(buffer[i],file);
    }
    fputc('\n',file);
    fclose(file);

}


// Function to check if the next block exists
int check_next_job(){

    
    FILE *file = fopen("input.txt", "r");
    flush_Buffer();
    int Linecounter = 1;

     while(Linecounter < current_line_Counter){   // Finds the data line of current job
        fgets(buffer,sizeof(buffer),file);
        flush_Buffer();
        Linecounter++;
       
     }
     
    while(fgets(buffer,sizeof(buffer),file)){
        if(strncmp(buffer,"$AMJ",4)==0){
            extract_jobinfo(buffer);
            if(PCB[0]==job_no){
                fclose(file);
                // current_line_Counter = Linecounter - 1;
                return 1;
                break;
            }
           
        }
        flush_Buffer();
    }

    fclose(file);
    return 0;
}

// Function to print 2 next line characters after the job is done
void print_nextLine(){
    FILE* file;
    file = fopen("output.txt","a");
    fputc('\n',file);
    fputc('\n',file);
    fclose(file);
}