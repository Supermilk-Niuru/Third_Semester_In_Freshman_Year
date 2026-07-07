// LibrarySystem.h —— 图书馆管理系统类的声明
// 核心管理类，包含所有数据容器、业务逻辑和文件读写功能
#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include "Book.h"
#include "Borrower.h"
#include "Staff.h"
#include <vector>
#include <string>
using namespace std;

class LibrarySystem {
private:
    // ---- 三个数据容器 ----
    vector<Book> Books;            // 图书列表
    vector<Borrower> Borrowers;    // 借阅者列表
    vector<Staff> StaffMembers;    // 工作人员列表

    // ---- 文件名常量 ----
    const string BOOK_FILE = "books.txt";
    const string BORROWER_FILE = "borrowers.txt";
    const string STAFF_FILE = "staff.txt";

    // 暂停等待用户按键
    void pause();

    // ---- 文件读写私有方法 ----
    void saveBooks();              // 保存图书到 books.txt
    void loadBooks();              // 从 books.txt 加载图书
    void saveBorrowers();          // 保存借阅者到 borrowers.txt
    void loadBorrowers();          // 从 borrowers.txt 加载借阅者
    void saveStaff();              // 保存工作人员到 staff.txt
    void loadStaff();              // 从 staff.txt 加载工作人员

public:
    LibrarySystem();               // 构造函数：自动加载数据

    // 安全输入：获取 min~max 范围内的整数
    int getChoice(int min, int max);

    // ---- 图书管理 ----
    void addBook();
    void deleteBook();
    void modifyBook();
    void searchBook();
    void listAllBooks();

    // ---- 借阅人员管理 ----
    void addBorrower();
    void deleteBorrower();
    void modifyBorrower();
    void searchBorrower();
    void listAllBorrowers();

    // ---- 工作人员管理 ----
    void addStaff();
    void deleteStaff();
    void modifyStaff();
    void searchStaff();
    void listAllStaff();

    // ---- 借还操作 ----
    void borrowBook();
    void returnBook();

    // ---- 数据保存 ----
    void saveData();

    // ---- 统计数据（供菜单显示） ----
    int getBookCount() const;
    int getBorrowerCount() const;
    int getStaffCount() const;
};

#endif
