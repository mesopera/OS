#include "memory.c" // include memory for memory related operation

int dataLineNo = 1; // Count for number of data lines readed before
static int current_line_Counter = 1; // Keeps count of current line in the code
static int job_no = 1; // Keeps count of current job
int current_job_info[3]; // Stores the info of current job
bool sameJob = true; // Flag to check the current job

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

// Function to extract unit of time required
int No_of_units(char* buffer){
    char job[5];
    job[0] = buffer[8];
    job[1] = buffer[9];
    job[2] = buffer[10];
    job[3] = buffer[11];
    job[4] = '\0';
    return atoi(job);
}

// Function to extract number of lines
int No_of_instruction_lines(char* buffer){
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
    current_job_info[0] = jobNo(buffer);
    current_job_info[1] = No_of_units(buffer);
    current_job_info[3] = No_of_instruction_lines(buffer);
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
            if(current_job_info[0]==job_no){
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
        buffer_To_Memory(buffer);
        current_line_Counter++;
    }

    fclose(file);
}

// Function to load data to main memory
void Data_To_Buffer(int memory_address){

    FILE *file = fopen("input.txt", "r");
    int i = 1;
    int Linecounter = 1; 
    if(sameJob){                     // Finds the data line of current job
        while(Linecounter < current_line_Counter){
            fgets(buffer,sizeof(buffer),file);
            flush_Buffer();
            Linecounter++;
       
         }
          sameJob = false;
    }

    while(EOF){                             // Gets the line that starts with $DATA
        fgets(buffer,sizeof(buffer),file);
        if(strncmp(buffer,"$DATA",5)==0 && current_job_info[0] == job_no){
            current_line_Counter++;
            break;  
        }
       
    }

    while(strncmp(buffer,"$END",4)!=0){    // Reads 40 bytes of data at a time 
       flush_Buffer();
       fgets(buffer,sizeof(buffer),file);
        if(i!=dataLineNo){
            i++;
            continue;
        }
        data_To_Memory(buffer,memory_address);
        break;
        
    }
    
     dataLineNo++;                       // Data line counter increments

    fclose(file);
  
}

// Function to write data into output file
void Buffer_To_OutputFile(int memory_address){

    FILE *file = fopen("result.txt", "a");
    int block_address = memory_address - memory_address % 10;       // Nearest 10 block of address
    
    memory_to_buffer(buffer,block_address);                         // Loads the data from memory to buffer

    for(int i = 0 ;; i++){ 
        if(buffer[i]==' ' && buffer[i+1] == ' ')
        break;                          // Printing the data in output file
        fputc(buffer[i],file);
    }
    fputc(' ',file);
    fclose(file);

}


// Function to check if the next block exists
int check_next_job(){

    FILE *file = fopen("input.txt", "r");
    flush_Buffer();
    int Linecounter = 1;
    while(Linecounter < current_line_Counter){
        fgets(buffer,sizeof(buffer),file);
        flush_Buffer();
        Linecounter++;
    }

    while(fgets(buffer,sizeof(buffer),file)){
        if(strncmp(buffer,"$AMJ",4)==0){
            extract_jobinfo(buffer);
            if(current_job_info[0]==job_no){
                fclose(file);
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
    file = fopen("result.txt","a");
    fputc('\n',file);
    fputc('\n',file);
    fclose(file);
}