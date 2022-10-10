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
    return res;
}



int spilt_size_gar(char *a,char *b){
    char *str = a;
    char *dent = b;
    int strlens = strlen(str);
    char  ch[strlens];
    strcpy(ch,str);
    char* str1 = strtok(ch, dent);
    int i = 0;
    while (str1 != NULL)
    {
        str1 = strtok(NULL, dent);
        if (str1!=NULL){
            i++;
        }
    }

    return i+1;
}

char **split_gar(char *str,char *dent){
    int size = spilt_size_gar(str,dent);
    int strlens = strlen(str);
    char  ch[strlens];
    strcpy(ch,str);
    char* str1 = strtok(ch, dent);
    char **res =  (char**) malloc(size * sizeof(char*));
    memset(res,0,sizeof(res));
    int i = 0;
    res[i] = str_copy(res[i],str1);
    while (str1 != NULL)
    {
        str1 = strtok(NULL, dent);
        if (str1!=NULL){
            i++;
            res[i] = str_copy(res[i],str1);
        }
    }
    return res;
}



int max_strarr(char** arr,int len){
    if (arr == NULL){
        return 0;
    }
    if (len < 0){
        return 0;
    }
    int len_arr[len];
    for (int i = 0; i < len; ++i) {
        len_arr[i] = strlen(arr[i]);
    }

    return 0;


}

char* spell_char(char arr,int len){
    char* res = (char*)malloc(len+1);
    memset(res,0,len+1);
    for (int i = 0; i < len; ++i) {
        res[i] = arr;
    }
    return res;
}







