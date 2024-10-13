#include "FileOperations.c" // Include file operations

int SI = 0; // Interupt counter
int TI = 0;
int PI = 0;
int TTC = 0;
int LLC = 0;
int nextJob = 0;
int H = 0;

void MOS(char* instruction);

// Function to read data from input file
int Read(char* instruction){

    int address = String_to_address(instruction);

    printf("%d\n",address);
    if(isValidAddress(address)){

        return Data_To_Buffer(address);
    }
    else{
        PI = 2;
        MOS(instruction);
    }
}

// Function to write data to output file
 void Write(char* instruction){

    int vitualAddress = String_to_address(instruction);
    if(isValidAddress(vitualAddress)){
        int block_address = calRealAddress(vitualAddress);
        Buffer_To_OutputFile(block_address);
    }
    else{
        PI = 2;
        MOS(instruction);
    }
    
 }

// Function to handle errors
void terminate(int error){

    FILE* file = fopen("output.txt","a");
    if(error == 0){
        fprintf(file,"\nProgram executed successfully with exit code :%d\n", error);
    }
    else if(error == 1){
        fprintf(file,"Out of data");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }
    else if(error == 2){
        fprintf(file,"Line Limit Exceeded");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }
    else if(error == 3){
        fprintf(file,"Time limit Exceeded");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }
    else if(error == 4){
        fprintf(file,"Operation Code Error");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }
    else if(error == 5){
        fprintf(file,"Operand Error");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }
    else if(error == 6){
        fprintf(file,"Invalid Page Fault");
        fprintf(file,"\nProgram terminated with exit code :%d\n", error);
    }

    fclose(file);
}

int Halt(){
    print_nextLine();
    job_no++;
    dataLineNo = 1;
    return check_next_job();
}

// Switching to master mode
void MOS(char* instruction){

    switch(TI)
    {
        case 0:
        {   
            switch (SI)
            {
                case 1: 
                {
                    int temp = Read(instruction);
                    if(!temp){
                        terminate(1);
                        H = 1;
                        nextJob = Halt();
                        break;
                    }
                    break;
                }
                case 2:
                {
                    if( LLC > PCB[2]){
                        terminate(2);
                        nextJob = Halt();
                        H = 1;
                        break;
                    }
                    Write(instruction);
                    break;
                }
                case 3:
                {   
                    terminate(0);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
            }
            switch (PI)
            {
                case 0:
                {
                    break;
                } 
                case 1:
                {
                    terminate(4);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 2:
                {
                    terminate(5);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 3:
                {
                    //if valid page fault, allocate else terminate(6)
                    break;
                }
            }
            break;
        }
        case 2:
        {
            switch (SI)
            {
                case 1: 
                {
                    terminate(3);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 2:
                {   
                    if(LLC > PCB[2]){
                        terminate(2);
                        H = 1;
                        nextJob = Halt();
                        break;
                    }
                    Write(instruction);
                    terminate(3);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 3:
                    terminate(0);
                    H = 1;
                    nextJob = Halt();
                    break;
            }
            switch (PI)
            {
                case 0:
                {   
                    break;
                } 
                case 1:
                {
                    terminate(3);
                    terminate(4);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 2:
                {
                    terminate(3);
                    terminate(5);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
                case 3:
                {
                    terminate(3);
                    H = 1;
                    nextJob = Halt();
                    break;
                }
            }
            break;
        } 
    }
}