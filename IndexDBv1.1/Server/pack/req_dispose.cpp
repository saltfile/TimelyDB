//
// Created by saltfish on 2022/1/9.
//

#include "../ser_drive.h"


/**
 * TODO:协议包的解析协议
 * @param arr传输过来还未经过处理的协议体
 *
 * */

void packge::solve_package(u8 *arr) {
    int lens = size_of_buf(arr)-1;
    fun_xor(arr,lens);
    this->pack_head = arr[0];

    this->len[0] = arr[4];
    this->len[1] = arr[5];
    this->len[2] = arr[6];
    this->len[3] = arr[7];

    //长度解析

    int lenRe = toInt(this->len);

    //crc解析
    short crc = getShort(arr[2],arr[1]);
    short crcRe = crc16(this->len);

    //获取协议版本
    this->version = arr[3];

    if(lens == lenRe && crc == crcRe){
        this->alllen = lenRe;
        this->result = get_Result(arr);
    } else{
        this->result = "err";
    }


}
/**
 * TODO:有点鸡肋只是能返回协议包的协议消息不过要再在解包之后才能返回
 * */


string packge::GetResult() {
    return this->result;
}


/**
 * TODO:协议体打包
 * @param result要传递的消息,head协议头
 * */

void packge::create_package(string result, u8 head) {
    int str_len = result.size();
    int all_len = str_len+9;
    this->alllen = all_len;
    cout<<all_len<<"    "<<endl;
    u8 *res = to_Char(result);
    this->all = (u8 *)malloc(sizeof(u8)*all_len);

    //协议安装协议头
    this->all[0] = head;
    u8 *lenall = int_to_byte(all_len);
    //协议中安装crc校验
    short crcRe = crc16(lenall);
    u8 *crc = to_crc16(crcRe);

    this->all[1] = crc[0];
    this->all[2] = crc[1];

    //协议版本
    this->all[3] = this->version;


    //获取协议长度
    this->all[4] = lenall[0];
    this->all[5] = lenall[1];
    this->all[6] = lenall[2];
    this->all[7] = lenall[3];
    //安装协议体
    int j = 0;
    for(int i = 8;i < all_len;i++){
        this->all[i] = res[j];
        j++;
    }
    //最后再异或
    this->all = fun_xor(this->all,all_len);
    cout<<endl;
    for(int i = 0;i < all_len;i++)
        printf("%d   ",this->all[i]);
}













u8* lab_fun() {
    u8 *arr;
    u8 aaa[4] = {97,98,99,100};
    int len = size_of_buf(aaa);
    arr = (u8 *)malloc(sizeof(u8)*len);
    for(int i =0 ;i < len-1;i++){
        arr[i] = aaa[i];
    }
    arr[len-1] = 0;
    return arr;

}




/**
 * TODO:将协议报文中的内容全部拿出来
 * @param bytes：协议整体
 * @return 解析出的内容
 * */
string get_Result(u8 *bytes){
//读取长度
    u8 len[4];
    len[0] = bytes[4];
    len[1] = bytes[5];
    len[2] = bytes[6];
    len[3] = bytes[7];
    int pack_size = 0;
    int str_size = 0;

    for(int i=0;i<sizeof(len);i++){
        pack_size+= (len[i] & 0xff) << ((3-i)*8);
    }
    int j = 8;
    //减去前面的校验版本的长度就是内容了
    str_size = pack_size-9;
    u8 str_result_byte[str_size];


    //先将内容转为u8形式
    for(int i = 0;i < str_size;i++){
        str_result_byte[i] = bytes[j];
        j++;
    }
    //u8转字符串
    char str_result_char[str_size+1];
    for(int i = 0;i < str_size;i++){
        str_result_char[i] = str_result_byte[i];
    }
    //这里的0表示结束符为了能将char *转成字符串
    str_result_char[str_size] = 0;
    string str_result_string = str_result_char;

    return str_result_string;
}







