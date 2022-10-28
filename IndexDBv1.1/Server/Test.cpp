#include "ser_drive.h"
#include "../grammar/Myall.h"
#include "../index/database_index.h"
#include "ser_drive.h"

int test_ser() {
    engine_init(1000);
//        epollser_start(8994);
    char *inserts = "insert into item(age,name)values(45,xiaoming)";
    char *insert1 = "insert into item(age,name)values(43,aaaaa)";

    cout<<use_handle("use com");
    scan_word* iword = scanWordInit();
    sqlsacnner(iword,inserts);
    treenode *iroot = check_tree(iword);
    memte_insert(iroot);
    scan_word* wors2 = scanWordInit();
    sqlsacnner(wors2,insert1);
    treenode *our = check_tree(wors2);
    memte_insert(our);

//
    int a = 1;
    scanf("%d",&a);
//    cout<<show_DB_handle("show databases")<<endl;
//    cout<<create_handle("create database xxxs")<<endl;
//    cout<<show_DB_handle("show databases")<<endl;
//    cout<<use_handle("use com");
//    cout<<create_handle("create table xxx(age int)");
//    cout<<show_Table_handle("show tables");


//    cout<<create_handle("create table hgf(age int,name varchar(25),shengao float)")<<endl;


//    ser_start(8686);

//packge *pa = (packge *)malloc(sizeof(packge));
//
//pa->pack_head = 192;
//pa->result = "sucssfly of creat databases : xxxx";






//    initCircularList(1000);
//    InitRootNode();
//
//    VfsNode  * databaseNode = createNode(1,"xxx",1,NULL,NULL,NULL);
//    databaseNode->filepath=(char *)malloc(sizeof("/home/saltfish/indexTSDB/xxx/"));
//    databaseNode->filepath="/home/saltfish/indexTSDB/xxx/";
//    VfsNode  * table1Node = createNode(2,"tname",1,NULL,NULL,NULL);
//    VfsNode  * column1Node = createNode(3,"age|char*",1,NULL,NULL,NULL);
//    VfsNode  * column1Node2 = createNode(3,"name|char*",1,NULL,NULL,NULL);
//
//    VfsTree * vfs=createVfsTreeRoot();
//    addVfsTreeNode(vfs->root,databaseNode);
//    addVfsTreeNode(databaseNode,table1Node);
//    addVfsTreeNode(table1Node,column1Node);
//    addVfsTreeNode(table1Node,column1Node2);

//    char *use = "use xxx";
//    scan_word *uword = scanWordInit();
//    sqlsacnner(uword,use);
//    treenode *uroot = check_tree(uword);
//    use_memte(uroot);

//
//    char *c_t = "create table tname(age int,name varchar(25),shengao float)";
//    scan_word *tword = scanWordInit();
//    sqlsacnner(tword,c_t);
//    treenode *troot = check_tree(tword);
//    create_memte_tb(troot);








//    char *inserts = "insert into tname(age,name)values(45,xiaoming)";
//
//    scan_word* iword = scanWordInit();
//    sqlsacnner(iword,inserts);
//    treenode *iroot = check_tree(iword);
//    memte_insert(iroot);
//
//    //z最后落盘
//    manager_writedisk(1);
//    scanf("%d");



//u8 a = -113;
//printf("%d ",a);

//    u8 up[4] = {0,0,0,28};
//    int a = toInt(up);
//    cout<<a;

//printf("%d",RESP_REQUIRE);
//u8 cp[12] = {129,0,33,0,0,0,0,12,97,115,102,10};
//packge *packge1 = (packge *)malloc(sizeof(packge));
//packge1->create_package("asf",RESP_REQUIRE);
//cout<<endl;
//for(int i = 0;i < packge1->alllen;i++){
//    printf("%d   ",packge1->all[i]);
//}





//u8 *arr = lab_fun();
//for(int i = 0;i < 4;i++){
//    printf("%d  ",arr[i]);
//}
//u8 *all = to_Char("asdafdsgfdgdh");
//for(int i = 0;i < size_of_buf(all);i++){
//    printf("%d    ",all[i]);
//}



//
    return 0;
}
