//
// Created by saltfish on 23-10-22.
//
#include "tool_base.h"

static map<char*,char*> path_map;
static map<char*,FILE *> file_map;

void file_test(){
    FILE * f_write = fopen("../test.txt", "a+");
    if (f_write == NULL)
    {
        return;
    }
    char buf[] = "this is first test";
    fputs(buf, f_write);
    fclose(f_write);

    //读文件
    FILE * f_read = fopen("../test.txt", "r");
    if (f_read == NULL)
    {
        return;
    }
    char ch;
    while ( (ch = fgetc(f_read)) != EOF  )  // EOF  Enf of File
    {
        printf("%c", ch);
    }
    fclose(f_read);

}




int push_file(char* database,char* table){
    FILE *file = fopen("", "a+");









}










