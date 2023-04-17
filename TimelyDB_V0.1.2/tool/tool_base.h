//
// Created by saltfish on 23-4-17.
//

#ifndef TIMELYDB_V0_1_2_TOOL_BASE_H
#define TIMELYDB_V0_1_2_TOOL_BASE_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;

//字符串框架

//字符串赋值
char *str_copy(char *str1,char *str2);
//字符串合并
char *str_marge(char *str1,char *str2);
//字符穿拆分
int str_spilt_size(char *a,char *b);
char **str_spilt(char *str,char *dent);









#endif //TIMELYDB_V0_1_2_TOOL_BASE_H
