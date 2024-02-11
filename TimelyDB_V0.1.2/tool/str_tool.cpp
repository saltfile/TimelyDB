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
    char *p = str1;
    int str1_len = sizeof(char)*(strlen(str2)+1);
    str1 = (char *) malloc(str1_len);
    memset(str1,0,str1_len);
    strcpy(str1,str2);
    free_str(p);
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
char *str_to_int(int num,char* str,int radix){
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。

    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=(unsigned)num;//若是num为正，直接赋值给unum

    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位

    }while(unum);//直至unum为0退出循环

    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整

    char temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }

    return str;//返回转换后的字符串
}






