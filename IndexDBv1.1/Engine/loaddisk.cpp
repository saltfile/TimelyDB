//
// Created by mikasa on 2022/1/19.
//

//#include "loaddisk.h"
#include "database_engine.h"
#include "../index/database_index.h"
/**
 * 落盘
 * {@param}load_list 要落盘的链
 *
 *
 *
 * */
void * load_disk_method(head_tuple * load_list){

    while (load_list!=NULL){
        VfsNode * basenode=findDataBaseByName(load_list->databasename);
        int offset=strlen(basenode->filepath);
        char * load_base_path=(char *)malloc(offset);//落盘的文件路径
        VfsNode * tablenode=findNodeByName(basenode->cList,load_list->tablename);
        strcat(load_base_path,basenode->filepath);
        memcpy(load_base_path+offset,tablenode->name,strlen(tablenode->name));
        struct stat statbuf;
        stat(load_base_path,&statbuf);
        int size=statbuf.st_size;
        //为获取文件路径 load_base_path



        tuple_column* column=load_list->fileds;
        tuple_column * column_begin=column;
        char * table_struct;
        char * table_struct_begin;
        int ts_offset=0;
        if (size==0){
            ts_offset+=strlen(column->columnname);
            table_struct=(char *)malloc(ts_offset);
            strcat(table_struct,column->columnname);
            table_struct_begin=table_struct;
        }//如果文件是空的就添加文件的结构

        while (column!=NULL){
        if (table_struct!=NULL&&column!=NULL&&column->columnname!=NULL) {
                int next_offset=strlen(column->columnname);
                memcpy(table_struct+ts_offset,column->columnname,next_offset);
                ts_offset+=next_offset;
                memcpy(table_struct+ts_offset,";",1);
                ts_offset++;
            }
        }
        ofstream file(load_base_path,ios::app);
        file<<table_struct_begin;
        file<<"\n";
//        写入文件结构

        column=column_begin;

        char * input=(char *)malloc(strlen(load_list->fileds->datalist->timestamp));//
        char * input_begin=input;
        long int input_offset=0;
        while (column!=NULL){
            value_tuple * datanode=column->datalist;
            while (datanode!=NULL){

                int timestamp_len=strlen(datanode->timestamp);
                int value_len=strlen((char *)datanode->value);
                memcpy(input+input_offset,datanode->timestamp,timestamp_len);
                input_offset+=timestamp_len;
                memcpy(input+input_offset,";",1);
                input_offset++;
                memcpy(input+input_offset,(char *)datanode->value,value_len);
                input_offset+=value_len;
                memcpy(input+input_offset,"\n",1);
                input_offset++;
                //拼待压缩的数据input和长度input_offset

                char * database_tablename=load_list->databasename;
                strcat(database_tablename,load_list->tablename);
                skip_list * list= find_skiptable(database_tablename);
                data_node * dataNode=find_x_from_skip_list(list,atoi(datanode->timestamp));
                struct stat statbuf;
                stat(load_base_path,&statbuf);
                size=statbuf.st_size;
                dataNode->indexEntry->Offset=size;
                string output;
                snappy::Compress(input_begin,input_offset,&output);
                file<<output;
                dataNode->indexEntry->Size=output.size();
                //数据落盘和为索引提供偏移量和偏移长度

                free(datanode->timestamp);
                free(datanode->value);
                value_tuple *temp=datanode;
                datanode=datanode->next;
                free(temp);

                input=input_begin;
                memset(input,0,input_offset);
                input_offset=0;
            }
            tuple_column * tempcolumn=column;
            column=column->nextcolumn;
//
            free(tempcolumn);
        }
        
        free(input);

        head_tuple * tempheadtuple=load_list;
        load_list=load_list->next;
        free(tempheadtuple);
    }
    exit(0);
}
