//
// Created by saltfish on 2021/10/17.
//
#include <string>
#include <list>
#include <vector>
#include "primitive.h"


using namespace std;

/**
 * TODO:这里可以将字符串数组变成int方便为下面的排序做准备
 * @param strs:字符串数组
 * @return 转换完成的int数组
 * */
vector<int> StrAnInt(vector<string> strs){
    vector<int> res;

    for(int i = 0;i < strs.size();i++){
        string data = strs[i];
        res.push_back(atoi(data.data()));
    }

    return res;
}


/**
 * TODO:这里是做了快速排序
 * @param arr:做快速排序，str：被排序的数组
 * */
void quickSort(long arr[],string str[],int begin,int end)
{
    if(begin < end)
    {
        long temp = arr[begin];
        string strTemp = str[begin];
        int i = begin;
        int j = end;
        while(i < j)
        {

            while(i<j && arr[j] > temp)
                j--;
            arr[i] = arr[j];
            str[i] = str[j];
            while(i<j && arr[i] <= temp)
                i++;
            arr[j] = arr[i];
            str[j] = str[j];
        }
        arr[i] = temp;
        str[i] = strTemp;
        quickSort(arr,str,begin,i-1);
        quickSort(arr,str,i+1,end);
    }
    else
        return;
}

/**
 * TODO:做升序排序
 * */


void IntquickSortUp(int arr[],string str[],int begin,int end)
{
    if(begin < end)
    {

        int temp = arr[begin];
        string strTemp = str[begin];
        int i = begin;
        int j = end-1;
        while(i < j)
        {

            while(i<j && arr[j] > temp)
                j--;
            arr[i] = arr[j];
            str[i] = str[j];
            while(i<j && arr[i] <= temp)
                i++;
            arr[j] = arr[i];
            str[j] = str[i];
        }
        arr[i] = temp;
        str[i] = strTemp;
        IntquickSortUp(arr,str,begin,i-1);
        IntquickSortUp(arr,str,i+1,end);
    }
    else
        return;
}

/**
 * TODO：这里是做降序
 * */


void IntquickSortDown(int arr[],string str[],int begin,int end){
    IntquickSortUp(arr,str,begin,end);
    int arrs[end];
    string strs[end];
    for(int i =0 ; i < end;i++){
        arrs[i] = arr[(end-1)-i];
        strs[i] = str[(end-1)-i];
    }
    for(int i =0 ; i < end;i++){
        arr[i] = arrs[i];
        str[i] = strs[i];
    }

}

/**
 * TODO:是为了有人会因为名字首字母做排序而做的
 * @param Value：被取首字母的数组
 * @return 被截取的字符串字母ASCLL码
 * */




vector<int> AscllFile(vector<string> Value){
    vector<int> ascllList;
    for(int i = 0;i < Value.size();i++){

        string str = Value[i];
        ascllList.push_back((int)str[0]);
    }

    return ascllList;
}


/**
 * TODO:跟上的排序一样只不过是可以做ascll码排序
 * */




vector<string> SortByAscll(vector<string> value,vector<string> rows,TokenType type){
    vector<int> ascllList = AscllFile(value);

    int arr[ascllList.size()];
    for(int i = 0;i < ascllList.size();i++){
        arr[i] = ascllList[i];
    }

    string str[rows.size()];
    for(int i = 0;i < rows.size();i++){
        str[i] = rows[i];
    }
    switch (type) {
        case Asc : IntquickSortUp(arr,str,0,ascllList.size());break;
        case Desc:IntquickSortDown(arr,str,0,ascllList.size());break;
    }

    vector<string> res;
    for(int i = 0;i < rows.size();i++){
        res.push_back(str[i]);
    }
    return res;
}


/**
 * TODO:跟上的排序一样只不过是可以做整型排序
 * */

vector<string> SortByInt(vector<string> value,vector<string> rows,TokenType type){
    vector<int> vals = StrAnInt(value);
    int arr[vals.size()];
    for(int i = 0;i < vals.size();i++){
        arr[i] = vals[i];
    }
    string str[rows.size()];
    for(int i = 0;i < rows.size();i++){
        str[i] = rows[i];
    }

    switch (type) {
        case Asc:IntquickSortUp(arr,str,0,rows.size());break;
        case Desc:IntquickSortDown(arr,str,0,rows.size());break;
    }
    vector<string> res;
    for(int i = 0;i < rows.size();i++){
        res.push_back(str[i]);
    }
    return res;

}



vector<string> SortByTime(vector<long> time,vector<string> rows){
    long timeList[time.size()];
    for(int i = 0;i < time.size();i++)
        timeList[i] = time[i];

    string rowList[rows.size()];
    for(int i = 0;i < rows.size();i++){
        rowList[i] = rows[i];
    }

    quickSort(timeList,rowList,0,time.size()-1);

    vector<string> res;
    for(int i = 0;i < rows.size();i++){
        res.push_back(rowList[i]);
    }

    return res;
}


/**
 * TODO:找到最大值
 * @param arr:这是用来比最大值 rows：表数据的每一行
 * @return 表数据的最大值
 * */


string SortMax(vector<int> arr,vector<string> rows){
    string res = rows[0];
    int num = arr[0];
    for(int i = 1;i < rows.size();i++){
        if(num < arr[i]){
            res = rows[i];
            num = arr[i];
        }
    }
    return res;
}

/**
 * TODO:找数据表最小值
 * @param arr:这是用来比最小值 rows：表数据的每一行
 * @return 表数据的最小值
 * */


string SortMin(vector<int> arr,vector<string> rows){
    string res = rows[0];
    int num = arr[0];
    for(int i = 1;i < rows.size();i++){
        if(num > arr[i]){
            res = rows[i];
            num = arr[i];
        }
    }
    return res;

}



/**
 * TODO:找数据大小值的一个简单封装
 * @param arr:这是用来比最小值 rows：表数据的每一行
 * @return 表数据的最小值
 * */


vector<string> SortNum(vector<string> value,vector<string> rows,TokenType type){
    string res = "";
    vector<string> reslut;
    vector<int> arr = StrAnInt(value);
    switch (type) {
        case Max:res = SortMax(arr,rows);break;
        case Min:res = SortMin(arr,rows);break;
    }
    reslut.push_back(res);
    return reslut;
}

vector<string> SortS(vector<string> value,vector<string> rows,int num,TokenType type){
    vector<string> res;
    switch (num) {
        case 0: res = SortByInt(value,rows,type);break;
        case 1: res = SortByAscll(value,rows,type);break;
    }
    return res;


}

/**
 *TODO:第二层最后的封装
 *详情看README
 *
 * */



vector<string> SortOrChange(string res,int colums,int aim,TokenType type){
    vector<string> values = FilterByValue(res,colums);
    vector<string> rows = FilterColumn(res);
    vector<string> result;

    switch (type) {
        case Max:
        case Min:result = SortNum(values,rows,type);break;
        case Asc:
        case Desc:result = SortS(values,rows,aim,type);break;
    }

    return result;
}








