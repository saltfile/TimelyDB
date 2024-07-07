//
// Created by saltfish on 2021/10/21.
//

#include <string>
#include <list>
#include <vector>
#include "primitive.h"


using namespace std;

/**
 * TODO:执行函数
 * 执行责任链上的所有功能
 *如果res是""那么就用上面得出的结果继续进行计算
 *
 * */
string run_task(Link_Node head){
    Link_Node *p = (&head)->next;
    vector<string> after;
    vector<string> listp;


//责任链头
    struct duty_node *entry;
    p=(&head)->next;

    while (p->next != NULL){
    //使用偏移量对duty_node做取值
        entry = ((class  duty_node *)((char *)(p)-(unsigned long )(&((duty_node *)0)->list)));
        //如果res是空的那么就用上一个节点得出的答案

        if(entry->type == AND|| entry->type == OR || entry->type == NOT){
            entry->res = MergeList(after)+"^"+MergeList(listp);
        }

        if(entry->res == ""){
           string ress = MergeList(listp);
           entry->res = ress;
        }

        after = listp;
        listp = entry->handler(entry->res,entry->colums,entry->aim,entry->type);
        p = p->next;
    }
    entry = ((class duty_node*)((char *)(p)-(unsigned long )(&((duty_node *)0)->list)));
    if(entry->res == ""){
        string ress = MergeList(listp);
        entry->res = ress;
    }
    vector<string> res = entry->handler(entry->res,entry->colums,entry->aim,entry->type);

    return MergeList(res);
}


/**
 * TODO:做责任链注册新的节点
 * @param node 被添加的新节点 , head 责任链链头结点
 * */

void duty_register(Link_Node *head,class duty_node *node ){
    Link_Hadd(head,&node->list);
    Log_info("注册节点");
}

/**
 * TODO:删除某一个注册的节点
 * @param head :责任链的链头，node:被删除的节点
 *
 * */



void duty_unregister(Link_Node head,class duty_node node){
    Link_Del(&head,&node.list);
    delete(&node);
}



















