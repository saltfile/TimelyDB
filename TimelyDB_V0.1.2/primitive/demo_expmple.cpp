//
// Created by saltfish on 2021/10/24.
//

#include <string>
#include <list>
#include <vector>
#include "primitive.h"


/**
 * 声明： 这个cpp内写我的函数和功能是如何使用，类似于功能实例
 * 格式为   创建头节点---->初始化责任链节点--->最后将所有节
 * 点运行，返回一个string的最终结果
 * */

//全局变量 这是模拟的数据表属性是0时间,1姓名，2年龄，3编号
string res = "1213331145001,xxx,35,2;1212331141002,sam,12,1;1212331145004,AAA,39,3;1212331145003,BBB,31,4;1212331145004,CCC,20,5;1212331145004,WWW,12,6;1213331145001,xxx,35,2;1212331141002,sam,12,1;1212331145004,AAA,45,7;1212331145003,BBB,31,8;1212331145006,wert,35,9;1212331145018,fdh,81,10;";

string res2 = "";

/**
 * TODO：步骤->先查询大于年龄大于13的数据并且已第四列(从0数起到3)为基准进行升序排序
 * select * from xxxtable where age > 13 order by asc
 * */

void expmple1(){
    Link_Node *head = new(Link_Node);
    //先实现查找大于13
    duty_node *srceen_datas = new(class duty_node);
    srceen_datas->init_node(SrceenDatas,res,2,13,GT);
    duty_register(head,srceen_datas);
    //升序排序
    duty_node *sort_data = new (class duty_node);
    sort_data->init_node(SortOrChange,"",3,0,Asc);
    duty_register(head,sort_data);

    Log_info(run_task(*head));

}

/**
 * TODO:步骤->先查询年龄大于等于30的并且id小于等于5的人以升序的方式进行降序排序
 * select * from xxxtable where age > 30 AND id >= 4 order by desc
 * 由于那个集合的关系所以是先算出两个结果集进行最后的合并计算
 * */

void expmple2(){
    Link_Node *head = new(Link_Node);

    //查询大于三十的人
    duty_node *srceen1 = new(class duty_node);
    srceen1->init_node(SrceenDatas,res,2,30,GE);
    duty_register(head,srceen1);
    //查询id小于5的人
    duty_node *srcreen2 = new(class duty_node);
    srcreen2->init_node(SrceenDatas,res,3,5,LE);
    duty_register(head,srcreen2);
    //利用上面的结果做交集计算
    duty_node *set_c = new(class duty_node);
    set_c->init_node(Set_operation,"",0,0,AND);
    duty_register(head,set_c);
    //降序排序
    duty_node *sort_data = new (class duty_node);
    sort_data->init_node(SortOrChange,"",3,0,Desc);
    duty_register(head,sort_data);
    //输出答案
    Log_info(run_task(*head));

}


/**
 * TODO:步骤->先查询年龄小于等于40的并且id大于等于5的人以升序的方式进行降序排序最后结果取第一行
 * select * from xxxtable where age <= 40 AND id >= 5 order by desc limit 1
 * 由于那个集合的关系所以是先算出两个结果集进行最后的合并计算
 * */
void expmple3(){
    Link_Node *head = new(Link_Node);
    //查询大于三十的人
    duty_node *srceen1 = new(class duty_node);
    srceen1->init_node(SrceenDatas,res,2,40,LT);
    duty_register(head,srceen1);
    //查询id小于5的人
    duty_node *srcreen2 = new(class duty_node);
    srcreen2->init_node(SrceenDatas,res,3,5,LE);
    duty_register(head,srcreen2);
    //利用上面的结果做交集计算
    duty_node *set_c = new(class duty_node);
    set_c->init_node(Set_operation,"",0,0,AND);
    duty_register(head,set_c);
    //降序排序
    duty_node *sort_data = new (class duty_node);
    sort_data->init_node(SortOrChange,"",3,0,Desc);
    duty_register(head,sort_data);
    //limit操作
    duty_node *limit = new (class duty_node);
    limit->init_node(limit_data,"",1,0,LIMIT);
    duty_register(head,limit);

    Log_info(run_task(*head));
}



/**
 * TODO:步骤->先查询年龄小于等于40的并且id大于等于5的人以升序的方式进行降序排序最后结果取第一行
 * select * from xxxtable where age <= 40 AND id >= 5 or age >30 order by desc limit 1
 * 由于那个集合的关系所以是先算出两个结果集进行最后的合并计算
 * */



void expmple4(){

    Link_Node *head = new(Link_Node);
    //查询大于三十的人
    duty_node *srceen1 = new(class duty_node);
    srceen1->init_node(SrceenDatas,res,2,40,LT);
    duty_register(head,srceen1);
    //查询id小于5的人
    duty_node *srcreen2 = new(class duty_node);
    srcreen2->init_node(SrceenDatas,res,3,5,LE);
    duty_register(head,srcreen2);
    //利用上面的结果做交集计算
    duty_node *set_c = new(class duty_node);
    set_c->init_node(Set_operation,"",0,0,AND);
    duty_register(head,set_c);

    duty_node *srcreen3 = new(class  duty_node);
    srcreen3->init_node(SrceenDatas,res,2,30,GE);
    duty_register(head,srcreen3);

    duty_node *set_c1 = new(class duty_node);
    set_c1->init_node(Set_operation,"",0,0,OR);
    duty_register(head,set_c1);
    //降序排序
    duty_node *sort_data = new (class duty_node);
    sort_data->init_node(SortOrChange,"",3,0,Desc);
    duty_register(head,sort_data);
    //limit操作
    duty_node *limit = new (class duty_node);
    limit->init_node(limit_data,"",7,0,LIMIT);
    duty_register(head,limit);

    Log_info(run_task(*head));


}


/**
 * TODO:语句insert
 * Insert into tablename(id name age)values(1,xx,45)(1,aa,54)
 * 插入语句展示
 * */
//
//void demosql1(){
//    sql_operation *sqlOperation = new(sql_operation);
//    sqlOperation->handler = INSERTINTO;
//    sqlOperation->name = "tablename";
//    sqlOperation->table_colenm.push_back("id");
//    sqlOperation->table_colenm.push_back("name");
//    sqlOperation->table_colenm.push_back("age");
//    sqlOperation->datas.push_back("1,xx,45");
//    sqlOperation->datas.push_back("1,aa,54");
//}
///**
// * TODO:语句use
// * use xxx             xxx---->databasesname
// * 使用数据库
// * */
//
//
//void demosql2(){
//    sql_operation *sqlOperation = new(sql_operation);
//    sqlOperation->handler = USE;
//    sqlOperation->name = "xxx";
//}
///**
// * TODO:语句CREATE_DATABASE
// * CREATE DATABASE XXX            xxx---->databasesname
// * 使用数据库
// * */
//
//
//void demosql3(){
//
//    sql_operation *sqlOperation = new(sql_operation);
//        sqlOperation->handler = CREATE_DATABASE;
//        sqlOperation->name = "xxx";
//
//}
//
///**
// * TODO:语句CREATE_TABLE
// * CREATE table XXX(id int,LastName varchar(255))            xxx---->databasesname
// * 使用数据库
// * */
//void demosql4(){
//    sql_operation *sqlOperation = new(sql_operation);
//    sqlOperation->handler = CREATE_TABLE;
//    sqlOperation->name = "xxx";
//    sqlOperation->table_colenm.push_back("id int");
//    sqlOperation->table_colenm.push_back("LastName varchar(255)");
//}









