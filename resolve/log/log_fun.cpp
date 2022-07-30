//
// Created by saltfish on 2022/2/7.
//
#include "../Myall.h"

void log_info(char *data){
    string str = data;
    string out = "\033[34mLOG-INFO:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[34m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}
void log_info(string str){
    string out = "\033[34mLOG-INFO:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[34m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}

void log_erro(char *data){
    string str = data;
    string out = "\033[31mLOG-ERROR:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[31m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}


void log_debug(char *data){
    string str = data;
    string out = "\033[35mLOG-DEBUG:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[35m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}

void log_erro(string str){
    string out = "\033[31mLOG-ERROR:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[31m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}



void log_debug(string str){
    string out = "\033[35mLOG-DEBUG:------->\033[0m";
    time_t time1;
    time(&time1);
    struct tm *p = gmtime(&time1);
    string log = "\033[35m"+str+"\033[0m";
    cout<<1900+p->tm_year<<"/"<<1+p->tm_mon<<"/"<<p->tm_mday<<"    "
        <<8+p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec<<"  "<<out<<log<<endl;
}