//
// Created by saltfish on 23-4-19.
//
#include "eng_base.h"

static map<string, map<string, tab_struct>> DB_TAB_MAP;



/**
 * 打开数据库时将对应的库刷进内存
 * @return
 */
bool DB_init_memery_tab(){
    vector<string> bases = get_any_base();
    for (int i = 0; i < bases.size(); ++i) {
        string base_key = bases[i];
        vector<string> tab_s = get_any_table(base_key);

        for (int j = 0; j < tab_s.size(); ++j) {
//            file_read(base_key,tab_s[j])
        }










    }


}






/**
 * 建表的映射
 * 表结构文件存储方式：
 *  clonm_name$类型序号;
 */

bool DB_create_table(char* base_name,char* tab_name,char** clonms,data_type * types,int clonms_size){
    bool result = false;

    int is_succ = create_table(base_name,tab_name);
    if(is_succ != 1)return result;

    //1.拼接表信息
    char *tsdb_data = "";
    for (int i = 0; i < clonms_size; ++i) {
        char stnum[16] = {0};
        tsdb_data = str_marge(tsdb_data,clonms[i]);
        tsdb_data = str_marge(tsdb_data,"$");
        tsdb_data = str_marge(tsdb_data, str_to_int(types[i],stnum,10));
        tsdb_data = str_marge(tsdb_data,";");
    }
    //2.写入
    char *file_key = str_marge(tab_name,".tsdb");
    result = file_write(base_name,file_key,tsdb_data) > 0;

    return result;
}


























