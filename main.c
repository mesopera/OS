#include "cpu.c" // Include Cpu

int main() {

    init(); // Initialise memory
    Instructions_To_buffer(); // Load instructions in main memory
    cpu(); // Start functioning of cpu
    
   return 0; 
}
