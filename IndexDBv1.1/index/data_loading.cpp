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


char* path_merge(char* database,char* table){
    char* path = "/home/saltfish/indexTSDB";
    char*res = str_merge("",path);
    res = str_merge(res,"/");
    res = str_merge(res,database);
    res = str_merge(res,"/");
    res = str_merge(res,table);

    return res;
}


//初始化时一开始就有的数据
tuple_head* create_skip_data(tab_file *tabFile){
    //最后返回的结果
    tuple_head *res = malloc_tuple_head_null();
    //数据库名和表名
    char** dtname = split_gar(tabFile->db_t_name,"_");
    res->databasename = str_copy(res->databasename,dtname[0]);
    res->tablename = str_copy(res->tablename,dtname[1]);
    tuple_column *files = NULL;

    for (int i = 0; i < tabFile->col_len; ++i) {
        tuple_column *p = (tuple_column*) malloc(sizeof(tuple_column));
        memset(p, 0, sizeof(tuple_column));

        p->columnname = str_copy("",tabFile->colums[i]);
        if (files == NULL)files = p;
        else files->nextcolumn = p;
    }

    int flag = tabFile->col_len;
//    map<char*,int> times_map;

    for (int i = 0; i < tabFile->tab_len;i+=flag ) {
        tuple_column*p = files;
        for (int j = i; j <i+flag; ++j) {

            char** data = split_gar(tabFile->datas[j],";");
            p->datalist = value_tuple_add(p->datalist,data[0],data[1]);
            p = p->nextcolumn;
        }
    }
    res->fileds = files;

    return res;


}




//使用文件树预留接口遍历所有数据库和表
void library_table_federation(){
    char* all_base = showDataBase();
    if (strlen(all_base)==0)return;
    int base_len = spilt_size_gar(all_base,",");
    char** bases = split_gar(all_base,",");

    for (int i = 0; i < base_len; ++i) {
        char* tabs = showTables(bases[i]);
        if (strlen(tabs)==0)continue;
        int tab_lens = spilt_size_gar(tabs,",");
        char** tab_arr = split_gar(tabs,",");


        //将表中数据装入结构
        for (int j = 0; j < tab_lens; ++j) {
            char* data_path = path_merge(bases[i],tab_arr[j]);
            tab_file *tab_datas = read_table_data(data_path);
            tab_datas->db_t_name = str_merge("",bases[i]);
            tab_datas->db_t_name = str_merge(tab_datas->db_t_name,"_");
            tab_datas->db_t_name = str_merge(tab_datas->db_t_name,tab_arr[j]);
            skip_list_init(tab_datas->db_t_name);
            tuple_head *p  = create_skip_data(tab_datas);



            sql_operation* create_table=malloc_sqloperation();
            create_table->handler=CREATE_TABLE;
            create_table->name="item";

//    create_table->data_list=malloc_sqlcondition();
            create_table->data_list->next=malloc_sqlcondition();
            create_table->data_list->next->next=malloc_sqlcondition();

            create_table->data_list->c_name="age";
            create_table->data_list->dataTypes=INT;

            create_table->data_list->next->c_name="name";
            create_table->data_list->next->dataTypes=VARCHAR;
            create_table->data_list->next->c_value="255";


            set_map_node(tab_datas->db_t_name,create_table);

            rbTree_init(tab_datas->db_t_name);
            skip_list_init(tab_datas->db_t_name);
            create_skip_index(p);
            create_rbtree_index(p);
        }


        sql_operation* select_sql=malloc_sqloperation();
        select_sql->handler=SELECTS;
        select_sql->name="item";
        select_sql->field="*";

//    select_sql->data_list=malloc_sqlcondition();
        select_sql->data_list->c_name="age";
        select_sql->data_list->c_symbol=Assignment;//>
        select_sql->data_list->c_value="18";
//    select_sql->data_list->dataTypes=INT;

        //select_sql->timestamp="18";

        select_sql->data_list->next=malloc_sqlcondition();
        (select_sql->data_list->next)->cTypes=AND;
        (select_sql->data_list->next)->c_name="name";
        (select_sql->data_list->next)->c_symbol=GE;//>=
        (select_sql->data_list->next)->c_value="aaaaaa";
//    (select_sql->data_list->next)->dataTypes=VARCHAR;

        select_sql->data_list->next->next=malloc_sqlcondition();
        (select_sql->data_list->next)->next->cTypes=GROUPBY;
        select_sql->data_list->next->next->next=malloc_sqlcondition();
        (select_sql->data_list->next)->next->next->cTypes=Desc;


        sql_oper_select(select_sql);




    }
}











int Load_Test(){
    engine_init(5);
//    snappy::Uncompress()
    char* filepath = "/home/saltfish/indexTSDB/com/item";
    library_table_federation();
//    read_table_data(filepath);
    return 0;
};






