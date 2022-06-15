////
//// Created by mikasa on 2022/4/15.
////
//
//#ifndef G_TEST_VFSTREE_H
//#define G_TEST_VFSTREE_H
//typedef  enum{
//    IFalse=0,ITrue=1,Ierror=-1
//}IBool;
//
////文件树节点
//typedef struct vfsNode{
//    int level;         //节点等级
//    char* name;        //name
//    int flag;          //标志位
//    struct vfsNode *parentNode; //父节点
//    struct vfsNode *next;       //下一个节点的位置
//    struct childList *cList;    //孩子链表
//    char * filepath;
//}VfsNode;
//
////文件树
//typedef struct vfsTree{
//    VfsNode *root;
//    struct vfsTree * next;
//}VfsTree;
////文件树节点中的子链表
//typedef struct childList{
//    int size;
//    VfsNode *head;
//    VfsNode *tail;
//}ChildList;
//
////初始化孩子链表头节点
//ChildList * InitHeadNode();
//
////生成节点
//VfsNode * createNode(int level,char *name,int flag,VfsNode* next,VfsNode *parentNode,ChildList * cList);
//
////遍历链表查看是否有相同的名字  -1表示错误
//IBool   foreachListByName(ChildList *list ,char *name);
//
////查找节点
//VfsNode *findNodeByName(ChildList *list,char* name);
//
////遍历子链表
//char *  foreachList(ChildList* list);
//
////销毁节点
//void * deleteNode(VfsNode* node);
//
////删除节点
//IBool removeNode(ChildList *list,char* name);
//
////销毁链表
//void  deleteList(ChildList *list);
//
////初始化VfsTree
//VfsTree * InitRootNode();
//
////遍历数据库
//char* showDataBase();
//
////添加数据库信息
//IBool addVfsTreeNode(VfsNode *parentNode,VfsNode* childNode);
//
////遍历表
//char* showTables(char* databaseName);
//
////遍历列
//char* showColumn(char* databaseName,char* tableName);
//
////销毁列节点
//void* destroyVfsTree(VfsTree* vfsTree );
//
//VfsTree * createVfsTreeRoot();
//
//
//VfsNode* findDataBaseByName(char* dbName);
//extern VfsTree *vfsTreeRoot;
//extern VfsNode *root;
//#endif //G_TEST_VFSTREE_H
