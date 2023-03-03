//
// Created by saltfish on 2022/10/8.
//

#include "../my_bases.h"

u8 grammer_check(char* mes){
int mes_klen = spilt_size(mes," ");

char** arrs = split(mes," ");
    if (strcmp(arrs[0],"use")==0){
        return USE_DATABASE;
    }

    if (strcmp(mes,"show databases\n") == 0){
        return SHOW_DATABASE;
    }
    if (strcmp(mes,"show tables\n") == 0){
        return SHOW_TABLE;
    }
    if (strcmp(arrs[0],"create")==0){
        return CREATE_HANDLE;
    }
    if (strcmp(arrs[0],"select")==0){
        return SELECT_HANDLE;
    }
    if (strcmp(arrs[0],"insert")==0){
        return INSERT_HANDLE;
    }
    return 0;

}









