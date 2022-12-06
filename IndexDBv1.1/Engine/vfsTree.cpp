//
// Created by maomao on 2021/8/20.
//
#include "database_engine.h"
#include "../grammar/Myall.h"
#include "../index/database_index.h"
//#include "vfsTree.h"
//#include "global_c.h"
VfsTree *vfsTreeRoot;
VfsNode *root;





VfsTree * createVfsTreeRoot(){
    return vfsTreeRoot;
}







char* nameComplete;

//初始化孩子链表头节点
ChildList * InitHeadNode()
{
    ChildList* newList = (ChildList *)malloc(sizeof(ChildList));
    //确保内存申请成功
    if (newList != NULL)
    {
        newList->size=0;
        newList->head=NULL;
        newList->tail=NULL;
        return newList;
    }
    return NULL;
}

//生成节点
VfsNode * createNode(int level,char *name,int flag,VfsNode* next,VfsNode *parentNode,ChildList * cList)
{
    VfsNode *newNode = (VfsNode*)malloc(sizeof(VfsNode));

    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->level = level;
    newNode->name  = name;
    newNode->flag  = flag;
    newNode->next  = next;
    newNode->cList = cList;
    newNode->parentNode = parentNode;
    printf("%d,%d,%s\n",level,flag,name);
    return newNode;
}

//遍历链表查看是否有相同的名字  -1表示错误
IBool  foreachListByName(ChildList *list ,char *name)
{
    if (list ==NULL ||list->size == 0|| name == NULL)
    {
        return Ierror;
    }
    VfsNode *temp;
    for (temp=list->head; temp!= NULL ; temp = temp->next) {
        //如果两个字符串相等
        if (strcmp(temp->name,name)==0)
        {
            return IFalse;
        }
    }
    return ITrue;
}

//添加节点
IBool addNode(ChildList *list,VfsNode *addNode)
{

    printf("%d,%d,%s\n",addNode->level,addNode->flag,addNode->name);;
    if (list == NULL || addNode ==NULL)
    {
        return Ierror;
    }

    if (list->head == NULL)
    {
        list->head = addNode;
        list->tail = addNode;
    }
    else if (foreachListByName(list,addNode->name)==ITrue)
    {
        list->tail->next = addNode;
        list->tail = addNode;
    }else
    {
        printf("重名了%s\n",addNode->name);
        return IFalse;
    }
    list->size++;
    printf("增加的节点名称为=%s，当前链表长度为=%d\n",addNode->name,list->size);
    return ITrue;
}

//根据名称查找节点
VfsNode *findNodeByName(ChildList *list,char* name)
{
    if (list == NULL ||list->size == 0|| name ==NULL)
    {
        return NULL;
    }

    VfsNode *temp;
    for (temp=list->head;  temp != NULL ; temp = temp->next) {
        if (strcmp(temp->name,name)==0)
        {
            printf("find it level = %d,flag=%d,name=%s\n",temp->level,temp->flag,temp->name);
            return temp;
        }
    }
    return NULL;
}



VfsNode *findClonmByName(ChildList *list,char* name)
{
    if (list == NULL ||list->size == 0|| name ==NULL)
    {
        return NULL;
    }

    VfsNode *temp;
    for (temp=list->head;  temp != NULL ; temp = temp->next) {
        char** colms = split_gar(temp->name,"|");
        if (strcmp(colms[0],name)==0)
        {
            printf("find it level = %d,flag=%d,name=%s\n",temp->level,temp->flag,temp->name);
            return temp;
        }
    }
    return NULL;
}





//遍历子链表
char * foreachList(ChildList* list)
{

    if (list == NULL || list->size == NULL)
    {
       // return error;
    }
    VfsNode *temp;
    //TODO 内存大小合理计算
    nameComplete=(char*)malloc(100*sizeof(char*));
  /*  memset(nameComplete,'/0',sizeof(nameComplete));*/
    int i = 0;
    if (list !=NULL && list->size != 0)
    {
        for (temp = list->head;temp != NULL;temp = temp->next) {
            if (i==0){
                strcat(nameComplete,temp->name);
                i++;
            }
            else
            {
                strcat(nameComplete,",");
                strcat(nameComplete,temp->name);
                i++;
            }
            printf("节点名称=%s\n",temp->name);
        }

        return nameComplete;
    }
}

//销毁节点
void * deleteNode(VfsNode* node)
{

   free(node);
   node = NULL;
}

