//
// Created by saltfish on 2021/10/12.
//


#include <string>
#include <list>
#include <vector>
#include "primitive.h"


using namespace std;

/**
 * @author LC
 * 业务说明：这里是作为过滤器的函数方法，数据库的数据每一条都是以分号做分割
 * 每一条属性都是由逗号做分割，所以过滤器用来过滤数据。（单独拿出一列的数据
 * 集合）或是将每一列信息分开
 * */


/**
 * TODO:单独拿出某一列的数据
 * @param data:数据库某个表的数据 column:需要拿走的列数（从0开始）
 * @return 返回的是拿到的结果集
 * */

vector<string>  FilterByValue(string strdata,int column){
    vector<string> rows = split(strdata,";");
    vector<string> res;
    for(int i = 0;i < rows.size();i++){
        vector<string> columns = split(rows[i],",");
        res.push_back(columns[column]);
    }
    return res;
}

/**
 * TODO:把每一列都分开
 * @param data：数据库某个表的数据
 * @return 拿到每一列的值
 * */

vector<string> FilterColumn(string data){
    vector<string> res = split(data,";");
    return res;
}


