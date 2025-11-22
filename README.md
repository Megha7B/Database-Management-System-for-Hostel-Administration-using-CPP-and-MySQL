# Database-Management-System-for-Hostel-Administration-using-CPP-and-MySQL

A simple and fast **Hostel Management System** built using **C++**,
**MySQL**, and **MySQL Connector/C++**.\
Perfect for learning **database connectivity** and building **real
console applications**.

------------------------------------------------------------------------

## 🔥 Tech Stack

-   C++\
-   MySQL\
-   MySQL Connector/C++\
-   MSVC 2022 (Windows)

------------------------------------------------------------------------

## 📌 Features

-   Admin login\
-   Student login\
-   Add new students\
-   View all students\
-   Update all student details\
-   Delete student\
-   Real MySQL backend\
-   Easy build using a single batch file\

------------------------------------------------------------------------

## 📂 Project Structure

    HostelManagement/
│
├── bin/
│
├── include/
│   ├── jdbc/
│   ├── mysql/
│   └── mysqlx/
│
├── lib64/
│   ├── plugin/
│   └── vs14/
│       ├── libcrypto-3-x64.dll
│       ├── libssl-3-x64.dll
│       ├── mysqlcppconn-10-vs14.dll
│       ├── mysqlcppconn-10-vs14.pdb
│       ├── mysqlcppconnx-2-vs14.dll
│       └── mysqlcppconnx-2-vs14.pdb
│
├── output/
│   ├── libmysql.dll
│   ├── main.exe
│   └── mysqlcppconn-10-vs14.dll
│
├── build.bat
├── libmysql.dll
├── main.cpp
├── main.exe
├── main.obj
└── README.md

------------------------------------------------------------------------

## 🛠️ 1. Requirements

  Tool                      Needed For
  ------------------------- ------------------------
  MSVC Build Tools 2022     Compiling C++
  MySQL Server              Database
  MySQL Connector/C++ 9.4   C++ → MySQL connection

------------------------------------------------------------------------

## 🗄️ 2. MySQL Setup

Run this in MySQL:

``` sql
CREATE DATABASE hostel;
USE hostel;

CREATE TABLE students (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100),
  age INT,
  course VARCHAR(50),
  year INT,
  room_number VARCHAR(20),
  contact VARCHAR(20),
  email VARCHAR(100)
);
```

------------------------------------------------------------------------

## Instructions to run,

1. Open Developer Command Prompt for VS 2022
2. Move to your project folder using cd command. 
ex. cd C:\Users\Admin\Desktop\ProjectFolder
3.type "build" and enter.
//What build.bat do internally, it runs this;
cl /EHsc main.cpp ^
  /I "include\jdbc" ^
  /I "C:\Path\To\mysql-connector\include" ^
  /link /LIBPATH:"C:\Path\To\mysql-connector\lib64\vs14" mysqlcppconn.lib
and give output, output/main.exe
4. Type main.exe and enter.

There you go...!!
------------------------------------------------------------------------

## 🖼️ 4. Output (Screenshots)
<img width="1366" height="720" alt="Screenshot 2025-11-22 163956" src="https://github.com/user-attachments/assets/0ee041c1-3871-44a4-9175-3b2c5e95217f" />
<img width="1366" height="720" alt="Screenshot 2025-11-22 163841" src="https://github.com/user-attachments/assets/c98087ef-d279-4e94-8c68-40f260927f4e" />


