package com.Entity;

public class ResponseResult {

    private Object result;
    private String msg;
    private int code;

    public ResponseResult(String msg, Object result, int code){
        this.msg=msg;
        this.result=result;
        this.code=code;
    }

}
