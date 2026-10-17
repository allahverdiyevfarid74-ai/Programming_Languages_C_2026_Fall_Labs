// week5_task4_struct_binary_io.c   (BONUS)
// Name: Farid  Surname: Allahverdiyev  Student ID: 251ADB084
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>

typedef struct Student {
char name[50];
int age;
float gpa;
} Student;

int save_student_binary(const Student *s, const char *filename)
{
FILE *fp = fopen(filename, "wb");

if (fp == NULL) {
    return -1;
}

int result = (fwrite(s, sizeof(Student), 1, fp) == 1);

if (fclose(fp) != 0 || result == 0) {
    return -1;
}

return 0;

}

int load_student_binary(const char *filename, Student *out)
{
FILE *fp = fopen(filename, "rb");

if (fp == NULL) {
    return -1;
}

int result = (fread(out, sizeof(Student), 1, fp) == 1);

if (fclose(fp) != 0 || result == 0) {
    return -1;
}

return 0;

}

long file_size(const char *filename)
{
FILE *fp = fopen(filename, "rb");

if (fp == NULL) {
    return -1;
}

if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
}

long size = ftell(fp);

if (fclose(fp) != 0) {
    return -1;
}

return size;

}

int main(void)
{
Student s = {0};
Student loaded = {0};
FILE *fp;
int result;

snprintf(s.name, sizeof(s.name), "%s", "Alice");
s.age = 21;
s.gpa = 3.75f;

printf("Saving student in binary format...\n");

if (save_student_binary(&s, "student.bin") != 0) {
    fprintf(stderr, "Error saving binary file.\n");
    return 1;
}

/* Save the same record as text for comparison. */
fp = fopen("student.txt", "w");

if (fp == NULL) {
    perror("Error opening text file");
    return 1;
}

result = fprintf(fp, "%s %d %.2f\n",
                 s.name, s.age, s.gpa);

if (fclose(fp) != 0 || result < 0) {
    fprintf(stderr, "Error writing text file.\n");
    return 1;
}

printf("Loading student from binary file...\n");

if (load_student_binary("student.bin", &loaded) != 0) {
    fprintf(stderr, "Error loading binary file.\n");
    return 1;
}

printf("Loaded student: %s, %d, GPA %.2f\n",
       loaded.name, loaded.age, loaded.gpa);

long text_size = file_size("student.txt");
long binary_size = file_size("student.bin");

if (text_size < 0 || binary_size < 0) {
    fprintf(stderr, "Error checking file sizes.\n");
    return 1;
}

printf("Text file size: %ld bytes\n", text_size);
printf("Binary file size: %ld bytes\n", binary_size);

return 0;

}