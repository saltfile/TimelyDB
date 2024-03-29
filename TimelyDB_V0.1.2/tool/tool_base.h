//
// Created by saltfish on 23-4-17.
//

#ifndef TIMELYDB_V0_1_2_TOOL_BASE_H
#define TIMELYDB_V0_1_2_TOOL_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include<map>
#include <csetjmp>

using namespace std;

enum data_type {
    BYTE = 0,
    INT = 1,
    FLOAT = 2,
    DOUBLE = 3,
    DECIMAL = 4,
    VARCHAR = 5,
    TEXT = 5,
    TIMESTAMP = 8,
    VOID = 9
};

#define NONE         "\033[m";
#define LIGHT_BLUE   "\033[1;34m"
#define LIGHT_PURPLE "\033[1;35m"
#define LIGHT_RED "\033[1;31m"
//基本的list宏
#define LIST_LAST(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_FOREACH(pos, head) \
    for (pos =(head) ;pos->next ;pos = pos->next)

#define LIST_FOR(pos, head, idx) \
    pos = head;                \
    for(int i = 0;i < idx;i++){\
    pos = pos->next;           \
    }                            \
pos = pos->next; \


#define LIST_FOR_RING(pos, head, idx) \
    pos = head;                \
    for(int i = 0;i < idx;i++){\
    pos = pos->next;           \
    }                            \
//pos = pos->next; \



#define LIST_ADD_TAIL(head, pos, node) \
    for (pos =(head) ;pos->next ;pos = pos->next);            \
    pos->next = node;                  \
    node->prev = pos;                  \


#define CONTAINER_OF(head, type, pos) \
   head = ((typeof(type) *)((char *)(pos)-(unsigned long )(&((typeof(type)*)0)->list)));

#define CREATE_BASE_LIST(ptr) \
ptr = (tylist_node*) malloc(sizeof (tylist_node));\
memset(ptr,0,sizeof(ptr))


#define CREATE_COLLECTION(ptr) \
ptr = (collection *) malloc(sizeof(collection)); \
memset(ptr, 0, sizeof(ptr));

#define CREATE_ARRLIST(ptr) \
ptr = (arr_list *)malloc(sizeof(arr_list)); \
memset(ptr,0,sizeof(arr_list));             \
ptr->arr_list(); \

#define SAFE_FREE(p) \
    if (NULL != (p)) { \
        free((p)); \
        (p) = NULL;\
    }\

typedef struct tylist_node {
    tylist_node *prev;
    tylist_node *next;
} tylist_node;


//QUEUE
struct collection {
public:
    void *data;
    struct tylist_node list;

    void set_data(void *data) {
        this->data = data;
    }

    void *get_data() {
        return this->data;
    }
};

struct arr_list {
private:
    void free_list_node(collection *_col) {
        try {
            void *p = _col->data;
//            memset(p,0, sizeof(p));
//            SAFE_FREE(p);
            _col->data = NULL;
            SAFE_FREE(_col);
            _col = NULL;
        } catch (exception e) {
            printf(LIGHT_RED"异常： 自定义链表内存释放失败\n\033[m");
        }
    }

public:
    int length = 0;
    int aim = -1;
    collection *collect = NULL;

    void initialization() {
        this->collect = CREATE_COLLECTION(this->collect);
    }

    void arr_list_add(void *data) {
        //1.拿到当前list句柄
        collection *ptr = this->collect;
        //2.初始化新节点
        collection *new_node = NULL;
        CREATE_COLLECTION(new_node);
        //3.赋值NULL
        new_node->list.next = NULL;
        new_node->list.prev = NULL;
        new_node->set_data(data);
        //4.添加到末尾
        tylist_node *temp = NULL;

        for (temp = (&ptr->list); temp->next; temp = temp->next);
        temp->next = &new_node->list;
        new_node->list.prev = temp;
//        LIST_ADD_TAIL(&ptr->list, temp, &new_node->list);
        //5.长度加一
        this->length++;
    }


    void *get(int idx) {
        //1.拿到句柄
        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;

        //2.校验参数是否合法
        if (idx < 0 || idx >= length)
            return NULL;

        //3.拿到对应的下标
        LIST_FOR(p, ptr, idx);

        //4.置换出来返回结果
        collection *res = NULL;
        CONTAINER_OF(res, collection, p);
        return res->data;
    }

    void arr_list_remove(int idx) {
        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;

        if (idx > length - 1 || idx < 0)
            return;
        if (idx == 0) {
            tylist_node *tmp = ptr->next;
            tylist_node *p_tmp_next = ptr->next->next;
            p_tmp_next->prev = ptr;
            ptr->next = tmp->next;

            tmp->next = NULL;
            tmp->prev = NULL;
            collection *_rm = NULL;
            CONTAINER_OF(_rm, collection, tmp);
            free_list_node(_rm);
        } else if (idx == length - 1) {

            LIST_LAST(p, ptr);
            tylist_node *p_tmp_prev = p->prev;
            p_tmp_prev->next = NULL;
            p->prev = NULL;
            p->next = NULL;
            collection *_rm = NULL;
            CONTAINER_OF(_rm, collection, p);
            free_list_node(_rm);
        } else {

            LIST_FOR(p, ptr, idx - 1);
            tylist_node *tmp = p->next;
            tylist_node *p_tmp_next = p->next->next;
            p_tmp_next->prev = p;
            p->next = p_tmp_next;

            tmp->next = NULL;
            tmp->prev = NULL;
            collection *_rm = NULL;
            CONTAINER_OF(_rm, collection, tmp);
            free_list_node(_rm);
        }
        length--;

    }

};


