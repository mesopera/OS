#include "FileOperations.c" // Include file operations

int SI=0; // Interupt counter

// Function to extract memory address from instruction
int String_to_address(char* instruction){

    char s[2];
    s[0] = instruction[2];
    s[1] = instruction[3];

    return atoi(s);
}

// Function to read data from input file
void Read(char* instruction){

    int address = String_to_address(instruction);
    Data_To_Buffer(address);

 }

// Function to write data to output file
 void Write(char* instruction){
    int address = String_to_address(instruction);
    Buffer_To_OutputFile(address);
 }

int Halt(){
    print_nextLine();
    job_no++;
    sameJob = true;
    dataLineNo = 1;
    return check_next_job();
}

// Switching to master mode
void MOS(char* instruction){
    switch(SI)
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
       
    }
}