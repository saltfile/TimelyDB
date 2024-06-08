//
// Created by saltfish on 23-4-19.
//
#include "eng_base.h"
static map<string, map<string, tab_struct>> DB_TAB_MAP;

static char * databasename = NULL;

static int RING_LEN = 5;
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
            char *col_together = "";
            tab_struct tab;
            for (int k = 0; k < cloms; ++k) {
                char **type_s = str_spilt(c_names[k],"$");
                string col = type_s[0];
                col_together = str_marge(col_together,(char*)col.c_str());
                col_together = str_marge(col_together,";");
                data_type type = static_cast<data_type>(atoi(type_s[1]));

                ring_list *ptr = (ring_list *) malloc(sizeof(ring_list));
                memset(ptr, 0, sizeof(ring_list));
                ptr->initialization(RING_LEN,type);
                tab.data_map.insert(pair<string ,ring_list*>(col, ptr));
                tab.type_map.insert(pair<string,data_type>(col,type));


            }
            tab.col_together_name = col_together;
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
    char *tab_colnm_to = "";
    //  1.先把所有列名字合并
    for (int i = 0; i < clonms_size; ++i) {
        tab_colnm_to = str_marge(tab_colnm_to,clonms[i]);
        tab_colnm_to = str_marge(tab_colnm_to,";");
    }

    for (int i = 0; i < clonms_size; ++i) {
        char stnum[16] = {0};
        tsdb_data = str_marge(tsdb_data, clonms[i]);
        tsdb_data = str_marge(tsdb_data, "$");
        tsdb_data = str_marge(tsdb_data, str_to_int(types[i], stnum, 10));
        tsdb_data = str_marge(tsdb_data, ";");
        string col = clonms[i];

        ring_list *ptr = (ring_list *) malloc(sizeof(ring_list));
        memset(ptr, 0, sizeof(ring_list));
        ptr->initialization(RING_LEN,types[i]);

        tab.type_map.insert(pair<string,data_type>(col,types[i]));
        tab.data_map.insert(pair<string ,ring_list*>(col, ptr));
    }
    tab.col_together_name = tab_colnm_to;
    //2.写入
    char *file_key = str_marge(tab_name, ".tsdb");
    result = file_write(base_name, file_key, tsdb_data) > 0;
    //3.同步到内存map
    string b_name = base_name;
    string t_name = tab_name;
    DB_TAB_MAP[b_name].insert(pair<string ,tab_struct>(t_name,tab));


    return result;
}



bool create_database_db(char *basename){
    bool res = false;
    //查看是否已存在

    string base_key = basename;
    char *base_path = load_config_path();
    base_path = str_marge(base_path,"/");
    base_path = str_marge(base_path,basename);

    bool file_exist = file_is_exist(base_path);
    if (file_exist){
        return res;
    }
    //内存建库
    map<string, tab_struct> push_map;
    DB_TAB_MAP.insert(pair<string,map<string,tab_struct>>(base_key,push_map));
    //文件建库
    int result = create_database(basename);
    if (result == 1){
        res = true;
    }
    return res;
}

bool use_database(char *basename){
    bool res = false;
    //查看是否已存在

    string base_key = basename;
    bool file_exist = database_is_exist(basename);
    auto it = DB_TAB_MAP.find(base_key);
    if (!file_exist||it == DB_TAB_MAP.end()){
        return res;
    }
    databasename = str_copy("",basename);
    res = true;
    return res;
}

char *is_use_database(){
    if (databasename == NULL)return NULL;
    char *result = str_copy("",databasename);
    return result;
}

/**
 * 单行插入
 * @param base_name
 * @param tab_name
 * @return
 */
bool DB_insert_table(char *base_name,char *tab_name,char **colum_key,int key_size,char** colum_val,int val_size){
    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];

    for (int i = 0; i < key_size; ++i) {
        char *a1 = colum_key[i];
        string col_key = a1;
        data_type type_ins = ins_tab.type_map[col_key];
        char *val = colum_val[i];
        switch (type_ins) {
            case INT:
                if (strcmp(colum_val[i],"nil") != 0)
                    ins_tab.data_map[col_key]->add(str_to_type_int(colum_val[i]));
                else
                    ins_tab.data_map[col_key]->add(str_to_type_int("0"));
                break;
            case VARCHAR:
                ins_tab.data_map[col_key]->add(str_to_type_varchar(colum_val[i]));
                break;
            case TIMESTAMP:
                ins_tab.data_map[col_key]->add(get_now_timestamp());
                break;
        }
//
    }

}
bool DB_tab_is_exist(char *tab_name){
    string base_key = is_use_database();
    string tab_key = tab_name;
    auto it = DB_TAB_MAP.find(base_key);
    if (it == DB_TAB_MAP.end()){
        return false;
    }
    auto tab_it = DB_TAB_MAP[base_key].find(tab_key);
    if (tab_it == DB_TAB_MAP[base_key].end()){
        return false;
    }
    return true;
}



