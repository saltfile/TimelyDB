//
// Created by saltfish on 23-10-22.
//

#include "tool_base.h"
#include "../config_init/config_h.h"

/**
 * 本地文件映射
 * map< key: 数据库名称，  val: map<key :表文件，val： 文件指针>>
 */
static map<string, int> BASE_MAP;
static map<string, map<string, FILE *>> DB_FILE_MAP;

void file_test() {
    FILE *f_write = fopen("../test.txt", "a+");
    if (f_write == NULL) {
        return;
    }
    char buf[] = "this is first test";
    fputs(buf, f_write);
    fclose(f_write);

    //读文件
    FILE *f_read = fopen("../test.txt", "r");
    if (f_read == NULL) {
        return;
    }
    char ch;
    while ((ch = fgetc(f_read)) != EOF)  // EOF  Enf of File
    {
        printf("%c", ch);
    }
    fclose(f_read);

}

int create_mkdir(char *path) {
    if (access(path, F_OK)) {
        int isCreate = mkdir(path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if (!isCreate) {
            printf("成功创建数据库:%s\n", path);
            return 1;
        } else {
            printf("创建数据库失败! error: %s , %d \n", path, isCreate);
            return -1;
        }
    } else {
        printf("数据库已存在\n");
        return 0;
    }
}

bool file_is_exist(char *path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

FILE *create_file(char *path, char *suffix) {
    char *tab_path = str_marge(path, suffix);
    if (!file_is_exist(tab_path)) {
        FILE *file = fopen(tab_path, "a");
        return file;
    } else {
        return NULL;
    }
}

bool database_is_exist(char *database) {
    if (database == NULL)return false;
    string key = database;
    auto it = DB_FILE_MAP.find(key);
    if (it != DB_FILE_MAP.end()) {
        return true;
    } else {
        return false;
    }
}

int create_database(char *base_name) {
    char *base = str_copy(base, get_config_base_path());
    base = str_marge(base, "/");

    char *base_path = str_marge(base, base_name);
    int result = 0;

    if (file_is_exist(base_path)) {
        return result;
    }

    string key = base_path;

    map<string, FILE *> val;

    result = create_mkdir(base_path);
    //创建数据库成功后才可以添加进映射map
    if (result == 1) {
        DB_FILE_MAP.insert(pair<string, map<string, FILE *>>(key, val));
    }
    return result;
}


bool table_is_exist(char *database, char *table) {
    string key = database;
    string tab_key = table;
    if (!database_is_exist(database))return false;

    auto it = DB_FILE_MAP[key].find(key);
    if (it != DB_FILE_MAP[key].end()) {
        return true;
    } else {
        return false;
    }
}

int create_table(char *database, char *table) {
    //1.先查看数据库是否存在
    string base_key = database;

    char *base = str_copy(base, get_config_base_path());
    base = str_marge(base, "/");
    base = str_marge(base, database);
    base = str_marge(base, "/");
    base = str_marge(base, table);
    //2.如果数据库不存在返回-1
    if (database_is_exist(database)) {
        //2.1查看是否已经存在表
        if (table_is_exist(database, table)) {
            return -2;
        } else {
            //2.1.1创建基础存储文件表表结构元数据&先不创建索引
            /**
             * 1.数据源文件只是普通的txt
             * 2.表结构元数据文件+tsdb
             */
            //2.1.1创建数据文件
            FILE *db_file = fopen(base, "rw+");
            //2.1.2创建元数据文件
            char *des_path = str_marge(base, ".tsdb");
            FILE *des_file = fopen(des_path, "rw+");

            string db_key = table;
            string des_key = str_marge(table, ".tsdb");
            DB_FILE_MAP[base_key].insert(pair<string, FILE *>(db_key, db_file));
            DB_FILE_MAP[base_key].insert(pair<string, FILE *>(des_key, des_file));

            return 1;
        }
    } else {
        return -1;
    }


}




int get_databse_num(){
    DIR * dp;
    struct dirent *filename;

    char* local_host = str_copy(local_host,get_config_base_path());

    dp = opendir(local_host);
    if (!dp)
    {
        fprintf(stderr,"open directory error\n");
        return -1;
    }
    int res = 0;
    while (filename = readdir(dp))
    {
        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,"..")){
            res++;
        }
    }

    closedir(dp);
    return res;
}


int get_tables_num(char *database_path){


    DIR * dp;
    struct dirent *filename;

    dp = opendir(database_path);
    if (!dp)
    {
        fprintf(stderr,"open directory error\n");
        return -1;
    }
    int res = 0;
    while (filename = readdir(dp))
    {
        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,".."))
            res++;
    }
    return res;
}


char ** find_tables(char *database_path){

    int size = get_tables_num(database_path);
    char **res =  (char**) malloc(size * sizeof(char*));
    memset(res,0,sizeof(res));

    //遍历目录下的文件
    DIR * dp;
    struct dirent *filename;

    dp = opendir(database_path);
    if (!dp)
    {
        fprintf(stderr,"open directory error\n");
        return NULL;
    }

    int i = 0;
    while (filename = readdir(dp))
    {

        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,"..")){

            char *tab_path = str_marge("",filename->d_name);
            res[i] = tab_path;
            i++;
        }

    }
    return res;

}




char** find_database(){
    int size = get_databse_num();
    char **res =  (char**) malloc(size * sizeof(char*));
    memset(res,0,sizeof(res));
    char* local_host = str_copy(local_host,get_config_base_path());
    //遍历目录下的文件
    DIR * dp;
    struct dirent *filename;

    dp = opendir(local_host);
    if (!dp)
    {
        fprintf(stderr,"open directory error\n");
        return NULL;
    }

    int i = 0;
    while (filename = readdir(dp))
    {

        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,"..")){
            struct stat buf;
            char* path = str_copy(path,filename->d_name);
            res[i] = path;
            i++;
        }

    }
    return res;

}

//获取对应的文件指针
FILE *get_file_ptr(char *file_path){
    if (file_is_exist(file_path)) {
        FILE *file = fopen(file_path, "rw+");
        return file;
    } else {
        return NULL;
    }
}


void init_file_system(){
    int base_num = get_databse_num();
    char ** database_s = find_database();

    for (int i = 0; i < base_num; ++i) {
        string key = database_s[i];   //数据库本地文件夹名称
        map<string, FILE *> val;

        char *base_local_path = str_copy(base_local_path,get_config_base_path());
        base_local_path = str_marge(base_local_path,"/");
        base_local_path = str_marge(base_local_path,(char *)key.c_str());

        int table_file_num = get_tables_num(base_local_path);
        char **table_files = find_tables(base_local_path);

        for (int j = 0; j < table_file_num; ++j) {
            char *table_local_path = str_copy(table_local_path,get_config_base_path());
            char *tab_name = table_files[j];
            table_local_path = str_marge(table_local_path,"/");
            table_local_path = str_marge(table_local_path,(char *)key.c_str());
            table_local_path = str_marge(table_local_path,"/");
            table_local_path = str_marge(table_local_path,tab_name);

            FILE *file_ptr = get_file_ptr(table_local_path);
            string tab_key = tab_name;
            val.insert(pair<string,FILE *>(tab_key,file_ptr));
        }

        DB_FILE_MAP.insert(pair<string, map<string, FILE *>>(key, val));
    }





}







