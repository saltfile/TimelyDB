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

int create_database(char *base_name) {
    char *base = str_copy(base, get_config_base_path());
    base = str_marge(base, "/");

    char *base_path = str_marge(base, base_name);
    int result = create_mkdir(base_path);
    string key = base_path;

    map<string, FILE *> val;
    if (result == 1) {
        DB_FILE_MAP.insert(pair<string, map<string, FILE *>>(key, val));
    }

    return result;
}
//TODO:这里仍然需要多多斟酌
int create_table(char *database, char *table) {


    return 1;


}










