//#include "tool/tool_base.h"
#include "config_init/config_h.h"
using namespace std;
#define PATH_SIZE 255


char * load_project_path(){
    char *pro_path = (char *) malloc(PATH_SIZE);

    if (NULL == realpath("../", pro_path))

    {
        printf("***Error***\n");

        exit(-1);

    }

    strcat(pro_path, "/");

    return pro_path;


}





int main() {
    //获取当前项目位置
    char * pro_path = load_project_path();

    printf("current absolute path:%s\n", pro_path);
    //读取对应的配置文件      server-port address
    load_config("/opt/TIme1.2/TimelyDB/TimelyDB_V0.1.2/config.yaml");
//    cout<<str_spilt_size("aaa bbb ccc"," ");
    return 0;
}
