//
// Created by saltfish on 2022/10/2.
//

#include "Myall.h"
//字符串复制
char * str_copy(char *str,char *arr){
    str = (char *)malloc(strlen(arr)+1);
    memset(str,0,strlen(arr)+1);
    for(int i = 0;i < strlen(arr);i++){
        str[i] = arr[i];
    }
    str += '\0';
    return str;
}

char * str_merge(char *str,char * merstr){
    merstr+='\0';
    char * res = (char *)malloc(strlen(str)+strlen(merstr)+1);
    memset(res,0,strlen(str)+strlen(merstr)+1);
    for(int i = 0;i < strlen(str);i++){
        res[i] = str[i];
    }

    for(int i = 0;i < strlen(merstr);i++){
        int j = i;
        char s =  merstr[i];
        res[i+strlen(str)] = s;
    }
    char *p = str;
    if(strlen(str)!=0){
        free(p);
    }
    return res;
}