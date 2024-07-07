//
// Created by saltfish on 2021/10/12.
//

#include <string>
#include <list>
#include <vector>
#include "primitive.h"


using namespace std;



/**
 * TODO:数据的大于筛选
 * @param arr:是要对比的数据集（单列）rows:是每一列的整体数据 aim:被对比的目标值
 * @return 返回的值是每一列的数据
 * */

vector<string> Greaters(vector<int> arr,vector<string> rows,int arrsize,int aim){
    vector<string> res;
    for(int i =0 ;i < arrsize;i++){
        if(arr[i]>aim) {
            res.push_back(rows[i]);
        }
    }
    return res;
}

/**
 * TODO:数据的小于筛选
 * @param arr:是要对比的数据集（单列）rows:是每一列的整体数据 aim:被对比的目标值
 * @return 返回的值是每一列的数据
 * */


vector<string> Lesss(vector<int> arr,vector<string> rows,int arrsize,int aim){
    vector<string> res;
    for(int i =0 ;i < arrsize;i++){
        if(arr[i]<aim) {
            res.push_back(rows[i]);
        }
    }
    return res;
}


/**
 * TODO:数据的大于等于筛选
 * @param arr:是要对比的数据集（单列）rows:是每一列的整体数据 aim:被对比的目标值
 * @return 返回的值是每一列的数据
 * */

vector<string> GreEqus(vector<int> arr,vector<string> rows,int arrsize,int aim){
    vector<string> res;
    for(int i =0 ;i < arrsize;i++){
        if(arr[i]>=aim) {
            res.push_back(rows[i]);
        }
    }
    return res;
}


/**
 * TODO:数据的小于等于筛选
 * @param arr:是要对比的数据集（单列）rows:是每一列的整体数据 aim:被对比的目标值
 * @return 返回的值是每一列的数据
 * */

vector<string> LesEqus(vector<int> arr,vector<string> rows,int arrsize,int aim){
    vector<string> res;
    for(int i =0 ;i < arrsize;i++){
        if(arr[i]<=aim) {
            res.push_back(rows[i]);
        }
    }
    return res;
}

/**
 * TODO:数据的等于筛选
 * @param arr:是要对比的数据集（单列）rows:是每一列的整体数据 aim:被对比的目标值
 * @return 返回的值是每一列的数据
 * */

vector<string> Equals(vector<int> arr,vector<string> rows,int arrsize,int aim){
    vector<string> res;
    for(int i =0 ;i < arrsize;i++){
        if(arr[i]==aim) {
            res.push_back(rows[i]);
        }
    }
    return res;
}
/**
 * TODO:做了上述的一些简单封装
 *
 *vector<string> value,vector<string> row
 * */
vector<string> SrceenDatas(string res,int colums,int aim,TokenType type){
    vector<string> value = FilterByValue(res,colums);
    vector<string> row = FilterColumn(res);

    vector<int> vals = StrAnInt(value);
    vector<string> rows = row;

    switch (type) {
        case GT:rows = Greaters(vals,rows,row.size(),aim);break;
        case LT:rows = Lesss(vals,rows,row.size(),aim);break;
        case GE:rows = GreEqus(vals,rows,row.size(),aim);break;
        case LE:rows = LesEqus(vals,rows,row.size(),aim);break;
        case EQ:rows = Equals(vals,rows,row.size(),aim);break;
    }

//    string res = "";
//    for(int i = 0;i < rows.size();i++){
//        res+=rows[i];
//        res+=";";
//    }

    return rows;
}

/**
 * TODO:这里是做两边集合的交集
 * @param row1，row2：被求交集的两个数据集
 *
 * */


vector<string> Intersection(vector<string> row1 , vector<string> row2){
    //返回值
    vector<string> res;

    for(int i = 0;i < row1.size();i++){
        string str = row1[i];
        for(int j = 0;j < row2.size();j++){
            string str2 = row2[j];
            if(str.compare(str2) == 0){
                res.push_back(str);
                break;
            }
        }
    }


    return res;
}


/**
 * TODO：做数据集的并集操作
 * @param row1,row2:被做并集的数据集
 * @return 合并完成的结果集
 * */


vector<string> SumSection(vector<string> row1 , vector<string> row2){
    vector<string> res;
    for(int i = 0;i < row1.size();i++){
        res.push_back(row1[i]);
    }

    for(int i = 0;i < row2.size();i++){
        int num;
        string str = row2[i];
        for(int j = 0;j < row1.size();j++){

            if(str.compare(res[j]) == 0){
                break;
            }
            num = j;
        }
        if(num == row1.size()-1){
            res.push_back(str);
        }
    }
    return res;
}

/**
 * TODO:做补集操作
 * @param row1,row2:被操作补集的数据集
 * @return 并集的结果集
 * */

vector<string> Suppsection(vector<string> row1,vector<string> row2){
    vector<string> res;
    vector<int> sub;
    for(int i = 0;i < row1.size();i++){
        res.push_back(row1[i]);
    }

    for(int i = 0;i < row2.size();i++) {
        int num;
        string str = row2[i];
        for (int j = 0; j < row1.size(); j++) {

            if (str.compare(res[j]) == 0) {
                sub.push_back(j);
                break;
            }
        }
    }
    for(int i =0 ;i < sub.size();i++){
        res.erase(res.begin()+sub[i]);
    }
    return res;

}




vector <string> Set_operation(string res,int colums,int aim,TokenType type){
    vector<string> str = split(res,"^");
    string rows1 = str[0];
    string rows2 = str[1];

    vector<string> row1 = FilterColumn(rows1);
    vector<string> row2 = FilterColumn(rows2);

    vector<string> result;
    switch (type) {
        case AND: result = Intersection(row1,row2);break;
        case OR : result = SumSection(row1,row2);break;
        case NOT: result = Suppsection(row1,row2);break;
    }

    return result;
}



/**
 * TODO：实现limit功能
 * @param rows：数据集合;endnum是到第几行
 * */

vector<string> limit_data(string data,int endnum,int aim,TokenType type){
    vector<string> rows = FilterColumn(data);
    vector<string> reslust;
    int startnum = 0;
    int realsize = endnum;
    if(rows.size() < endnum){
        realsize = rows.size();
    }
    for(int i = 0 ;i < realsize;i++){
        reslust.push_back(rows[i]);
            }

    return reslust;
}





