#include<stdio.h>

static int blockCounter = 0;
char memory[100][4];

void buffer_To_Memory(char *buffer) {
    int k = 0;
    for(int i = blockCounter * 10; i < (blockCounter * 10) + 10; i++) {
        for(int j = 0; j < 4; j++) {
            memory[i][j] = buffer[k];
            k++;
        }
    }
    blockCounter++;
}

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

void checkMemory() {
    for(int i = 0; i < 100; i++)  {
        printf("%d   %c | %c | %c | %c \n", i, memory[i][0], memory[i][1], memory[i][2], memory[i][3]);
    }
}

void init() {
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 4; j++) {
            memory[i][j] = '$';
        }
    } 
}

void flush_memory()
{
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 4; j++) {
            memory[i][j] = '$';
        }
    }
}