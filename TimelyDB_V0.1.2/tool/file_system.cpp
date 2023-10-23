//
// Created by saltfish on 23-10-22.
//

#include "tool_base.h"
#include "../config_init/config_h.h"
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

    char *base = str_copy(base,get_config_base_path());
    base = str_marge(base,"/");

    char *database_path = str_marge(base,database);
    database_path = str_marge(database_path,"/");

    char *table_path = str_marge(database_path,table);


    if (access(database_path,F_OK)){
        int isCreate = mkdir(database_path,S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if( !isCreate )
            printf("成功创建:%s\n",database_path);
        else
            printf("创建目录失败! error: %s , %d \n",database_path,isCreate);
    } else{
        printf("创建完成");
    }

    if (access(table_path,F_OK)){
        FILE *fd = fopen(table_path,"a");
        fclose(fd);
    } else{
        perror("表已存在");
        return false;
    }











//    FILE *file = fopen(path_key, "a+");





    return 1;






}










