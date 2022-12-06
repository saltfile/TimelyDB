//
// Created by saltfish on 2022/10/3.
//
#include "database_engine.h"
#include "../grammar/Myall.h"
#define INDEX_PATH "/home/saltfish/indexTSDB"
#define MAX_READLEN 1024



//后期检测文件的功能函数
void chaeck_fun(char *path)
{


    int i;

    struct stat buf;

    char *ptr;

    if(lstat(path,&buf)<0)

    { printf("error"); return; }


    if(S_ISREG(buf.st_mode)) ptr="普通文件";

    else if(S_ISDIR(buf.st_mode)) ptr="目录文件";

    else if(S_ISCHR(buf.st_mode)) ptr="字符特殊文件";

    else if(S_ISBLK(buf.st_mode)) ptr="块特殊文件";

    else if(S_ISFIFO(buf.st_mode)) ptr="管道或FIFO";
    cout<<ptr;
}


void engine_init(int mem_size){

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
//      List("/home/saltfish/indexTSDB/xxx/tname.tsdb");
      //拿到所有数据库


    //这是开启内存环
    initCircularList(mem_size);
    InitRootNode();

      char** databases = find_database();


    //拿到数据库中的所有表
    char *aaa = "tanme.tsdb";
    for (int i = 0; i < get_databse_num(); ++i) {
        cout<<endl<<databases[i]<<endl;
        //数据库地址
        char *base = str_copy(base,INDEX_PATH);
        char *path = str_merge(base,"/");
        path = str_merge(path,databases[i]);


        //初始化第一层的数据库节点
        VfsNode  * databaseNode = createNode(1,databases[i],i+1,NULL,NULL,NULL);
        databaseNode->filepath=(char *)malloc(strlen(path));
        memset(databaseNode->filepath,0,strlen(path));
        databaseNode->filepath = str_copy(databaseNode->filepath,path);
        //文件树加节点:库->表->列
        VfsTree * vfs=createVfsTreeRoot();
        addVfsTreeNode(vfs->root,databaseNode);
        //表信息地址rand()rand()
        char **tbs = find_tables(path);
        int lens = get_tables_num(path);
        for (int j = 0; j < lens; j++) {
            VfsNode  * table1Node = createNode(2,tbs[j],i+1,NULL,NULL,NULL);
            addVfsTreeNode(databaseNode,table1Node);


            char *tables = str_merge("",path);
            tables = str_merge(tables,"/");
            tables = str_merge(tables,tbs[j]);
            tables = str_merge(tables,".tsdb");

            //列信息地址
            char **cums = conlum_apply(tables);

            for (int k = 0; k < get_conlum_size(tables); ++k) {
                VfsNode  * columnNode = createNode(3,cums[k],i+1,NULL,NULL,NULL);
                addVfsTreeNode(table1Node,columnNode);
            }
        }

    }
}



//检测数据库文件中的所有数据库文件夹
/**
 * 搜索一共多少个数据库
 * @return
 */
int get_databse_num(){
    DIR * dp;
    struct dirent *filename;

    dp = opendir(INDEX_PATH);
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
//        cout<<"文件类型"<<(int)filename->d_off<<"   ";
//        printf("filename:%-10s\td_info:%ld\t d_reclen:%us\n",
//               filename->d_name,filename->d_ino,filename->d_reclen);

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
        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,"..")&&!strstr(filename->d_name,".tsdb"))
        res++;
    }
    return res;
}


char** find_database(){
    int size = get_databse_num();
    char **res =  (char**) malloc(size * sizeof(char*));
    memset(res,0,sizeof(res));

    //遍历目录下的文件
    DIR * dp;
    struct dirent *filename;

    dp = opendir(INDEX_PATH);
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

        if (strcmp(filename->d_name,".")&&strcmp(filename->d_name,"..")&&!strstr(filename->d_name,".tsdb")){

            char *tab_path = str_merge("",filename->d_name);
            res[i] = tab_path;
            i++;
        }

    }
    return res;

}
int get_conlum_size(char *conms_path){
    FILE * file = fopen(conms_path,"r");
    char *buff = (char *)malloc(1024);
    memset(buff,0,1024);
    fscanf(file, "%s", buff);
    fclose(file);
    int lens = spilt_size_gar(buff,";");
    return lens;
}


//查到所有列
char **conlum_apply(char* clonms_path){
    FILE * file = fopen(clonms_path,"r");
    char *buff = (char *)malloc(1024);
    memset(buff,0,1024);
    fscanf(file, "%s", buff);
    cout<<buff;
    fclose(file);
    int lens = spilt_size_gar(buff,";");
    char **res = split_gar(buff,";");
    for (int i = 0; i < lens; ++i) {
        res[i] = str_merge(res[i], "|char*");
    }
    return res;

}












