#include "memory.c"


int main() {
    init();
    checkMemory();
    char buffer[40] = "hello niggas", buffboi[40];
    buffer_To_Memory(buffer);
    memory_to_buffer(buffboi, 0);
    checkMemory(); 
    printf("%s", buffboi);
    return 0;
}
