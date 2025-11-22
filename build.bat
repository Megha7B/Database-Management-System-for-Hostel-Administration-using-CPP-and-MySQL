cl /EHsc main.cpp ^
  /I "include\jdbc" ^
  /I "C:\Users\Admin\Downloads\mysql-connector-c++-9.4.0-winx64\mysql-connector-c++-9.4.0-winx64\include" ^
  /link /LIBPATH:"C:\Users\Admin\Downloads\mysql-connector-c++-9.4.0-winx64\mysql-connector-c++-9.4.0-winx64\lib64\vs14" mysqlcppconn.lib
