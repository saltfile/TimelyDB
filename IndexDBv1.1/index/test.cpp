//
// Created by zy on 2022/4/2.
//

//#include <cstring>
//
//#include <bitset>
////#include "index_operation.h"
//#include "z_malloc.h"
#include "database_index.h"


int z_index(){
    /*
     * CREATE  database;* */
    sql_operation* create_database_sql=malloc_sqloperation();
    create_database_sql->handler=CREATE_DATABASE;
    create_database_sql->name="school";
    /*
     *
     * Drop database;* */
    sql_operation* drop_sql=malloc_sqloperation();
    drop_sql->handler=DROP_DATABASE;
    drop_sql->name="school";
/*
 *
 *
 * insert into student (name,age) values(?,?);*/
    sql_operation* insert_sql=malloc_sqloperation();
    insert_sql->handler=INSERTINTO;
    insert_sql->name="student";
    insert_sql->timestamp="15613216545";

//    insert_sql->data_list=malloc_sqlcondition();
    insert_sql->data_list->c_name="age";
    insert_sql->data_list->c_symbol=Assignment;
    insert_sql->data_list->c_value="18";
//    insert_sql->data_list->dataTypes=INT;

    insert_sql->data_list->next=malloc_sqlcondition();
    (insert_sql->data_list->next)->cTypes=AND;
    (insert_sql->data_list->next)->c_name="name";
    (insert_sql->data_list->next)->c_symbol=Assignment;
    (insert_sql->data_list->next)->c_value="zhangsan";
    (insert_sql->data_list->next)->dataTypes=VARCHAR;

/*
 *
func run(c *<-chan int8){
	var a int8=99
	time.Sleep(1*time.Second)

 *
 * delete from student age=18 AND name="zhangsan";*/
    sql_operation* delete_sql=malloc_sqloperation();
    delete_sql->handler=DELETE;
    delete_sql->name="student";

//    delete_sql->data_list=malloc_sqlcondition();
    delete_sql->data_list->c_name="age";
    delete_sql->data_list->c_symbol=Assignment;
    delete_sql->data_list->c_value="18";
//    delete_sql->data_list->dataTypes=INT;

  //delete_sql->timestamp="15613216545";//有主键的删除

    condition* datalist_node= malloc_sqlcondition();
    datalist_node->cTypes=OR;
    (datalist_node)->c_name="name";
    (datalist_node)->c_symbol=Assignment;
    (datalist_node)->c_value="zhangsan";
//    (datalist_node)->dataTypes=VARCHAR;
    delete_sql->data_list->next=datalist_node;

/*
 *
 *
 *
 * select * from xxxtable where age > 30 AND id >= 4 order by desc*/
    sql_operation* select_sql=malloc_sqloperation();
    select_sql->handler=SELECTS;
    select_sql->name="student";
    select_sql->field="*";

//    select_sql->data_list=malloc_sqlcondition();
    select_sql->data_list->c_name="age";
    select_sql->data_list->c_symbol=Assignment;//>
    select_sql->data_list->c_value="18";
//    select_sql->data_list->dataTypes=INT;

    //select_sql->timestamp="18";

    select_sql->data_list->next=malloc_sqlcondition();
    (select_sql->data_list->next)->cTypes=AND;
    (select_sql->data_list->next)->c_name="name";
    (select_sql->data_list->next)->c_symbol=GE;//>=
    (select_sql->data_list->next)->c_value="zhangsan";
//    (select_sql->data_list->next)->dataTypes=VARCHAR;

    select_sql->data_list->next->next=malloc_sqlcondition();
    (select_sql->data_list->next)->next->cTypes=GROUPBY;
    select_sql->data_list->next->next->next=malloc_sqlcondition();
    (select_sql->data_list->next)->next->next->cTypes=Desc;

/*
 *
 * Use database;*/
    sql_operation* use_dataname=malloc_sqloperation();
    use_dataname->handler=USE;
    use_dataname->name="school";
/*
 *
 * CREATE TABLE student(age int,name varchar(255),timestamp varchar(255))*/
    sql_operation* create_table=malloc_sqloperation();
    create_table->handler=CREATE_TABLE;
    create_table->name="student";

//    create_table->data_list=malloc_sqlcondition();
    create_table->data_list->next=malloc_sqlcondition();
    create_table->data_list->next->next=malloc_sqlcondition();



    create_table->data_list->c_name="age";
    create_table->data_list->dataTypes=INT;

    create_table->data_list->next->c_name="name";
//    create_table->data_list->next->dataTypes=VARCHAR;
    create_table->data_list->next->c_value="255";

    create_table->data_list->next->next->c_name="timestamp";
//  create_table->data_list->next->next->dataTypes=VARCHAR;
    create_table->data_list->next->next->c_value="255";


//------------------------------------------
    sql_oper_create_database(create_database_sql);//ok

    sql_oper_use(use_dataname);//ok
    sql_oper_create_table(create_table); //ok
    sql_oper_insrtinto(insert_sql); //ok

//    sql_oper_select(select_sql);
    sql_oper_delete(delete_sql);
//    sql_oper_drop_database(drop_sql);

//    free(insert_sql);
//    free(delete_sql);
//    free(select_sql);
}