typedef struct integer {
    int val;

    integer(int v) : val(v) {}

    int operator=(integer &order) {
        return order.val;
    }

    void operator=(int i) {
        val = i;
    }
};

typedef struct varchar {
    int size = 255;
    char *val = (char *) malloc(sizeof(char) * size);

    void operator=(char *str) {
        if (size > strlen(str)) {
            memset(val, 0, size);
            strcpy(val, str);
        }
    }


};

typedef struct boolbean {
    bool val;

    void operator=(bool data) {
        val = data;
    }

};

typedef struct doubles {
    double val;

    void operator=(double data) {
        val = data;
    }
};

typedef struct time_tramp {
    time_t timestramp;
    long time_val;

    void operator=(time_t t) {
        time_val = (long) t;
        timestramp = t;
    }
};


struct ring_list {
private:
    void free_list_node(collection *_col) {
        try {
            void *p = _col->data;
//            memset(p,0, sizeof(p));
//            SAFE_FREE(p);
            _col->data = NULL;
            SAFE_FREE(_col);
            _col = NULL;
        } catch (exception e) {
            printf(LIGHT_RED"异常： 自定义链表内存释放失败\n\033[m");
        }
    }


public:
    int length = 0;
    int size = 0;
    collection *collect = NULL;
    enum data_type type;

    void initialization(int nul, enum data_type type) {
        collection *ptr = CREATE_COLLECTION(ptr);
        tylist_node *start = &ptr->list;
        tylist_node *tail = &ptr->list;

        for (int i = 0; i < nul - 1; ++i) {
            collection *new_node = NULL;
            CREATE_COLLECTION(new_node);
            //3.赋值NULL
            new_node->list.next = NULL;
            new_node->list.prev = NULL;
            tail->next = &new_node->list;
            tail = tail->next;
        }

        tail->next = start;

        this->collect = ptr;

        this->size = nul;

        this->type = type;
    }

    void add(int i) {
        //1.拿到句柄
        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;
        this->length = this->length % size;
        int len = this->length;
        //3.拿到对应的下标
//        LIST_FOR_RING(p, ptr, len);

        p = ptr;
        for (int i = 0; i < this->length; i++) {
            p = p->next;
        }
        //4.置换出来返回结果
        collection *res = NULL;
        CONTAINER_OF(res, collection, p);
        integer *aaa = NULL;
        if (res->data != NULL){
           aaa= (integer*)res->data;
        }
        integer *pi = (integer *) malloc(sizeof(integer));
        memset(pi, 0, sizeof(integer));
        pi->val = i;
        res->data = (void *) pi;

        this->length++;
//        this->length =

    }

    void add(varchar *s) {
        if (this->type != VARCHAR)return;

        if (this->length + 1 > size) {
            this->length = 0;
        }

        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;

        LIST_FOR_RING(p, ptr, length);
        collection *res = NULL;
        CONTAINER_OF(res, collection, p);

        if (res->data != NULL) {
            res->data = NULL;
        }

        res->data = (void *) s;
        length++;
    }

    int get(int idx) {
        //1.拿到句柄
        tylist_node *ptr = &this->collect->list;
        tylist_node *p = NULL;

        //2.校验参数是否合法
        if (idx < -1 || idx > this->size)
            return NULL;

        p = ptr;
        for (int i = 0; i < idx; i++) {
            p = p->next;
        }

        //4.置换出来返回结果
        collection *res = NULL;
        CONTAINER_OF(res, collection, p);
        integer *d = (integer *) res->data;
        return d->val;
    }


    string to_string() {
        //1.拿到句柄
        tylist_node *ptr = &this->collect->list;

        string result = "[ ";

        for (int i = 0; i < size; i++) {
            ptr = ptr->next;
            collection *res = NULL;
            CONTAINER_OF(res, collection, ptr);
            integer *o = (integer *) res->data;
            result += std::to_string(o->val);
        }

        return result;

    }

    void add(doubles *d) {
    }

    void add(time_tramp *t) {

    }


    void destroy() {

    }
};


int get_databse_num();

char **find_database();

int get_tables_num(char *database_path);

char **find_tables(char *database_path);

void init_file_system();

//文件系统初期测试存储文件
void file_test();

/**
 * 创建目录&文件接口
 * @return 统一规则
 * 目录    已创建：1、目录已存在：0、创建失败：-1
 */
int create_mkdir(char *path);

FILE *create_file(char *path);

bool file_is_exist(char *path);

int create_database(char *base_name);

int create_table(char *database, char *table);

int file_write(char *base_key, char *file_name, char *data);

char *file_read(char *base_name, char *file_name);

/**
 * 支持数据库的函数
 * @return
 */
vector<string> get_any_base();

vector<string> get_any_table(string base_key);



//字符串工具类

//字符串赋值
char *str_copy(char *str1, char *str2);

//字符串合并
char *str_marge(char *str1, char *str2);

//字符穿拆分
int str_spilt_size(char *a, char *b);

char **str_spilt(char *str, char *dent);

char *str_to_int(int num, char *str, int radix);

//释放字符串函数
char *free_str(char *str);


#endif //TIMELYDB_V0_1_2_TOOL_BASE_H
