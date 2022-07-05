package jdbc;

import jdbc.src.MyResultSet;

import java.sql.SQLException;
import java.util.HashMap;

public class ResultSetIpm extends MyResultSet {


    //获得条数
    public int count;
    //当前位置
    public int index;

    public HashMap<String,String> results;

    /*
    id,name,page;12,xxx,13

     */
    public ResultSetIpm(String result) {

        results=new HashMap<>();
        //分列
        String[] list=result.split(";");
        int len=list.length;
        count=len-1;
        index=0;
        //结果的列字段数量
        String[] first=list[0].split(",");
        int lens=first.length;
        for (int i = 1; i < len; i++) {
            String[]  row=list[i].split(",");
            for (int j = 0; j < lens; j++) {
                results.put(first[j]+i,row[j]);
            }
        }
    }
    @Override
    public boolean next() throws SQLException {
        if (count<(++index)){
            return false;
        }
        return true;
    }

    @Override
    public String getString(String columnLabel) throws SQLException {
      return  results.get(columnLabel+index);
    }

}
