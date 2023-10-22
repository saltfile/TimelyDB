//
// Created by saltfish on 23-5-16.
//

#ifndef TIMELYDB_V0_1_2_CONFIG_H_H
#define TIMELYDB_V0_1_2_CONFIG_H_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <cstring>
#include <cassert>
#include <yaml.h>
#include<unistd.h>
#include "../tool/tool_base.h"
#include <iostream>
using namespace std;
#define PATH_SIZE 255

#define NONE         "\033[m";
#define LIGHT_BLUE   "\033[1;34m"
#define LIGHT_PURPLE "\033[1;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define DEFAULT_XML_FILE "../config.yaml"
typedef struct dbconfig{
    char *port;
    char *host;
    char *base_path;
    dbconfig(){
    this->port = "8080";
    this->host = "localhost";
    this->base_path = "/home/saltfish/indexTSDB";
    }
}dbconfig;

int add(int a,int b);

int load_config(const char *file_name);

char * get_config_port();

char * get_config_address();

char * get_config_base_path();

char * load_project_path();

char* load_config_path();

#endif //TIMELYDB_V0_1_2_CONFIG_H_H
