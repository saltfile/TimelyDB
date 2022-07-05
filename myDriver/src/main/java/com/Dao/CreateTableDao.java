package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class CreateTableDao {
    public boolean CreateTable(StatementImp result, String tablename){
        String st="create table "+tablename;
        return result.CreateTable(st);
    }
}