bool DB_colum_is_exist(char *tab_name,char *col_name){
    string base_key = is_use_database();
    string tab_key = tab_name;
    tab_struct i_tab = DB_TAB_MAP[base_key][tab_key];
    string col_key = col_name;
    auto it = i_tab.type_map.find(col_key);
    if (it == i_tab.type_map.end()){
        return false;
    }
    return true;

}



/**
 * 从环中取出某一行
 */

vector<string> get_DB_once_row(char *base_name,char *tab_name,int idx_nums){
    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];

    vector<string> result;
    char **cols = str_spilt(ins_tab.col_together_name,";");
    int cols_len = str_spilt_size(ins_tab.col_together_name,";");

    for (int i = 0; i < cols_len; ++i) {
        string col_key = cols[i];
        data_type col_type  = ins_tab.type_map[col_key];
        void *val = ins_tab.data_map[col_key]->get(idx_nums);
        switch (col_type) {
            case INT: {
                integer *int_p = (integer *) val;
                result.push_back(int_p->to_string());
            }break;
            case VARCHAR: {
                varchar *char_p = (varchar *) val;
                result.push_back(char_p->to_string());
            }break;
            case TIMESTAMP: {
                long *long_p = (long *)val;
                result.push_back(to_string(*long_p));
            }break;
        }
    }

    return result;

}

/**
 * 通过读取单表数据环来获取全部数据
 */
vector<string> get_DB_data(char *base_name,char *tab_name){

    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];

    vector<string> result;
    char **cols = str_spilt(ins_tab.col_together_name,";");
    int cols_len = str_spilt_size(ins_tab.col_together_name,";");

    int ring_size = RING_LEN;
    for (int r = 0; r < ring_size; ++r) {

        string data_row = "";

        for (int i = 0; i < cols_len; ++i) {
            string col_key = cols[i];
            data_type col_type = ins_tab.type_map[col_key];
            void *val = ins_tab.data_map[col_key]->get(r);
            if (val == NULL){
                data_row = data_row + "nil";
                data_row = data_row + ";";
                continue;
            }
            switch (col_type) {
                case INT: {
                    integer *int_p = (integer *) val;
                    data_row = data_row + int_p->to_string();
                    data_row = data_row + ";";
                }
                    break;
                case VARCHAR: {
                    varchar *char_p = (varchar *) val;
                    data_row = data_row + char_p->to_string();
                    data_row = data_row + ";";
                }
                    break;
                case TIMESTAMP:{
                    long *l_ptr = (long *)val;
                    data_row = data_row + to_string(*l_ptr);
                    data_row = data_row + ";";
                }
            }
        }

        result.push_back(data_row);
    }

    return result;
}


/**
 * 获取所有库表信息 用;隔开   库名;表名
 */

vector<string> get_all_tab_name(){
    vector<string> result;
    for (auto it = DB_TAB_MAP.begin(); it != DB_TAB_MAP.end(); ++it) {
       string base_name = it->first;
        for (auto i = DB_TAB_MAP[base_name].begin(); i != DB_TAB_MAP[base_name].end(); ++i) {
            string tab_name = base_name +";"+ i->first;
            result.push_back(tab_name);
        }

    }
    return result;
}

/**
 * 获取一张表所有列
 */

vector<string> get_tab_colums(char* base_name,char* tab_name){
    vector<string> res;
    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];
    for (auto it = ins_tab.type_map.begin(); it != ins_tab.type_map.end(); ++it) {
        res.push_back(it->first);
    }
    return res;
}

//typedef void(*mointor_handler) (char *base_name,char *tab_name,char *file,int times,vector<string> colnms);

map<string,string> get_tab_map_colums(char* base_name,char* tab_name){
    map<string,string> res;
    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];
    for (auto it = ins_tab.type_map.begin(); it != ins_tab.type_map.end(); ++it) {
        res.insert(pair<string,string>(it->first,"nil"));
    }
    return res;
}






/**
 * 轮询监控
 * @param base_name
 * @param tab_name
 * @param count
 * @param ...
 *
 */
void mointor_s(char *base_name,char *tab_name,char *file,vector<string> colnms){
    string base_key = base_name;
    string tab_key = tab_name;
    tab_struct ins_tab = DB_TAB_MAP[base_key][tab_key];
    map<string,string> iot_map = read_iot(file,colnms);
    vector<string> col = get_tab_colums(base_name,tab_name);
    char** col_key = NULL;
    char** col_val = NULL;
    col_key = ( char**)calloc( col.size(),  sizeof( char*));
    col_val = ( char**)calloc( col.size(),  sizeof( char*));


    for (int i = 0; i < col.size(); ++i) {
        string k = col[i];
        auto it = iot_map.find(k);
        col_key[i] = (char *) malloc(k.size()*sizeof(char *));
        strcpy(col_key[i],k.c_str());
        if (it == iot_map.end()){
            col_val[i] = str_copy("","nil");
            continue;
        }
        string v = iot_map[k];
        col_val[i] = (char *) malloc(v.size()*sizeof(char *));
        strcpy(col_val[i],v.c_str());
    }
    DB_insert_table(base_name,tab_name,col_key,col.size(),col_val,col.size());


}






