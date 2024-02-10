//
// Created by saltfish on 23-4-19.
//
#include "eng_base.h"

static map<string, map<string, tab_struct>> DB_TAB_MAP;








/**
 * 建表的映射
 * 表结构文件存储方式：
 *  clonm_name$类型序号;
 */

bool DB_create_table(char* base_name,char* tab_name,char** clonms,data_type * types,int clonms_size){
    int is_succ = create_table(base_name,tab_name);
    if(is_succ != 1)return false;

    //TODO：明天要将这里写完






}


























