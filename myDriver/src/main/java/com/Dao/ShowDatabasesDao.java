package com.Dao;

import jdbc.ResultSetIpm;
import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class ShowDatabasesDao {

    public ResultSetIpm ShowDatabases(StatementImp result, String databasename){
        String st="";
        return result.ShowDatabases(st);
    }
}
