//
// Created by saltfish on 23-5-16.
//

#ifndef TIMELYDB_V0_1_2_CONFIG_H_H
#define TIMELYDB_V0_1_2_CONFIG_H_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <cassert>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <iostream>

using namespace std;
#define DEFAULT_XML_FILE "../config.xml"


static int parse_phone_book(const char *file_name);


#endif //TIMELYDB_V0_1_2_CONFIG_H_H
