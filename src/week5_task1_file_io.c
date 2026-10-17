// week5_task1_file_io.c
// Name: Farid Surname: Allahverdiyev  Student ID: 251ADB084
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// TODO: Fill in the missing parts marked below.
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>

int main(int argc, char *argv[])
{
const char *filename = (argc > 1) ? argv[1] : "data.txt";
FILE *fp;
char line[256];
int lines = 0;

printf("Writing lines to %s...\n", filename);

fp = fopen(filename, "w");
if (fp == NULL) {
    perror("Error opening file for writing");
    return 1;
}

fprintf(fp, "Hello, file I/O in C!\n");
fprintf(fp, "This is another line.\n");

if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
}

printf("Reading contents:\n");

fp = fopen(filename, "r");
if (fp == NULL) {
    perror("Error opening file for reading");
    return 1;
}

while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
    lines++;
}

if (ferror(fp)) {
    perror("Error reading file");
    fclose(fp);
    return 1;
}

if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
}

printf("Lines read: %d\n", lines);

return 0;

}