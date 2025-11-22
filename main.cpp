#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <limits>

// MySQL Connector/C++ headers
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// ---- Forward declarations ----
void addStudent(sql::Connection *con);
void viewStudents(sql::Connection *con);
void updateStudent(sql::Connection *con);
void deleteStudent(sql::Connection *con);
void viewProfile(sql::Connection *con, string email, string password);
void changePassword(sql::Connection *con, string email);

// ---- Admin Login ----
bool adminLogin(sql::Connection *con) {
    try {
        string user, pass;

        cout << "\n--- Admin Login ---\n";
        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM admin WHERE username=? AND password=?");
        pstmt->setString(1, user);
        pstmt->setString(2, pass);
        sql::ResultSet *res = pstmt->executeQuery();

        if (res->next()) {
            cout << "Login successful!\n";
            delete res;
            delete pstmt;
            return true;
        } else {
            cout << "Invalid username or password!\n";
            delete res;
            delete pstmt;
            return false;
        }
    } catch (sql::SQLException &e) {
        cout << "Error during login: " << e.what() << endl;
        return false;
    }
}

// ---- Admin Menu ----
void adminMenu(sql::Connection *con) {
    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(con); break;
            case 2: viewStudents(con); break;
            case 3: updateStudent(con); break;
            case 4: deleteStudent(con); break;
            case 5: cout << "Logging out...\n"; return;
            default: cout << "Invalid choice!\n";
        }
    }
}

// ---- Add Student ----
void addStudent(sql::Connection *con) {
    try {
        string name, course, contact, email, password;
        int room_no, year;

        cin.ignore();
        cout << "Enter student name: "; getline(cin, name);
        cout << "Enter room number: "; cin >> room_no;
        cout << "Enter course: "; cin >> course;
        cout << "Enter year: "; cin >> year;
        cout << "Enter contact: "; cin >> contact;
        cout << "Enter email: "; cin >> email;
        cout << "Enter password: "; cin >> password;

        sql::PreparedStatement *pstmt = con->prepareStatement(
            "INSERT INTO students (name, room_no, course, year, contact, email, password) VALUES (?, ?, ?, ?, ?, ?, ?)"
        );

        pstmt->setString(1, name);
        pstmt->setInt(2, room_no);
        pstmt->setString(3, course);
        pstmt->setInt(4, year);
        pstmt->setString(5, contact);
        pstmt->setString(6, email);
        pstmt->setString(7, password);

        pstmt->executeUpdate();
        cout << "✅ Student added successfully!\n";
        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "Error adding student: " << e.what() << endl;
    }
}

// ---- View Students ----
void viewStudents(sql::Connection *con) {
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM students");

        cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(8) << "Room" 
             << setw(10) << "Course" << setw(6) << "Year" << setw(12) 
             << "Contact" << setw(20) << "Email" << endl;
        cout << "-------------------------------------------------------------------------------\n";

        while (res->next()) {
            cout << left << setw(5) << res->getInt("id")
                 << setw(15) << res->getString("name")
                 << setw(8) << res->getInt("room_no")
                 << setw(10) << res->getString("course")
                 << setw(6) << res->getInt("year")
                 << setw(12) << res->getString("contact")
                 << setw(20) << res->getString("email") << endl;
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        cout << "Error viewing students: " << e.what() << endl;
    }
}

