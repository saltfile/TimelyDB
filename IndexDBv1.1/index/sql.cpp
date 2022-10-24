//
// Created by zy on 2022/1/27.
//

#include "database_index.h"
#include "../grammar/Myall.h"
static tuple_head  *tupleHead=malloc_tuple_head();//这里可以设计为锁，不use databasename的时候，这个databasename不会变。
static  skip_list * skipList;
static  RBRoot * rbRoot;


char * strcat_vfs(char* cloumn,DataTypes type,char* type_size){
    char* clouname=(char*) malloc(sizeof (char));
    char* type_swap;

    switch(type){
        case BYTE:      {type_swap="byte";       break;}
        case INT:       {type_swap="int";        break;}
        case FLOAT:     {type_swap="float";      break;}
        case DOUBLE:    {type_swap="bouble";     break;}
        case DECIMAL:   {type_swap="decimal";    break;}
        case VARCHAR:   {type_swap="char*";      break;}/////////? 255写不写
        case TEXT:      {type_swap="text";       break;}
        case TIME:      {type_swap="time";       break;}
        case TIMESTAMP: {type_swap="timestamp";  break;}
        default: {perror("[ERROR] vfs type error\n");break;}
    }
    clouname= strcat(clouname,cloumn);
    clouname= strcat(clouname,"|");
    clouname= strcat(clouname,type_swap);

    return clouname;
}

void create_vfsNode(char *databasename,char *tablename,condition* sql) {
    printf("asdia\n");
    VfsTree * vfsTreeRoot = InitRootNode();
    VfsNode  * databaseNode = createNode(1,databasename,1,NULL,NULL,NULL);
    VfsNode  * table1Node = createNode(2,tablename,1,NULL,NULL,NULL);
    addVfsTreeNode(vfsTreeRoot->root,databaseNode);

    addVfsTreeNode(databaseNode,table1Node);


    while(sql!=NULL){
        char *clouname=strcat_vfs(sql->c_name,sql->dataTypes,sql->c_value);
        VfsNode  * columnNode = createNode(3,clouname,1,NULL,NULL,NULL);
        addVfsTreeNode(table1Node,columnNode);
//        free(clouname);/////////////////////////? 要不要free   你猜
        sql=sql->next;
    }
}

///////////////////////////////////////////销毁节点
void destory_sqlnode(sql_operation* sql){
    if (sql==NULL){
        printf("销毁成功");
    }
    while(sql->data_list!=NULL){
        free(sql);
    }
}
//判断下一个列是否为空，不为空进行传值，为空跳过
tuple_column* judge_nextcolum(tuple_column* tupleColum, condition* sql, char* sql_timstamp){

    tuple_column* node=malloc_tuple_colum();
//    node->datalist=malloc_tuple();

    node->datalist->timestamp=sql_timstamp;
    node->datalist->value=sql->c_value;

    node->columnname=sql->c_name;
//    node->dataTypes=sql->dataTypes;
    tupleColum=node;

    if (sql->next!= nullptr){
        tupleColum->nextcolumn= judge_nextcolum(tupleColum->nextcolumn,sql->next,sql_timstamp);
    }
    return tupleColum;
}


/*插入数据
 * */
char* sql_oper_insrtinto(sql_operation* sql){
    tupleHead->tablename=sql->name;
    tuple_column* column_node=malloc_tuple_colum();
    column_node->columnname=sql->data_list->c_name;
//            tupleHead->fileds->dataTypes=sql->data_list->dataTypes;
// 对于类型的判断？？?

//    column_node->datalist=malloc_vtuple();
    column_node->datalist->timestamp=sql->timestamp;
    column_node->datalist->value=sql->data_list->c_value;

    tupleHead->fileds=column_node;
    //将sql参数传入tupled里面
    if (sql->data_list->next!= nullptr){
        tupleHead->fileds->nextcolumn=judge_nextcolum(tupleHead->fileds->nextcolumn,sql->data_list->next,sql->timestamp);
    }
    printf("插入语句：%d\n", sizeof(tupleHead));

//    create_skip_index(tupleHead);//创建跳表索引（一级索引）
//
//    create_rbtree_index(tupleHead);//创建rbtree （二级索引）
if (tupleHead->databasename == NULL){
    char* res = "Error: Please use a database";
    return res;
}

    //执行循环列表的插入
    int aaa = create_cir_nodelist(tupleHead->databasename,tupleHead->tablename,tupleHead->fileds,tupleHead->fileds->datalist);
cout<<"fork:"<<aaa<<endl;
//    if (aaa == 2|| aaa == 3){
//    pthread_exit(NULL);
//    }



    char* res = "Successfully inserted 1 * row into ";
    str_merge(res,tupleHead->tablename);
    str_merge(res,"table !!");
    return res;
}
/*删除数据
 * */
void sql_oper_delete(sql_operation* sql){
    if (sql->name==NULL)  perror("[ERROR] select table can't be NULL\n");
    tupleHead->tablename=sql->name;

    char* swar= dbname_tname(tupleHead);//生成database_tablename

    TokenType symbol=sql->data_list->c_symbol;
    if (sql->timestamp!=NULL){//有时间戳且其余均为=，则是一级索引（跳表）

        while(symbol==Assignment && symbol!=NULL){
            symbol=sql->data_list->next->c_symbol;
        }
        // 判断这样的情况 ：where timestamp=xxxx and id>10
        if (symbol==Assignment || symbol==NULL) delete_skip_index(swar, sql->timestamp);//一级索引查找
            //对于一级索引的值进行，刘创操作
        else delete_rbtree_index(swar,sql,tupleHead);//删除二级索引（红黑树）

    } else delete_rbtree_index(swar,sql,tupleHead);//删除二级索引，二级索引查找一级索引，一级索引去环形列表or vfs查询


}
/*查找数据
 * */
