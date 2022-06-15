//
// Created by saltfish on 2022/1/9.
//

#include "../ser_drive.h"



/**
 * TODO:这里的数据参照的是陈琛的消息crc校验java也一样
 * @param bytes未被异或的数据,size数据长度
 * @return 被异或后的数据
 * */
u8* fun_xor(u8 *bytes,int size){
    for(int i  = 0; i < size;i++){
        bytes[i]=(u8) (bytes[i]^SELECT);
    }
    return bytes;
}



int toInt(u8 *b){
    int res = 0;
    for(int i=0;i<4;i++){
        res += (b[i] & 0xff) << ((3-i)*8);
    }
    return res;
}

void int_unbyte(u8 *arr,int num){
    u8 arrs[4];
    arr[3] = (u8) (num & 0xff);
    arr[2] = (u8) (num >> 8 & 0xff);
    arr[1] = (u8) (num >> 16 & 0xff);
    arr[0] = (u8) (num >> 24 & 0xff);
    arr = arrs;
}


int revert(int src) {
    int lowByte = (src & 0xFF00) >> 8;
    int highByte = (src & 0x00FF) << 8;
    return lowByte | highByte;
}

/**
 * TODO:具体的crc校验计算
 * @param bytes需要读取的crc值
 * @return 解出来的值
 * */

int crc16(u8 *bytes){
    int res = INIT_VALUE;
    for(int i = 0;i < 4;i++){
        res = res ^ bytes[i];
        for (int i = 0; i < BITS_OF_BYTE; i++) {
            res = (res & 0x0001) == 1 ? (res >> 1) ^ POLYNOMIAL : res >> 1;
        }
    }

    return revert(res);

}


/**
 * TODO:校验协议中的crc最后作对比
 * @param a,b是协议体中的值
 * @return crc值
 * */
int getShort(u8 a,u8 b){
    return (int) ((a & 0xFF)| (b << 8));
}


u8 *to_Char(string result){
    //先获取长度然后给相应空间
    int str_len = result.size();
    u8 *str = (u8 *)malloc(sizeof(u8)*str_len+1);
    //最后一位结束符
    str[str_len] = 10;
    for(int i = 0 ;i < str_len;i++){
        str[i] = result[i];
    }
    return str;
}
u8 * to_crc16(short x){
    u8 *ret=(u8 *)malloc(sizeof(u8)*2);
    ret[0] = (u8)((x >> 8) & 0xff);
    ret[1] = (u8)(x & 0xff);
    return ret;
}



u8 *int_to_byte(int len){
    u8 *byte_len = (u8 *)malloc(4);

    byte_len[3] = (u8) (len & 0xff);
    byte_len[2] = (u8) (len >> 8 & 0xff);
    byte_len[1] = (u8) (len >> 16 & 0xff);
    byte_len[0] = (u8) (len >> 24 & 0xff);

    return byte_len;
}




