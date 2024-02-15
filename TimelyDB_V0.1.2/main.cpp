#include "_startup.h"



//异常处理封装

//
int main() {


    char *path =  load_config_path();
    load_config(path);

    init_file_system();

    DB_init_memery_tab();

    char* cloms[] = {"name","age"};
    data_type types[] = {VARCHAR,INT};

    DB_create_table("usnh_db","stuq",cloms,types,2);


//    map<string, int> myMap;
//    myMap["apple"] = 10;
//    myMap["banana"] = 5;
//    myMap["orange"] = 8;
//
//    vector<string> res;
//    // 使用迭代器遍历map
//    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
//        cout << "Key: " << it->first << ", Value: " << it->second << endl;
//        res.push_back(it->first);
//    }

//    file_write("usnh_db","push","sadakfhsdf");
//    file_write("usnh_db","push","sadakfhsdfss");
//    file_write("usnh_db","push","sadakfhsdfhh");
//TODO：目前可以得知服务端还可以使用
//    epollser_start(9898);





    
//    char *base = get_config_base_path();
//    int base_num = get_databse_num();
//    char ** database_s = find_database();


//    cout<<create_database("usnh_db");
//    cout<<create_table("usnh_db","push");
//    create_table("user","xxx");












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
