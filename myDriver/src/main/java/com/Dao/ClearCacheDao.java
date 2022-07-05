package com.Dao;

import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

@Repository
public class ClearCacheDao {

    public boolean ClearCache(StatementImp result){
        String st="";
        return result.ClearCache(st);
    }
}
