#include "_startup.h"








//
int main() {
    load_config("/opt/TIme1.2/TimelyDB/TimelyDB_V0.1.2/config.yaml");
    cout<<get_config_address()<<endl;
    cout<<get_config_port()<<endl;






    return 1;
}
