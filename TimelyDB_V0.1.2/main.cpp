#include "_startup.h"


//
int main() {

    char *path =  load_config_path();
    load_config(path);
    char *add = get_config_base_path();

    push_file("user","xxx");









    /**
     * 自定义配置读取
     */

//    char *path =  load_config_path();
//    load_config(path);
//    char *add = get_config_base_path();

    /**
     * arr_list 自定义数组的使用例子
     */

//    arr_list *ptr = (arr_list *) malloc(sizeof(arr_list));
//    memset(ptr, 0, sizeof(arr_list));
//    ptr->initialization();
//    int *a = (int *) malloc(sizeof(int));
//    int*b = (int *) malloc(sizeof(int));
//    memset(b,0, sizeof(b));
//    int *c = (int *) malloc(sizeof(int));
//    int *d = (int *) malloc(sizeof(int));
//
//
//    int nud = 10;
//    int nud1 = 11;
//    int nud2 = 12;
//    int nud3 = 13;
//
//    a = &nud;
//    c = &nud2;
//    b = &nud1;
//    d = &nud3;
//
//    ptr->arr_list_add((void *)a);
//    ptr->arr_list_add((void *)b);
//    ptr->arr_list_add((void *)c);
//    ptr->arr_list_add((void *)d);
//
//    int *str =(int *)ptr->get(ptr->length-1);
//    cout<<*str;
//    ptr->arr_list_remove(ptr->length-1);
//    int *sty = (int *)ptr->get(ptr->length-1);
//    cout<<*sty;



    return 1;
}