void sql_oper_select(sql_operation* sql){
    if (sql->name==NULL)  perror("[ERROR] select table can't be NULL\n");
    tupleHead->tablename=sql->name;

    char* swar= dbname_tname(tupleHead);//生成database_tablename

    TokenType symbol=sql->data_list->c_symbol;
    if (sql->timestamp!=NULL){//有时间戳且其余均为=，则是一级索引（跳表）

        while(symbol==Assignment && symbol!=NULL){
            symbol=sql->data_list->next->c_symbol;
        }
        // 判断这样的情况 ：where timestamp=xxxx and id>10
        if (symbol==Assignment || symbol==NULL) find_skip_data(swar, sql->timestamp,tupleHead->databasename);//一级索引查找
            //对于一级索引的值进行，刘创操作
        else find_rbtree_data(swar,sql,tupleHead);//查找二级索引（红黑树）

    } else find_rbtree_data(swar,sql,tupleHead);//查找二级索引，二级索引查找一级索引，一级索引去环形列表or vfs查询
}

/*
 * 删除表
 * */
void sql_oper_drop_table(sql_operation* sql){
    if (sql->name==NULL)  perror("[ERROR] select table can't be NULL\n");
    tupleHead->tablename=sql->name;
    //先删除索引
    delete_index(tupleHead);
    //删除表
    rm_table(tupleHead->databasename,sql->name);
}

/*删除数据库（先删除索引）
 * */
void sql_oper_drop_database(sql_operation* sql){
    //获取到这个表中所有的表名，然后拼接字符串，删除?
    rm_table(tupleHead->databasename,sql->name);
    rm_database(sql->name);
}
//TODO:记得后面加锁
/*use databasename
 * */
bool sql_oper_use(sql_operation* sql){
    if (tupleHead!= nullptr){
        free(tupleHead);
    }
    tupleHead=malloc_tuple_head();
    passwd *user = get_user();
    int yy = strlen("/home/")+strlen(user->pw_name)+strlen("/indexTSDB/")+strlen(sql->name);
    char *path=(char *)malloc(yy);
    memset(path,0,yy);
    strcat(path,"/home/");
    strcat(path,user->pw_name);
    strcat(path,"/indexTSDB/");
    strcat(path,sql->name);
    if (access(path,F_OK)){
            cout<<"\n错误没有这个数据库";
        return false;
        } else{
        tupleHead->databasename=sql->name;
        return true;
        }
}


//show tables查看各个数据库所存在的表
char* back_dbname(){
    if (tupleHead == nullptr) {
        return NULL;
    }
    if (tupleHead->databasename != NULL){
    char* res = str_copy(res,tupleHead->databasename);
    return res;
    } else{
        return NULL;
    }
}








/*创建表
 * */
bool sql_oper_create_table(sql_operation* sql){
    if (tupleHead->databasename==NULL){
        perror("[ERROR] databaseName  can't be NULL\n");
        perror(" 先use databasename");
        return false;
    }
    tupleHead->tablename=sql->name;
    //建表,jjs那边需要的一些参数
    /*参数1*/
    int columnNum=0;
    condition* swap=sql->data_list;
    while(swap!= nullptr){
        columnNum++;
        swap=swap->next;
    }
    /*参数2* */
    char* colums[columnNum];
    condition* swap1=sql->data_list;
    for (int i = 0; i < columnNum; ++i) {
        colums[i]=swap1->c_name;
        swap1=swap1->next;
    }
    if (!touch_table(tupleHead->databasename, sql->name, colums, columnNum))return false;//jjs

    //建vfsnode
    create_vfsNode(tupleHead->databasename,tupleHead->tablename,sql->data_list);//jjs

    //生成map的key（databasename_tablename）,value为对应索引的头节点
    char* swar= dbname_tname(tupleHead);//生成database_tablename

    skipList= skip_list_init(swar); //在创建表的时候就，初始化对应的跳表，并且放进skip_map里面
    rbRoot= rbTree_init(swar); //在创建表的时候就，初始化对应的rbtree，并且放进rbtree_map里面

    set_map_node(swar,sql);//存放表结构？忘记了
    return true;
}


/*
 * 创建数据库
 * */
bool sql_oper_create_database(sql_operation* sql){

    char *syu = (char *)malloc(10);
    memset(syu,0,10);

    if (sql->name==NULL)  perror("[ERROR] create database false,databaseName  can't be NULL\n");
    char *path = mkdir_database(sql->name);
    //初始化完成
    VfsNode  * databaseNode = createNode(1,sql->name,1,NULL,NULL,NULL);
    databaseNode->filepath=(char *)malloc(strlen(path));
    memset(databaseNode->filepath,0,strlen(path));
    databaseNode->filepath = str_copy(databaseNode->filepath,path);
    //更新树节点
    VfsTree * vfs=createVfsTreeRoot();
    addVfsTreeNode(vfs->root,databaseNode);

    if (path!=NULL){
        return true;
    } else{
        return false;
    }
}




