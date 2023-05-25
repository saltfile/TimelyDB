

#ifndef TIMELYDB_V0_1_2__STARTUP_H
#define TIMELYDB_V0_1_2__STARTUP_H
#include "tool/tool_base.h"
#include "config_init/config_h.h"
#include "time_pool/t_pool.h"
using namespace std;

#define CONFIG_INIT()\
({\
char * pro_path = load_config_path();\
printf("current absolute path:%s\n", pro_path);\
int res = load_config(pro_path);\
(res);\
})\
















#endif //TIMELYDB_V0_1_2__STARTUP_H
