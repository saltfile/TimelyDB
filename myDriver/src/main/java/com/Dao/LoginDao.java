package com.Dao;


import jdbc.ConnectionImp;
import jdbc.StatementImp;
import org.springframework.stereotype.Repository;

import java.sql.DriverManager;
import java.sql.SQLException;

@Repository
public class LoginDao {
    public StatementImp login(String user, String password){
        try {
            Class.forName("jdbc.TSDBDriver");
            ConnectionImp myConnection= (ConnectionImp) DriverManager.getConnection("jdbc:tsdb://127.0.0.1:8686",user,password);
            StatementImp statementImp=(StatementImp) myConnection.createStatement();
            return statementImp;
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
}
