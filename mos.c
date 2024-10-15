#include "FileOperations.c" // Include file operations

// Interupts
int SI = 0;
int TI = 0; 
int PI = 0;
// Counters
int TTC = 0;
int LLC = 0;

int nextJob = 0; // Check for next job

int H = 0;       // Condition for halt

// Halt function for a job
int Halt(){
    print_nextLine();
    job_no++;
    dataLineNo = 1;
    return check_next_job();
}

// Function to read data from input file
int Read(char* instruction){

    int address = String_to_address(instruction);
    if(isValidAddress(address)){                        // Checks for valid address
        
        if(address/10<blockCounter)
        PI = 2;
        else
        return Data_To_Buffer(address);
    }
    else{
        PI = 2;
        return 1;
    }
}

// Function to write data to output file
 void Write(char* instruction){

    int vitualAddress = String_to_address(instruction);
    if(isValidAddress(vitualAddress)){                              // Checks for valid address
        if(checkPageFault(vitualAddress)){                          // Checks for page fault
            int block_address = calRealAddress(vitualAddress);
            Buffer_To_OutputFile(block_address);
        }
        else{
            PI = 3;
        }
    }
    else{
        PI = 2;                                                      // Operand Error
    }
    
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
                    terminate(6);
                    H = 1;
                    nextJob = Halt();
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