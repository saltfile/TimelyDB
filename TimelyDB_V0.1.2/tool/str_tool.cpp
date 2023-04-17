//
// Created by saltfish on 23-4-17.
//
#include "tool_base.h"
/**
 * 字符串赋值给空字符串
 * @param str1 返回的内存指针
 * @param str2  被赋值的内容
 * @return 复制完成的指针
 */
char *str_copy(char *str1,char *str2){
    int str1_len = sizeof(char)*(strlen(str2)+1);
    str1 = (char *) malloc(str1_len);
    memset(str1,0,str1_len);
    strcpy(str1,str2);
    return str1;
}

/**
 * 字符串合并
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 返回合并好的字符串
 */
char *str_marge(char *str1,char *str2){
    char *p = str1;
    int res_len = strlen(str1)+ strlen(str2)+1;
    str1 = (char *) malloc(res_len);
    memset(str1,0,res_len);
    memcpy(str1,p, strlen(p));
    strcat(str1,str2);

    return str1;
}



/**
 * 获取拆分的长度
 * @param a 被拆分的字符串
 * @param b 要拆分的字符串
 * @return
 */
int str_spilt_size(char *a,char *b){
    char *str = a;
    char *dent = b;
    int strlens = strlen(str);
    char  ch[strlens];
    strcpy(ch,str);
    char* str1 = strtok(ch, dent);
    int i = 1;
    while (str1 != NULL)
    {
        str1 = strtok(NULL, dent);
        if (str1!=NULL){
            i++;
        }
    }

    return i;
}


/**
 * 字符串拆分
 * @param str 被拆的字符串
 * @param dent 要拆的字符串
 * @return
 */
char **str_spilt(char *str,char *dent){
    int size = str_spilt_size(str,dent);
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


/**
 * 只来释放字符串用的
 * @param str
 * @return
 */
char * free_str(char *str){
    char*p = str;
    str = NULL;
    return str;
}







