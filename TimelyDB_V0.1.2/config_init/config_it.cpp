//
// Created by saltfish on 23-5-16.
//

#include "config_h.h"

int add(int a,int b){
    return a+b;
}
static dbconfig *conf = new dbconfig();

char* get_config_port(){
    return conf->port;
}
char * get_config_address(){
    return conf->address;
}

int load_config(const char *file_name){
    FILE* fh = fopen(file_name, "r");

    yaml_parser_t parser;
    yaml_token_t token;



    if (!yaml_parser_initialize(&parser))
        fputs("Failed to initialize parser!\n", stderr);
    if (fh == NULL)
        fputs("Failed to open file!\n", stderr);
    yaml_parser_set_input_file(&parser, fh);
    char *parent = NULL;
    int state = 0;
    char** datap;
    do{

    unsigned char* tk;
    yaml_parser_scan(&parser, &token);


    switch(token.type)
    {
        case YAML_KEY_TOKEN:     state = 0; break;
        case YAML_VALUE_TOKEN:   state = 1; break;

        case YAML_SCALAR_TOKEN:
            tk = token.data.scalar.value;
            if (state == 0) {
                if (!strcmp((char *)tk, "dbconfig")) {
                    parent = str_copy(parent,(char *)tk);

                }

                if (!strcmp((char *)tk, "port")&& !strcmp(parent,"dbconfig")){
                    datap = &conf->port;

                }
                if (!strcmp((char *)tk, "address")&& !strcmp(parent,"dbconfig")){
                    datap = &conf->address;

                }

            }else {
                *datap = strdup((char*)tk);
            }
            break;
        default: break;
    }


} while (token.type != YAML_STREAM_END_TOKEN);
    if (token.type != YAML_STREAM_END_TOKEN)
        yaml_token_delete(&token);
    free_str(parent);


    printf(LIGHT_BLUE"TimelyDb初始化ing ... \n");
    printf(LIGHT_BLUE"开启服务 \n");
    printf(LIGHT_BLUE"        port：%s \n",conf->port);
    printf(LIGHT_BLUE"        address：%s \n\033[m",conf->address);

}
