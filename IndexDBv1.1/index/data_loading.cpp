//
// Created by saltfish on 22-12-6.
//
/**
* 此文件为了载入对应表的数据
*/
#include "database_index.h"
#include "../grammar/Myall.h"

//TODO:12-06 理论接口已经清楚，明天完成整个部分

char* string_trans_char(string tmp){
    char *res = (char*) malloc(sizeof(tmp.size())+1);
    memset(res,0,tmp.size()+1);

    strcpy(res,tmp.c_str());

    res[tmp.size()] = 0;
    return res;
}
char * decompress_data(char* str){
    string string1;
    snappy::Uncompress(str, strlen(str),&string1);
    cout<<string1;
    char *res = string_trans_char(string1);
}


//  读文件
void read_test(char* filepath){

    FILE *fp = fopen(filepath, "r");
    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    int flen=ftell(fp); /* 得到文件大小 */
    char* p=(char *)malloc(flen+1); /* 根据文件大小动态分配内存空间 */
    if(p==NULL)
    {
        fclose(fp);
        return;
    }
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
    fread(p,flen,1,fp); /* 一次性读取全部文件内容 */

    p[flen]=0;
    fclose(fp);
    char **chars = split_gar(p,"\n");
    int files = spilt_size_gar(p,"\n");
    for (int i = 1; i < files; ++i) {
        cout<<chars[i]<<endl;
    }

    string string1;
    snappy::Uncompress(chars[1], strlen(chars[1]),&string1);
    cout<<string1;
    char *st = string_trans_char(string1);
    return;
}




int Load_Test(){
//    snappy::Uncompress()
    char* filepath = "/home/saltfish/indexTSDB/com/item";
    read_test(filepath);
    return 0;
};






