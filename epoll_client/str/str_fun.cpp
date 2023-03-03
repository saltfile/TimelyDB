//
// Created by saltfish on 2022/5/10.
//
#include "../my_bases.h"

int size_of_buf(u8 *buf){
    for(int i = 0;i < 1002555l;i++){
        if(buf[i] == 0){
            return i+1;
        }
    }
    return sizeof(buf);
}




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


int spilt_size(char *a,char *b){
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
    return i;
}




char **split(char *str,char *dent){
    int size = spilt_size(str,dent);
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

char *strrpc(char *src,char *before,char *after){
    size_t src_size = strlen(src);
    size_t before_str_size = strlen(before);
    size_t after_str_size = strlen(after);
    char *dest = (char *)malloc(strlen(src)+1);
    memset(dest,0,sizeof(dest));
    size_t dest_offset = 0;
    for(size_t src_offset = 0;src_offset < src_size; ){
        if(!strncmp(src + src_offset,before,before_str_size)){
            memcpy(dest + dest_offset,after, after_str_size);
            src_offset += before_str_size;
            dest_offset += after_str_size;
        }else{
            memmove(dest + dest_offset,src + src_offset,1);
            dest_offset++;
            src_offset++;
        }
    }

    return dest;
}

int Str_FirFind(char *str_target,char *str_use)
{
    char *str_temp1 = NULL;
    char *str_temp2 = NULL;
    int count_i,count_j;
    int flg_find = 0;

    for(count_i = 1;*str_target != '\0';count_i++) {
        if(*str_target == *str_use){
            str_temp1 = str_target;
            str_temp2 = str_use;
            for(count_j = 1;*str_temp2 != '\0';count_j++){    //以要查找的字符串长度为循环回数
                str_temp1++;
                if(*str_temp1 == '\0'){                        //判断是否到目标字符串的结尾
                    break;
                }
                str_temp2++;
                if(*str_temp2 == '\0'){                        //判断是否到查找字符串的结尾
                    flg_find = 1;
                    break;
                }
                if(*str_temp1 != *str_temp2){
                    break;                                    //出现不相等的情况即返回上层循环重新查找
                }else if(*(str_temp2 + 1) == '\0'){         //如果下一个字符为结尾，那么证明已经找到
                    flg_find = 1;
                    break;
                }
            }
        }
        if(flg_find == 1){
            printf("First Position: %d\n",count_i);
            return count_i;
        }
        str_target++;
    }
    printf("No Find ""%s""\n",str_use);
}



char *strrpc_first(char *src,char *before,char *after){
    size_t src_size = strlen(src);
    size_t before_str_size = strlen(before);
    size_t after_str_size = strlen(after);
    char *dest = (char *)malloc(strlen(src)+1);
    memset(dest,0,sizeof(dest));
    size_t dest_offset = 0;
    int c = 0;
    for(size_t src_offset = 0;src_offset < src_size; ){
        if(!strncmp(src + src_offset,before,before_str_size)&&c == 0){
            memcpy(dest + dest_offset,after, after_str_size);
            src_offset += before_str_size;
            dest_offset += after_str_size;
            c = 1;
        }else{
            memmove(dest + dest_offset,src + src_offset,1);
            dest_offset++;
            src_offset++;
        }
    }

    return dest;
}

