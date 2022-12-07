//
// Created by saltfish on 22-12-6.
//
/**
* 此文件为了载入对应表的数据
*/
#include "database_index.h"
#include "../grammar/Myall.h"

//TODO:12-06 理论接口已经清楚，明天完成整个部分

// string 转 char
char* string_trans_char(string tmp){
    char *res = (char*) malloc(sizeof(tmp.size())+1);
    memset(res,0,tmp.size()+1);

    strcpy(res,tmp.c_str());

    res[tmp.size()] = 0;
    return res;
}
//  解压API
char * decompress_data(char* str){
    string string1;
    snappy::Uncompress(str, strlen(str),&string1);
    cout<<string1;
    char *res = string_trans_char(string1);
    return res;
}

//赋值专用
char* assign_char(char *res,char *str){
    res = (char*) malloc(strlen(str)+1);

    memset(res,0, strlen(str)+1);
    strcpy(res,str);

    return res;
}

//读取一个表中的数据
tab_file* read_table_data(char* filepath){
    tab_file *res = (tab_file*) malloc(sizeof(tab_file));
    memset(res,0, sizeof(tab_file));
    FILE *fp = fopen(filepath, "r");
    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    int flen=ftell(fp); /* 得到文件大小 */
    char* p=(char *)malloc(flen+1); /* 根据文件大小动态分配内存空间 */
    if(p==NULL)
    {
        fclose(fp);
        return NULL;
    }
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
    fread(p,flen,1,fp); /* 一次性读取全部文件内容 */

    p[flen]=0;
    fclose(fp);
    char **chars = split_gar(p,"\n");
    int files = spilt_size_gar(p,"\n");

    res->col_len = spilt_size_gar(chars[0],";");
    res->colums = split_gar(chars[0],";");
    res->tab_len = files-1;
    res->datas = (char**) malloc((files-1)*sizeof(char*));
    memset(res->datas,0, sizeof(res->datas));
    for (int i = 1; i < files; ++i) {
        char* p = decompress_data(chars[i]);
        res->datas[i-1] = assign_char(res->datas[i-1], p);
    }
    return res;
}




//使用文件树预留接口遍历所有数据库和表
void library_table_federation(){
    char* all_base = showDataBase();








}











int Load_Test(){
    engine_init(5);
//    snappy::Uncompress()
    char* filepath = "/home/saltfish/indexTSDB/com/item";
    library_table_federation();
//    read_table_data(filepath);
    return 0;
};






