//
// Created by maomao on 2021/8/20.
//
//#include "global_c.h"
#include "database_engine.h"
//#include "database_engine.h"

void isInitVsfTree(){
    if (vfsTreeRoot->root==NULL)
    {
        vfsTreeRoot->root = (VfsNode *)InitRootNode();
    }

}

//加载文件树
void loadVfsTree(){

}

//建库
void createDatabase(char* databaseName){
    isInitVsfTree();
    if (databaseName == NULL){
        perror("[ERROR] the databaseName can not be NULL\n");
    }
    VfsNode *dbNode = createNode(1,databaseName,1,NULL,NULL,NULL);
    if (addVfsTreeNode(vfsTreeRoot->root,dbNode)==ITrue){
        char * file_path=mkdir_database(databaseName);
        dbNode->filepath=(char *)malloc(strlen(file_path));
        dbNode->filepath=file_path;  //创建数据库时获取数据库路径
    }

}
/*

 * @param databaseName
 * @param tableName
 * @param columns
 * @param columnSize
 */

//建表
void createTable(char* databaseName,char* tableName,char** columns,int columnSize){
    isInitVsfTree();
    if (databaseName == NULL || tableName ==NULL || columns == NULL || columns ==0)
        perror("[ERROR] databaseName or tableName or columns or columns can't be NULL\n");
        //return error;

    VfsNode * database=findNodeByName(vfsTreeRoot->root->cList,databaseName);
    VfsNode *tNode=createNode(2,tableName,1,NULL,database,NULL);

    for (int i = 0; i < columnSize; ++i) {
        char* columnName=columns[i];
        VfsNode *columnNode = createNode(3,columnName,1,NULL,tNode,NULL);
        if (addVfsTreeNode(tNode,columnNode)!=ITrue){
            perror("[ERROR] create table fail\n ");
        };
    }
    touch_table(database->name,tableName,columns,columnSize);
}

//删库
void deleteDatabase(char* databaseName){
    if (databaseName==NULL){

    }
    //删除数据库
    if (removeNode(vfsTreeRoot->root->cList,databaseName)==ITrue){
        rm_database(databaseName);
    };
    ///TODO 文件操作
}

//删表
void deleteTable(char* databaseName,char* tableName){
    if (databaseName == NULL || tableName == NULL){

    }
    VfsNode * dbNode=findNodeByName(root->cList,databaseName);
    if (removeNode(dbNode->cList,tableName)==ITrue){
        rm_table(databaseName,tableName);
    };
}


//查看库信息
void selectDatabase(){
    showDataBase();
}

//查看表信息
void selectTable(char* databaseName){
    if (databaseName == NULL){

    }
    showTables(databaseName);
}


