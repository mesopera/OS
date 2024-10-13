#include "FileOperations.c" // Include file operations

int SI = 0; // Interupt counter
int TI = 0;
int PI = 0;

// Function to read data from input file
void Read(char* instruction){

    int address = String_to_address(instruction);
    Data_To_Buffer(address);

 }

// Function to write data to output file
 void Write(char* instruction){
    int vitualAddress = String_to_address(instruction);
    int block_address = calRealAddress(vitualAddress);
    Buffer_To_OutputFile(block_address);
 }

int Halt(){
    print_nextLine();
    job_no++;
    current_line_Counter = current_line_Counter + dataLineNo;
    dataLineNo = 1;
    return check_next_job();
}
// Function to handle errors
void terminate(int error){
    if(error == 0){
        printf("\nProgram executed successfully with code :%d\n", error);
    }
    else if(error == 1){
        printf("\nOut of data");
        printf("\nProgram terminated with code :%d\n", error);
    }
    else if(error == 2){
        printf("\nLine Limit Exceeded");
        printf("\nProgram terminated with code :%d\n", error);
    }
    else if(error == 3){
        printf("\nTime limit Exceeded");
        printf("\nProgram terminated with code :%d\n", error);
    }
    else if(error == 4){
        printf("\nOperation Code Error");
        printf("\nProgram terminated with code :%d\n", error);
    }
    else if(error == 5){
        printf("\nOperand Error");
        printf("\nProgram terminated with code :%d\n", error);
    }
    else if(error == 6){
        printf("\nInvalid Page Fault");
        printf("\nProgram terminated with code :%d\n", error);
    }
    //Halt();
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
                    Read(instruction);
                    break;
                }
                case 2:
                {
                    Write(instruction);
                    break;
                }
                case 3:
                    terminate(0);
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
                    terminate(4);
                    break;
                }
                case 2:
                {
                    terminate(4);
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
                    break;
                }
                case 2:
                {
                    Write(instruction);
                    terminate(3);
                    break;
                }
                case 3:
                    terminate(0);
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
                    break;
                }
                case 2:
                {
                    terminate(3);
                    terminate(5);
                    break;
                }
                case 3:
                {
                    terminate(3);
                    break;
                }
            }
            break;
        } 
    }
}