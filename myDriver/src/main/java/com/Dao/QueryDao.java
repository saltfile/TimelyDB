package com.Dao;

import jdbc.ResultSetIpm;
import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class QueryDao {

    public ResultSetIpm Query(StatementImp result){
        String st="SELECT * from {mytest}";
        return result.Query(st);
    }
}
