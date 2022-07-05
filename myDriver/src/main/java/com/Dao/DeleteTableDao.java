package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class DeleteTableDao {
    public boolean DeleteTable(StatementImp result, String tablename){
        String st="drop table "+tablename;
        return result.DeleteTable(st);
    }
}
