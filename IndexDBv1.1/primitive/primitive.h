//
// Created by zy on 2022/4/13.
//

#ifndef INDEXDBV1_1_PRIMITIVE_H
#define INDEXDBV1_1_PRIMITIVE_H

#include "vector"
#include <bitset>
#include "../global_c.h"
using namespace std;
typedef struct Link_Node{

    struct Link_Node *prve;
    struct Link_Node *next;

}Link_Node;

void Init_head(Link_Node *head);

void Link_SwapH(Link_Node *head,Link_Node *Prve_Node,Link_Node *Next_Node);

void Link_SwapT(Link_Node *head,Link_Node *Prve_Node,Link_Node *Next_Node);

void Link_Hadd(Link_Node *head,Link_Node *new_Node);

void Link_Tadd(Link_Node *head,Link_Node *new_Node);

void Link_Del(Link_Node *head,Link_Node *tail);

void Link_AllDel(Link_Node *head);


//TesTraverse测试

void TraverseList(vector<string> list);
void Log_info(string str);
void log_err(string str);
string MergeList(vector<string> list);
//两个相互反转的函数翻转字符串和二进制
string bit_filp_str(vector<bitset<8>> data);
vector<bitset<8>> str_filp_bit(string str);
string bit_filp_strlab(string bstr);
bool req_head_const(char c);



typedef vector<string>(*duty_func)(string res,int colums,int aim,TokenType type);
//
//struct duty_nodes{
//    struct Link_Node list;
//    duty_func handler;
//};

class duty_node{

public:
    struct Link_Node list;

    duty_func handler;

    string res = "";
    int colums;
    int aim;
//    enum TokenType: int;
    TokenType type;
    void init_node(duty_func handlers,string ress,int colum,int aim,TokenType type){

        this->handler = handlers;

        this->res = ress;

        this->colums = colum;

        this->aim = aim;

        this->type = type;
    }
    ~duty_node(){
        Log_info("节点被清理");
    }
};


//函数的底层功能函数
vector<int> StrAnInt(vector<string> strs);
void quickSort(long arr[],string str[],int begin,int end);
void IntquickSortUp(int arr[],string str[],int begin,int end);
void IntquickSortDown(int arr[],string str[],int begin,int end);
vector<int> AscllFile(vector<string> Value);
string SortMax(vector<int> arr,vector<string> rows);
string SortMin(vector<int> arr,vector<string> rows);


//第一层封装
vector<string> SortNum(vector<string> value,vector<string> rows,TokenType type);
vector<string> SortByAscll(vector<string> value,vector<string> rows,TokenType type);
vector<string> SortByInt(vector<string> value,vector<string> rows,TokenType type);
vector<string> SortByTime(vector<long> time,vector<string> rows);

//第二层封装
vector<string> SortOrChange(string res,int colums,int aim,TokenType type);
vector<string> SrceenDatas(string res,int colums,int aim,TokenType type);
vector <string> Set_operation(string res,int colums,int aim,TokenType type);


//srceens.cpp声明


vector<string> Greaters(vector<int> arr,vector<string> rows,int arrsize,int aim);

vector<string> Lesss(vector<int> arr,vector<string> rows,int arrsize,int aim);

vector<string> GreEqus(vector<int> arr,vector<string> rows,int arrsize,int aim);

vector<string> LesEqus(vector<int> arr,vector<string> rows,int arrsize,int aim);

vector<string> Equals(vector<int> arr,vector<string> rows,int arrsize,int aim);


//strfactory字符串处理（分割）

vector<string> split(const string& str,const string& delim);


//Filter过滤数据

vector<string>  FilterByValue(string strdata,int column);
vector<string> FilterColumn(string data);


//Duty责任链主要实现功能
string run_task(Link_Node head);
void duty_register(Link_Node *head,class duty_node *node );
void duty_unregister(Link_Node head,class duty_node node);


//exmple例子实现
void expmple1();
void expmple2();
void expmple3();
void expmple4();


//实现最后的limit操作
vector<string> limit_data(string data,int endnum,int aim,TokenType type);

#endif //INDEXDBV1_1_PRIMITIVE_H
