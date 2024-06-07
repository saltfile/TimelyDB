#include "_startup.h"



//异常处理封装

//void funcd(int count,...){
//    va_list ap;
//    va_start(ap, count);
//
//    for (int i = 0; i < count; i++) {
//        char *s = va_arg(ap, char *);
//        cout<<s<<endl;
//    }
//
//    va_end(ap);
//}





int main() {
    char *inf =  str_copy("","asdasd");




    char *path =  load_config_path();
    load_config(path);
    init_file_system();
    DB_init_memery_tab();

    cout<<use_handle("use usnhdb")<<endl;
//    cout<<create_handle("create database xxxs")<<endl;
//    cout<<create_handle("create table xxx(age int,name varchar(255))")<<endl;

    cout<<insert_handle("insert into xxx (name,age) values(asd,45)");

//create database xxxs

//    run_file_loading();
//    run_mointor_loading();
//
//    sleep(60);
//    stop_file_pool();
//    stop_mointor_pool();

//    run_mointor_loading();
//    sleep(3);
//    mointor_add_task("usnh_db","stu","test",arr_col,3);
//    mointor_add_task("usnh_db34","stu4","test",arr_col,4);
//    mointor_add_task("usnh_db1","stu4","test",arr_col,3);
//    sleep(50);
//

//    m_handler.tab_name = str_copy("","str");
//    m_handler.file = str_copy("","asdasd");
//    m_handler.colums = arr_col;

//    get_tab_colums("usnh_db","stu");
//    funcd(4,"aaa","bbb","ccc");
//    char *path =  load_config_path();
//    load_config(path);
//
//    init_file_system();
//
//    DB_init_memery_tab();
//    char ** col_name = (char**)malloc(sizeof(char*) * (1024));
//    col_name[0] = "name";
//    col_name[1] = "age";
//    char ** col_val = (char**)malloc(sizeof(char*) * (1024));
//    col_val[0] = "aaaa";
//    col_val[1] = "1";
//    DB_insert_table("usnh_db","stu",col_name,2,col_val,2);
//
//    vector<string> list = get_DB_once_row("usnh_db","stu",0);
//    for (int i = 0; i < list.size(); ++i) {
//        cout<<list[i]<<endl;
//    }
//    vector<string> lis = get_DB_data("usnh_db","stu");
//    for (int i = 0; i < lis.size(); ++i) {
//        cout<<lis[i]<<endl;
//    }
//
//    run_file_loading();
//    sleep(50);
//    stop_time_pool();







//分词
//    scan_word *words = scanWordInit();
//    sqlsacnner(words,"use databasename");
//    sqlitWord head = get_word(words,0);
//    cout<<head.num;


//    std::shared_ptr<Lexer> lexer(new Lexer("./../code.ch"));
//    std::shared_ptr<Parser> parser(new Parser(lexer));


//test_fire();






//    integer *s = (integer*) malloc(sizeof(integer));
//    *s=5;
//    cout<<s->val;

    /**
     * 环形链表：使用方法
     */
//     ring_list *list =  (ring_list *) malloc(sizeof(ring_list));;
//     list->initialization(5,INT);
//     list->add(1);
//    list->add(2);
//    list->add(3);
//    list->add(4);
//    integer* va = (integer *)list->get(0);
//
//    cout<<va->val;
//    va = (integer *)list->get(1);
//    cout<<va->val;
//    cout<<list->get(1);
//    cout<<list->get(2);
//    cout<<list->get(3);
//    cout<<list->get(4);
//    cout<<list->get(5);


//    cout<<list->to_string();












//    char* cloms[] = {"name","age"};
//    data_type types[] = {VARCHAR,INT};

//    DB_create_table("usnh_db","stuq",cloms,types,2);


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

//    file_write("usnh_db","stu","sadakfhsdf");
//    file_write("usnh_db","stu","sadakfhsdfss");
//    file_write("usnh_db","stu","sadakf");
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

//    mointor_handler m_handler;

    return 1;
}
