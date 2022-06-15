//
// Created by saltfish on 2021/10/12.
//

#include <ctime>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "primitive.h"
#include <bitset>
#include <algorithm>

using namespace std;



/**
 * TODO:遍历某个列表，最后输出一遍列表内容（目前都是字符串我就不用泛型了）
 * @param list：被遍历的链表
 * */

void TraverseList(vector<string> list){
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    for(int i = 0;i < list.size();i++){
        cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  That list message : "<<list[i]<<endl;
    }
}

/**
 * TODO:一个可以输出时间和类型的日志（测试：写着玩的）
 * @param str：要输出的字符串
 * */
void Log_info(string str){
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
        cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
            <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  LOG——INFO [-,,,] ---  : "<<str<<endl;
}


bool req_head_const(char c){






    return false;
}









void log_err(string str){
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  LOG——ERROR [-!!!] ---  : "<<str<<endl;
}



/**
 * TODO:将数组里面的数据合并起来
 * @param list:被合并的数组
 * @return 合并完成的结果
 * */

string MergeList(vector<string> list){
    string res = "";
    for(int i =0 ;i < list.size();i++){
        res+= list[i];
        res+= ";";
    }
    return res;

}

/**
 * TODO:可以讲bit转为字符串
 * @param data 所有字符串的数据
 * @return转换完的字符串
 * */


string bit_filp_str(vector<bitset<8>> data) {
    string str = "";
    string bit_str = "";

    for(int i = 0;i < data.size();i++){
        bit_str+=data[i].to_string();
    }
    //每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for (int i = 0; i < bit_str.size(); i += 8) {
        sum = 0;
        for (int j = 0; j < 8; j++){
            if (bit_str[i + j] == '1')
                sum = sum * 2 + 1;
            else
                sum = sum * 2;
        }
        str = str + char(sum);
    }
    return str;

}

/**
 * TODO:将一字符串转为单个bit<8>（一字节）的值，数据包做解析
 * @param str 要转成的字符串
 * @return 返回包的解析
 */
vector<bitset<8>> str_filp_bit(string str)
{
    vector<bitset<8>> bit_list;
    bitset<1024> bstr ;
    cout<<str.size()<<endl;

    for(int i=0;i<str.size();i++)
    {
//        cout<<i<<"次"<<endl;
        bitset<8> bits =  bitset<8>(str[i]);
//        cout<<str[i]<<endl;
        for(int j = 0;j<8;j++)
        {
            bstr[i*8+j] = bits[7-j];
        }
    }
    string s = bstr.to_string();
    //添加一个翻转操作
    reverse(begin(s),end(s));

    for(int i = 0;i < str.size();i++){
        bitset<8> str_lone;
        for(int j =0;j < 8;j++){
           str_lone[j] = bstr[i*8+j];
        }
        bit_list.push_back(str_lone);
    }
    return bit_list;
}

string bit_filp_strlab(string bstr){
    string str="";
    //每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for(int i=0;i<bstr.size();i+=8)
    {
        sum=0;
        for(int j=0;j<8;j++)
            if(bstr[i+j] == '1')
                sum = sum*2+1;
            else
                sum = sum*2;
        str =str+char(sum);
    }
    return str;

}



