// ---- Update Student ----
void updateStudent(sql::Connection *con) {
    try {
        int id;
        cout << "Enter Student ID to update: ";
        cin >> id;

        // consume leftover newline before any getline
        auto flushLine = [](){
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };

        while (true) {
            int choice;
            cout << "\n--- Update Student (" << id << ") ---\n";
            cout << "1. Update Name\n";
            cout << "2. Update Course\n";
            cout << "3. Update Year\n";
            cout << "4. Update Room Number\n";
            cout << "5. Update Contact\n";
            cout << "6. Update Email\n";
            cout << "7. Update Password\n";
            cout << "8. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 8) {
                cout << "Returning to Admin Menu...\n";
                return;
            }

            sql::PreparedStatement *pstmt = nullptr;
            int rows = 0;

            switch (choice) {
                case 1: { // name
                    string name;
                    cout << "New name: ";
                    flushLine();
                    getline(cin, name);
                    pstmt = con->prepareStatement("UPDATE students SET name=? WHERE id=?");
                    pstmt->setString(1, name);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 2: { // course
                    string course;
                    cout << "New course: ";
                    flushLine();
                    getline(cin, course);
                    pstmt = con->prepareStatement("UPDATE students SET course=? WHERE id=?");
                    pstmt->setString(1, course);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 3: { // year
                    int year;
                    cout << "New year (int): ";
                    cin >> year;
                    pstmt = con->prepareStatement("UPDATE students SET year=? WHERE id=?");
                    pstmt->setInt(1, year);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 4: { // room_no
                    int room;
                    cout << "New room number (int): ";
                    cin >> room;
                    pstmt = con->prepareStatement("UPDATE students SET room_no=? WHERE id=?");
                    pstmt->setInt(1, room);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 5: { // contact
                    string contact;
                    cout << "New contact: ";
                    flushLine();
                    getline(cin, contact);
                    pstmt = con->prepareStatement("UPDATE students SET contact=? WHERE id=?");
                    pstmt->setString(1, contact);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 6: { // email
                    string email;
                    cout << "New email: ";
                    flushLine();
                    getline(cin, email);
                    pstmt = con->prepareStatement("UPDATE students SET email=? WHERE id=?");
                    pstmt->setString(1, email);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                case 7: { // password
                    string pwd;
                    cout << "New password: ";
                    flushLine();
                    getline(cin, pwd);
                    pstmt = con->prepareStatement("UPDATE students SET password=? WHERE id=?");
                    pstmt->setString(1, pwd);
                    pstmt->setInt(2, id);
                    rows = pstmt->executeUpdate();
                    break;
                }
                default:
                    cout << "Invalid choice!\n";
                    continue;
            }

            if (pstmt) {
                if (rows > 0) cout << "✅ Updated successfully!\n";
                else          cout << "⚠️ No student found with ID " << id << ".\n";
                delete pstmt;
            }
        }
    } catch (sql::SQLException &e) {
        cout << "❌ Error updating student: " << e.what() << endl;
    }
}
void deleteStudent(sql::Connection *con) {
    try {
        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;

        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("DELETE FROM students WHERE id=?");
        pstmt->setInt(1, id);

        int rows = pstmt->executeUpdate();
        if (rows > 0) {
            cout << "🗑️ Student deleted successfully!\n";
        } else {
            cout << "⚠️ No student found with ID " << id << ".\n";
        }

        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "❌ Error deleting student: " << e.what() << endl;
    }
}

// ---- User Menu ----
void userMenu(sql::Connection *con) {
    string email, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter email: "; cin >> email;
    cout << "Enter password: "; cin >> password;

    sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM students WHERE email=? AND password=?");
    pstmt->setString(1, email);
    pstmt->setString(2, password);
    sql::ResultSet *res = pstmt->executeQuery();

    if (res->next()) {
        cout << "✅ Login successful! Welcome " << res->getString("name") << endl;
        int choice;
        while (true) {
            cout << "\n--- User Menu ---\n";
            cout << "1. View My Details\n";
            cout << "2. Change Password\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) viewProfile(con, email, password);
            else if (choice == 2) changePassword(con, email);
            else if (choice == 3) { cout << "Logging out...\n"; break; }
            else cout << "Invalid choice!\n";
        }
    } else {
        cout << "❌ Invalid login credentials!\n";
    }
    delete res;
    delete pstmt;
}

// ---- View Profile ----
void viewProfile(sql::Connection *con, string email, string password) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM students WHERE email=? AND password=?");
        pstmt->setString(1, email);
        pstmt->setString(2, password);
        sql::ResultSet *res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\n--- My Profile ---\n";
            cout << "Name: " << res->getString("name") << endl;
            cout << "Room: " << res->getInt("room_no") << endl;
            cout << "Course: " << res->getString("course") << endl;
            cout << "Year: " << res->getInt("year") << endl;
            cout << "Contact: " << res->getString("contact") << endl;
            cout << "Email: " << res->getString("email") << endl;
        } else {
            cout << "⚠️ No profile found!\n";
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "❌ Error fetching profile: " << e.what() << endl;
    }
}

// ---- Change Password ----
void changePassword(sql::Connection *con, string email) {
    try {
        string newPass;
        cout << "Enter new password: ";
        cin >> newPass;

        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE students SET password=? WHERE email=?");
        pstmt->setString(1, newPass);
        pstmt->setString(2, email);

        int rows = pstmt->executeUpdate();
        if (rows > 0) cout << "✅ Password updated successfully!\n";
        else cout << "⚠️ Password update failed!\n";

        delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "❌ Error changing password: " << e.what() << endl;
    }
}

// ---- Main ----
int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "Sumitra@2003");
        con->setSchema("hostel_db");

        cout << "✅ Connected to MySQL successfully!\n";

        int choice;
        cout << "Welcome to Hostel Management System\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: if (adminLogin(con)) adminMenu(con); break;
            case 2: userMenu(con); break;
            case 3: cout << "Exiting...\n"; delete con; return 0;
            default: cout << "Invalid choice!\n";
        }

        delete con;
    } catch (sql::SQLException &e) {
        cout << "❌ Error connecting to MySQL: " << e.what() << endl;
        return 1;
    }
    return 0;
}