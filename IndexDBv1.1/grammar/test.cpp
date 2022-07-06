#include "Myall.h"
#include "database_engine.h"
/**
 * "select id,age,name from aaa where age > 2 and id = 12 or xxx = xs"
 * "insert into tname  values(id,name,age,sex)"
 * @return
 */




int tests() {
use_fun();
char *sss = "insert into tname (id,name,age,sex) values(num,asd,45,N)(num,asd,11,N)(num,asd,23,N)(num,asd,67,N)";
char *str =   "select id,age,name from aaa where age > 2 and id = 12 or xxx = xs";
sqlsacnner(str);
get_wordlen();
create_sqltree();
treenode *root =check_tree();//词组中第一个word匹配
//sqlsacnner(sss);
//treenode *root2 = check_tree();
//sql_sel(root);
//tree_trim(root);







//
//char a[4];
//char *sre = "aaa";
//strcat(a,sre);
//cout<<a;







//sqlitWord wordbbbbbbbb11 = get_word(1);

//char arr[50] = "asfsfgd";
//char arr1[50] = "xxx";
//std::size_t arrs =  strlen(arr1)+strlen(arr)+1;
//char strs[arrs];
//memset(strs,0,arrs);
//strcat(strs,arr);
//strcat(strs,arr1);
//strs[strlen(arr1)+strlen(arr)] = '\0';
//char *stras = (char *)malloc(sizeof(strlen(arr1)+strlen(arr)+1));
//memcpy(stras,strs,strlen(arr1)+strlen(arr)+1);

//test();



//treenode *root = (treenode *)malloc(sizeof(treenode));
//root->str = "aaa";
//
//    treenode *root2 = (treenode *)malloc(sizeof(treenode));
//    root2->str = "bbb";
//
//    treenode *root3 = (treenode *)malloc(sizeof(treenode));
//    root3->str = "ccc";
//list *p = (list *)malloc(sizeof(list));
//add_list(p,root);
//add_list(p,root2);
//add_list(p,root3);
//dis_play(p);
//treenode *port = get_list_node(p,1);
//log_info(port->str);
//p = remove_node(p,1);
//port = get_list_node(p,1);
//log_info(port->str);

    return 0;
}
