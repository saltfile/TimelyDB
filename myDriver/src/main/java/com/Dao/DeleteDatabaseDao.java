package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class DeleteDatabaseDao {
    public boolean DeleteDatabase(StatementImp result, String databasename){
        String st="drop "+databasename;
        return result.DeleteDatabase(st);
    }
}
