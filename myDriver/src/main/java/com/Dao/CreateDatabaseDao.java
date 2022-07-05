package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class CreateDatabaseDao {

    public boolean CreateDatabase(StatementImp result, String databasename){
        String st="create database "+databasename;
        return result.CreateDatabase(st);
    }
}