//删除节点
IBool removeNode(ChildList *list,char* name)
{

    if (list == NULL || list->size == 0 || name == NULL)
    {
        return Ierror;
    }

    VfsNode * temp;
    //用于尾指针删除
    VfsNode * dNode;
    VfsNode* destroyNode=findNodeByName(list,name);


    if (destroyNode == NULL)
    {
        printf("该链表不存在名称为:%s的节点\n",name);
        return IFalse;
    }
    if (destroyNode->flag ==0)
    {
        printf("该节点不可删除->%s\n",name);
        return IFalse;
    }
    if (list->size ==1)
    {
       deleteNode(destroyNode);
       list->head=NULL;
       list->tail=NULL;
       list->size =0;
        return ITrue;
    }
    if (destroyNode->next != NULL)
    {
        temp = destroyNode->next;
        deleteNode(destroyNode);
        //防止浅拷贝
        destroyNode->next = temp->next;
        destroyNode->name = temp->name;
        destroyNode->flag = temp->flag;
        destroyNode->level = temp->level;
        destroyNode->cList = temp->cList;
        list->size--;
        return ITrue;
    }
    else {

        temp=list->head;
        dNode=list->head->next;
        while (dNode)
        {
            if (dNode->name == name)
            {
                temp->next=NULL;
                deleteNode(dNode);
                list->tail=temp;
                list->size--;
                return ITrue;
            }
            temp = dNode;
            dNode = dNode->next;
        }


    }

}

//TODO:10-12  完成后续show table操作
char* show_table_panle(){
    char*res = back_dbname();
    if (res == NULL){
        return "Error: Please use or check whether the statement is correct!";
    }
    vfsTree * p = vfsTreeRoot;
    vfsNode*DB_list = p->root->cList->head;
    vfsNode *DB;
    while (DB_list){

        if (strcmp(DB_list->name,res) == 0){
            DB = DB_list;
            break;
        }
        DB_list = DB_list->next;
    }
    if (DB == nullptr){
        return "Error: database exception";
    }
if (DB->cList == NULL){
    return "This is Empty";
}
    vfsNode* table_list = DB->cList->head;

    char** res_db = (char**)malloc(sizeof(char*)*DB->cList->size);
    memset(res_db,0,sizeof(res_db));
    int push_lens = 0;
    for (int i = 0; i < DB->cList->size; ++i) {
        if (strlen(table_list->name)>push_lens){
            push_lens = strlen(table_list->name);
        }
        res_db[i] = str_copy(res_db[i],table_list->name);
        table_list = table_list->next;
    }
    char* result = NULL;
    char* head = spell_char('*',push_lens+4);
    head = str_merge(head,"\n");
    result = str_copy(result,head);
    for (int i = 0; i < DB->cList->size; ++i) {
        char* start = "* ";
        start = str_merge(start,res_db[i]);
        int cloum_s = push_lens-strlen(res_db[i]);
        int space_s = 1;
        char* space = spell_char(' ',space_s+cloum_s);
        start = str_merge(start,space);
        start = str_merge(start,"*\n");
        start = str_merge(start,head);
        result = str_merge(result,start);
    }

    return result;





}



char*show_database_panle(){
    if ( vfsTreeRoot->root->cList == NULL){
        return "This is empty\n";
    }
    childList* p = vfsTreeRoot->root->cList;

    vfsNode* phead = p->head;
    char** res_db = (char**)malloc(sizeof(char*)*p->size);
    memset(res_db,0,sizeof(res_db));
    int push_lens = 0;

    for (int i = 0; i < p->size; ++i) {
        cout<<"=>"<<phead->name<<endl;
        if (strlen(phead->name)>push_lens){
            push_lens = strlen(phead->name);
        }
        res_db[i] = str_copy(res_db[i],phead->name);
       phead = phead->next;
    }
    char* result = NULL;

    char* head = spell_char('*',push_lens+4);
    head = str_merge(head,"\n");
    result = str_copy(result,head);

    for (int i = 0; i < p->size; ++i) {
        char* start = "* ";
        start = str_merge(start,res_db[i]);
        int cloum_s = push_lens-strlen(res_db[i]);
        int space_s = 1;
        char* space = spell_char(' ',space_s+cloum_s);
        start = str_merge(start,space);
        start = str_merge(start,"*\n");
        start = str_merge(start,head);
        result = str_merge(result,start);
    }

    return result;
    
}




//销毁链表
void  deleteList(ChildList *list)
{
   VfsNode *temp;
   if (list == NULL || list->size ==0)
   {
      // return IFalse;
   }
   temp=list->head;
   while (temp)
   {
       list->head=list->head->next;
       temp->next=NULL;
       deleteNode(temp);
       temp=list->head;
   }
   list->tail=NULL;
   free(list);
   list = NULL;


}

//初始化树节点
VfsTree * InitRootNode()
{
    VfsTree* newTree = (VfsTree *)malloc(sizeof(VfsTree));
    memset(newTree,0, sizeof(VfsTree));
    VfsNode *root=createNode(0,"root",0,NULL,NULL,NULL);
    if (newTree == NULL || root == NULL)
    {
        return NULL;
    }
    newTree->root =root;

    vfsTreeRoot=newTree;
    return newTree;
}

