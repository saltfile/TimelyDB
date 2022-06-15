/**
 * @author LC
 * @date Created by saltfish on 2021/9/28.
 * */


#include "primitive.h"



/**
 * TODO:初始化
 * @param head ：被初始化的节点
 * */
void Init_head(Link_Node *head){

    head = (Link_Node *)malloc(sizeof(Link_Node));
    head->next = NULL;
    head->prve = NULL;

}

/**
 * TODO:责任链的功能交换，每一个节点代表一个功能
 * @param head:前节点
 * @param Prve_Node:后节点
 * @param Next_Node：中节点
 * */
void Link_SwapH(Link_Node *head,Link_Node *Prve_Node,Link_Node *Next_Node){
    //next在head后面
    head->next = Next_Node;
    Next_Node->prve = head;
    //prve在next后面
    Next_Node->next = Prve_Node;
    Prve_Node->prve = Next_Node;
}

/**
 * TODO:跟上面函数相反的一种交换
 * @param head:前节点
 * @param Prve_Node:后面的节点
 * @param Next_Node:中间的节点
 * */
void Link_SwapT(Link_Node *head,Link_Node *Prve_Node,Link_Node *Next_Node){

    head->next = Prve_Node;
    Prve_Node->prve = head;

    Prve_Node->next = Next_Node;
    Next_Node->prve = Prve_Node;

}

/**
 * TODO:正常尾插法单个节点
 * @param head:当前节点
 * @param new_Node:在head后面的节点
 * */
void Link_Hadd(Link_Node *head,Link_Node *new_Node){
    Link_Node *p = head;
    while (p->next != NULL){
        p = p->next;
    }
    p->next = new_Node;
    new_Node->prve = p;
    new_Node->next = NULL;

}

/**
 * TODO:正常头插法插入单个节点
 * @param head:当前节点
 * @param new_Node:在head前面的节点
 * */

void Link_Tadd(Link_Node *head,Link_Node *new_Node){

    head->prve = new_Node;
    new_Node->next = head;

}

/**
 * TODO:删除两个节点中间的节点(删除单个或多个节点)
 * @param head:前节点
 * @param tail：后节点
 * */
void Link_Del(Link_Node *head,Link_Node *tail){
    //被删掉的中间节点
    Link_Node *p = head->next;

    head->next = tail;
    tail->prve = head;
    //放掉那里的节点内存
    free(p);

}
/**
 * TODO:全表删除
 * @param head：头结点
 * */
void Link_AllDel(Link_Node *head){
    Link_Node *p = head;
    while (p->next != NULL){
        p = p->next;
        free(p->prve);
    }

}













