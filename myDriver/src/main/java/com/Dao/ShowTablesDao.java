package com.Dao;

import jdbc.ResultSetIpm;
import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class ShowTablesDao {
    public ResultSetIpm ShowTables(StatementImp result, String tablename){
        String st="show tables";
        return result.ShowTables(st);
    }
}
