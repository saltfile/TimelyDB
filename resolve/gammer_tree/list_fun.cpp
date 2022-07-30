//
// Created by saltfish on 2022/2/20.
//
#include "../Myall.h"

void add_list(list *root,treenode *node){
    list *p = root;

    if(p->tree == NULL){
        p->tree = node;
        return;
    }
        while (p->next){
            p = p->next;
        }
        list *newnode = (struct list*)malloc(sizeof(list));
        newnode->tree = node;
        newnode->next = NULL;
        p->next = newnode;
        newnode->prev = p;
}

void dis_play(list *root){
    list *p = root;
    if (p == NULL){
        log_info("这是空的了");
        return;
    }
    string str = "[";
    while (p->next){
        str +=p->tree->str;
        str += "     ";
        p = p->next;
    }
    str+=p->tree->str;
    str+="]";
    log_info(str);
}


int get_list_size(list *root){
    int res  = 0;
    list *p= root;
    while (p->next){
        res++;
        p=p->next;
    }
    return ++res;
}

treenode *get_list_node(list *root,int len){
    int arrsize = get_list_size(root);

    if(len > arrsize){
        log_erro("超出该链表长度------list_fun.cpp");
        return NULL;
    }else if (len <= 0){
        log_erro("违规下标位置------list_fun.cpp");
        return NULL;
    }
    list *p = root;
    for(int i = 1 ; i < len;i++){
        p = p->next;
    }
    treenode *res = p->tree;
    return res;
}

list *remove_node(list *root,int len){
    int arrsize = get_list_size(root);
    if(len > arrsize){
        log_erro("超出该链表长度无法删除------link.cpp");
        return NULL;
    }else if (len <= 0){
        log_erro("违规下标位置无法删除---link.cpp");
        return NULL;
    }
    list *p = root;
    if(arrsize == 1){
        list *node = p;
        free (node);
        return NULL;
    }
    for(int i = 1 ; i < len;i++){
        p = p->next;
    }
    //尾节点
    if(p->next == nullptr){
        list *node = p->prev;
        list *nodep = p;
        node->next = NULL;
        free (nodep);
        while (node->prev){
            node = node->prev;
        }
        return node;
    } else if(p->prev == nullptr){
        list *node = p->next;
        list *nodep = p;
        node->prev = NULL;
        p = node;
        nodep->next = NULL;
        delete (nodep);
        return node;

    } else{
        list *pnode = p->prev;
        list *pres = p;
        list *nnode = p->next;
        pnode->next = nnode;
        nnode->prev = pnode;
        delete (pres);
        while (pnode->prev){
            pnode = pnode->prev;
        }
        return pnode;
    }
}

//字符串复制
char * str_copy(char *str,char *arr){
    str = (char *)malloc(strlen(arr)+1);
    memset(str,0,strlen(arr)+1);
    for(int i = 0;i < strlen(arr);i++){
        str[i] = arr[i];
    }
    str += '\0';
    return str;
}

char * str_merge(char *str,char * merstr){
    merstr+='\0';
    char * res = (char *)malloc(strlen(str)+strlen(merstr)+1);
    memset(res,0,strlen(str)+strlen(merstr)+1);
    for(int i = 0;i < strlen(str);i++){
        res[i] = str[i];
    }

    for(int i = 0;i < strlen(merstr);i++){
        int j = i;
        char s =  merstr[i];
        res[i+strlen(str)] = s;
    }
    char *p = str;
    if(strlen(str)!=0){
        free(p);
    }
    return res;
}

