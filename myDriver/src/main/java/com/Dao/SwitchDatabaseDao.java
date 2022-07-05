package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class SwitchDatabaseDao {

    public boolean SwitchDatabase(StatementImp result, String databasename){
        String st="";
        return result.SwitchDatabase(st);
    }
}