//添加数据库信息
IBool addVfsTreeNode(VfsNode *parentNode,VfsNode* childNode)
{
    if (parentNode == NULL || childNode == NULL)
    {
        return IFalse;
    }

    if (parentNode->cList == NULL)
    {
        parentNode->cList = InitHeadNode();
        addNode(parentNode->cList,childNode);
        childNode->parentNode = parentNode;
    }
    else
    {
        addNode(parentNode->cList,childNode);
        childNode->parentNode = parentNode;
    }

    return ITrue;
}
//根据名称查找表 -1 找不到这个表
VfsNode *find_table_by_name(char* tab){
    char*dbname=back_dbname();
    if (dbname == NULL){return NULL;}
    VfsNode *tab_list = findDataBaseByName(dbname);
    VfsNode *ss =findNodeByName(tab_list->cList,tab);
    if (ss == NULL)return NULL;
    return ss;
}




//根据名称查找数据库
VfsNode* findDataBaseByName(char* dbName)
{
    VfsNode *root =vfsTreeRoot->root;
    if (root == NULL || root->cList->size==0)
    {
        return NULL;
    }

   //根据名称查找数据库节点
   VfsNode * dbNode = findNodeByName(root->cList,dbName);

   if (dbNode==NULL)
   {
       return NULL;
   }
    return dbNode;
}

//遍历数据库
char* showDataBase()
{
    VfsNode *root =vfsTreeRoot->root;
    if (root == NULL || root->cList->size==0)
    {
        return NULL;
    }

    char *dbName=foreachList(root->cList);

    if (dbName == NULL)
    {
        return NULL;
    }
    printf("dbAllName=%s\n",dbName);
    return dbName;
}






//遍历表
char* showTables(char* databaseName)
{
    VfsNode *root = vfsTreeRoot->root;
    if (root == NULL || root->cList->size == 0)
    {
        return NULL;
    }

    VfsNode * dbNode = findDataBaseByName(databaseName);
    if (dbNode == NULL)
    {
        return NULL;
    }
    char* tableAllName =  foreachList(dbNode->cList);

    if (tableAllName == NULL)
    {
        return NULL;
    }
    printf("tbAllName=%s\n",tableAllName);
    return tableAllName;
}

//遍历列
char* showColumn(char* databaseName,char* tableName)
{
    VfsNode *root = vfsTreeRoot->root;
    if (root == NULL || root->cList->size == 0)
    {
        return NULL;
    }

    //查找该名称的数据库是否存在
    VfsNode *dbNode = findNodeByName(root->cList,databaseName);
    if (dbNode == NULL)
    {
        return NULL;
    }

    //查找该名称的表是否存在
    VfsNode *tbNode = findNodeByName(dbNode->cList,tableName);
    if (tbNode == NULL)
    {
        return NULL;
    }

    char* column = foreachList(tbNode->cList);

    if (column == NULL)
    {
        return NULL;
    }
    printf("allColumnName=%s\n",column);
    return column;
}


//销毁列节点
void* destroyVfsTree(VfsTree* vfsTree )
{
    free(vfsTree);
    vfsTree->root = NULL;
}

//int main(){
//
//
//    vfsTreeRoot = InitRootNode();
//    VfsNode  * databaseNode = createNode(1,"user",1,NULL,NULL,NULL);
//    VfsNode  * table1Node = createNode(2,"userTable",1,NULL,NULL,NULL);
//    VfsNode  * column1Node = createNode(3,"time|char*",1,NULL,NULL,NULL);
//    VfsNode  * column1Node2 = createNode(3,"user|char*",1,NULL,NULL,NULL);
//    VfsNode  * column1Node3 = createNode(3,"age|int",1,NULL,NULL,NULL);
//    VfsNode  * column1Node4 = createNode(3,"money|float",1,NULL,NULL,NULL);
//
//    addVfsTreeNode(vfsTreeRoot->root,databaseNode);
//
//    addVfsTreeNode(databaseNode,table1Node);
//
//    addVfsTreeNode(table1Node,column1Node);
//    addVfsTreeNode(table1Node,column1Node2);
//    addVfsTreeNode(table1Node,column1Node3);
//    addVfsTreeNode(table1Node,column1Node4);
//
//
//
//    char* allDatabase =  showDataBase();
//    printf("目前库中的数据库:%s\n",allDatabase);
//    free(nameComplete);
//
//    char* allTable = showTables("user");
//    printf("当前数据库下的所有表名称:%s\n",allTable);
//    free(nameComplete);
//
//    char* allColumn = showColumn("user","userTable");
//    printf("当前表下的所有列:%s\n",allColumn);
//    free(nameComplete);
//
//    char *s=foreachList(vfsTreeRoot->root->cList);
//    printf("接收到的返回值%s\n",s);
//}
