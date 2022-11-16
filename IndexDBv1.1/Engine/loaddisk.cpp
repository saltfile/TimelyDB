//
// Created by mikasa on 2022/1/19.
//

//#include "loaddisk.h"
#include "database_engine.h"
#include "../grammar/Myall.h"
#include "../index/database_index.h"
/**
 * 落盘
 * {@param}load_list 要落盘的链
 *
 *
 *
 * */


 int get_load_size(load_lists *ptr){
    load_node *p = ptr->head;
    int res = 0;
    while (p){
        res++;
        p = p->next;
    }
    return res;
}
void add_value_node(value_tuple *root,value_tuple *new_node){
    value_tuple *p = root;
    if (p->timestamp == NULL){
//         p = malloc_tuple();

        p->timestamp = str_copy(p->timestamp,new_node->timestamp);
        p->value = str_copy(p->value,new_node->value);
        return;
    }
    while (p->next){
        p = p->next;
    }
    p->next = new_node;
}

void add_value(value_tuple *root,char *timestamp,char* value){
     int st_len = strlen(timestamp);
     value_tuple *p = root;
     if (p->timestamp == NULL){
//         p = malloc_tuple();

         p->timestamp = str_copy(p->timestamp,timestamp);
         p->value = str_copy(p->value,value);
         return;
     }
     while (p->next){
         p = p->next;
     }
     value_tuple *n_node = malloc_tuple();
     n_node->value = str_copy(n_node->value,value);
     n_node->timestamp = str_copy(n_node->timestamp,timestamp);
     p->next = n_node;
 }


void * load_disk_method(head_tuple * load_list){
    head_tuple * p =load_list;
    while (p!=NULL){
        VfsNode * basenode=findDataBaseByName(p->databasename);
        if (basenode == NULL){
            p = p->next;
            continue;
        }
        int offset=strlen(basenode->filepath);
        char * load_base_path=NULL;//落盘的文件路径
        VfsNode * tablenode=findNodeByName(basenode->cList,p->tablename);
        //注:修改
        load_base_path = str_copy(load_base_path,basenode->filepath);
        load_base_path = str_merge(load_base_path,"/");
//        strcat(load_base_path,basenode->filepath);
        memcpy(load_base_path+offset+1,tablenode->name,strlen(tablenode->name));
        struct stat statbuf;
        stat(load_base_path,&statbuf);
        int size=statbuf.st_size;
        //为获取文件路径 load_base_path


        FILE *write=fopen(load_base_path,"a");
        tuple_column* column=p->fileds;
        tuple_column * column_begin=column;
        char * table_struct;
        char * table_struct_begin;
        int ts_offset=0;
        if (size==0){
            char *head_con = "timestamp;";
//            ts_offset+=strlen(head_con);
            table_struct=(char *)malloc(ts_offset);
//            strcat(table_struct,head_con);
            table_struct_begin=table_struct;


        while (column!=NULL){

        if (table_struct!=NULL&&column!=NULL&&column->columnname!=NULL) {
                int next_offset=strlen(column->columnname);
                memcpy(table_struct+ts_offset,column->columnname,next_offset);
                ts_offset+=next_offset;
                memcpy(table_struct+ts_offset,";",1);
                ts_offset++;
            }
        column = column->nextcolumn;
        }


        fwrite(table_struct_begin,strlen(table_struct_begin),1,write);
        fwrite("\n",1,1,write);
        fflush(write);
        }//如果文件是空的就添加文件的结构
//        ofstream file(load_base_path,ios::app);
//        file<<table_struct_begin;
//        file<<"\n";
//        写入文件结构

        column=column_begin;

        char * input=(char *)malloc(strlen(p->fileds->datalist->timestamp));//
        char * input_begin=input;
        long int input_offset=0;
        load_lists *lists = (load_lists *)malloc(sizeof(load_lists));
        memset(lists,0,sizeof(load_lists));

        //重构,结构不对
        while (column!=NULL){
            value_tuple * datanode=column->datalist;

            if (lists->tail == NULL){
                load_node *new_node = (load_node*)malloc(sizeof(load_node));
                memset(new_node,0,sizeof(load_node));
                new_node->data = column->datalist;
                lists->next = new_node;
                lists->tail = lists->next;
                lists->head = lists->next;
            } else{
                load_node *new_node = (load_node*)malloc(sizeof(load_node));
                memset(new_node,0,sizeof(load_node));
                new_node->data = column->datalist;
                lists->tail->next = new_node;
                lists->tail = lists->tail->next;
            }
            tuple_column * tempcolumn=column;
            column=column->nextcolumn;

            free(tempcolumn);
        }
        value_tuple *datan = malloc_tuple();
        bool states = false;
        while (1){

            if (states)break;
            load_node *hs = lists->head;


            while (hs){
                if (hs->data == NULL){
                    states = true;
                    break;
                }
               add_value(datan, hs->data->timestamp,hs->data->value);
                hs->data = hs->data->next;
                hs = hs->next;
            }
        }











            while (datan!=NULL){

                int timestamp_len=strlen(datan->timestamp);
                int value_len=strlen((char *)datan->value);
                memcpy(input+input_offset,datan->timestamp,timestamp_len);
                input_offset+=timestamp_len;
                memcpy(input+input_offset,";",1);
                input_offset++;
                memcpy(input+input_offset,(char *)datan->value,value_len);
                input_offset+=value_len;
                memcpy(input+input_offset,"\n",1);
                input_offset++;
                //拼待压缩的数据input和长度input_offset

                char * database_tablename=p->databasename;
//                strcat(database_tablename,p->tablename);
//                skip_list * list= find_skiptable(database_tablename);
//                data_node * dataNode=find_x_from_skip_list(list,atoi(datanode->timestamp));
                struct stat statbuf;
                stat(load_base_path,&statbuf);
                size=statbuf.st_size;
//                dataNode->indexEntry->Offset=size;
                string output;
                snappy::Compress(input_begin,input_offset,&output);
                //TODO:09-29 table_struct_begin 列名重复      解决
                fwrite(output.data(),output.length(),1,write);
                fflush(write);
//                file<<output;

//                dataNode->indexEntry->Size=output.size();
                //数据落盘和为索引提供偏移量和偏移长度
//                char *p = datanode->timestamp;
//                datanode->timestamp = NULL;
//                free(p);
//                if (datanode->value)
//                free(datanode->value);
//                value_tuple *temp=datanode;
                datan=datan->next;
//                free(temp);

                input=input_begin;
                memset(input,0,input_offset);
                input_offset=0;
            }




        free(input);
        //TODO:10-01 这里的内存处理需要释放
        head_tuple * tempheadtuple=p;
        p=p->next;
        free(tempheadtuple);
        fclose(write);
    }

    pthread_exit(0);
}
