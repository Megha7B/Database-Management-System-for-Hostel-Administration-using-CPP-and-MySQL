# 🚀 Hostel Management System (C++ + MySQL)

A lightweight, fast, and clean **Hostel Management System** built using **C++**, **MySQL**, and **MySQL Connector/C++**.  
Perfect for learning **database integration**, **file-free storage**, and **real-world console applications**.

---

<div align="center">

### 🔥 Tech Stack

![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white&style=for-the-badge)
![MySQL](https://img.shields.io/badge/MySQL-00618A?logo=mysql&logoColor=white&style=for-the-badge)
![MSVC](https://img.shields.io/badge/Compiler-MSVC%202022-blue?style=for-the-badge)
![Windows](https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge)

</div>

---

## 📌 Features

✔ Admin login  
✔ Add new students  
✔ View all students  
✔ Update **all fields** (Name, Age, Course, Year, Room, Phone, Email)  
✔ Delete student  
✔ Real MySQL backend  
✔ Clean, modular C++ code  
✔ Easy to compile using a single `build.bat`  
✔ Beginner friendly  

---

## 📂 Project Structure

HostelManagement/
│
├── main.cpp
├── build.bat
├── run.bat
├── README.md
│
├── include/
│    └── jdbc/    # MySQL Connector headers
│
└── output/
     └── main.exe (generated after build)

---

## 🛠️ Installation & Setup

### 1️⃣ Install Required Tools

| Tool | Purpose |
|------|---------|
| **MSVC Build Tools 2022** | C++ compiler & linker |
| **MySQL Server** | Database backend |
| **MySQL Connector/C++ 9.4** | API to connect C++ with MySQL |

---

## 🗄️ 2️⃣ MySQL Database Setup

Run these commands in MySQL:

```sql
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
 
## Instructions to run,

1) Open Developer Command Prompt for VS 2022
2)//move to your project folder.
cd C:\Users\Admin\Desktop\HostelManagement
3)type build and enter.
//What build.bat do internally, it runs this;
cl /EHsc main.cpp ^
  /I "include\jdbc" ^
  /I "C:\Path\To\mysql-connector\include" ^
  /link /LIBPATH:"C:\Path\To\mysql-connector\lib64\vs14" mysqlcppconn.lib
and give output, output/main.exe
4)type main.exe and enter.
There you go...!!



