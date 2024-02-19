//
// Created by saltfish on 23-4-19.
//
#include "eng_base.h"

static map<string, map<string, tab_struct>> DB_TAB_MAP;


/**
 * 打开数据库时将对应的库刷进内存
 * @return
 */
bool DB_init_memery_tab() {
    /**
     * 后期加入try块儿
     */


    vector<string> bases = get_any_base();
    for (int i = 0; i < bases.size(); ++i) {
        string base_key = bases[i];
        vector<string> tab_s = get_any_table(base_key);
        map<string, tab_struct> push_map;
        for (int j = 0; j < tab_s.size(); ++j) {

            char *tsdata = const_cast<char *>(tab_s[j].c_str());
            tsdata = str_marge(tsdata,".tsdb");
            char *ts_data = file_read(const_cast<char *>(base_key.c_str()), const_cast<char *>(tsdata));
            int cloms = str_spilt_size(ts_data, ";");
            char **c_names = str_spilt(ts_data, ";");

            tab_struct tab;
            for (int k = 0; k < cloms; ++k) {
                char **type_s = str_spilt(c_names[k],"$");
                string col = type_s[0];
                data_type type = static_cast<data_type>(atoi(type_s[1]));


                arr_list *ptr = (arr_list *) malloc(sizeof(arr_list));
                memset(ptr, 0, sizeof(arr_list));
                ptr->initialization();

                tab.data_map.insert(pair<string ,arr_list*>(col, ptr));
                tab.type_map.insert(pair<string,data_type>(col,type));

            }
            push_map.insert(pair<string,tab_struct>(tab_s[j],tab));

        }
        DB_TAB_MAP.insert(pair<string,map<string,tab_struct>>(base_key,push_map));

    }
    return true;

}


/**
 * 建表的映射
 * 表结构文件存储方式：
 *  clonm_name$类型序号;
 */

bool DB_create_table(char *base_name, char *tab_name, char **clonms, data_type *types, int clonms_size) {
    bool result = false;

    int is_succ = create_table(base_name, tab_name);
    if (is_succ != 1)return result;

    tab_struct tab;
    //1.拼接表信息
    char *tsdb_data = "";
    for (int i = 0; i < clonms_size; ++i) {
        char stnum[16] = {0};
        tsdb_data = str_marge(tsdb_data, clonms[i]);
        tsdb_data = str_marge(tsdb_data, "$");
        tsdb_data = str_marge(tsdb_data, str_to_int(types[i], stnum, 10));
        tsdb_data = str_marge(tsdb_data, ";");
        string col = clonms[i];

        arr_list *ptr = (arr_list *) malloc(sizeof(arr_list));
        memset(ptr, 0, sizeof(arr_list));
        ptr->initialization();

        tab.type_map.insert(pair<string,data_type>(col,types[i]));
        tab.data_map.insert(pair<string ,arr_list*>(col, ptr));
    }
    //2.写入
    char *file_key = str_marge(tab_name, ".tsdb");
    result = file_write(base_name, file_key, tsdb_data) > 0;
    //3.同步到内存map
    string b_name = base_name;
    string t_name = tab_name;
    DB_TAB_MAP[b_name].insert(pair<string ,tab_struct>(t_name,tab));


    return result;
}








/**
 * 插入这里需要想想
 * @param base_name
 * @param tab_name
 * @return
 */
bool DB_insert_table(char *base_name,char *tab_name){

}
















