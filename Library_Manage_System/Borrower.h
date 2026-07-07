// Borrower.h —— 借阅人员类的声明
// 公有继承 Person，拥有学号、借阅列表、违约次数等特有属性
#ifndef BORROWER_H
#define BORROWER_H
#include "Person.h"
#include <vector>
#include <string>
using namespace std;

class Borrower : public Person {
private:
    string StudentId;              // 学号
    vector<string> BorrowedBooks;  // 当前借阅的ISBN列表
    int ViolationCount;            // 违约次数

public:
    Borrower();
    Borrower(string n, string sid, string g, string p, string e);

    // ---- Getter ----
    string getStudentId() const;
    int getViolationCount() const;
    vector<string> getBorrowedBooks() const;
    int getBorrowedCount() const;

    // ---- Setter ----
    void setStudentId(string sid);
    void setViolationCount(int v);

    // 借还操作
    void addBorrowedBook(string isbn);      // 借书：ISBN加入列表
    void removeBorrowedBook(string isbn);   // 还书：从列表移除
    void addViolation();                    // 违约次数+1

    // 重写基类的 display
    void display() const override;

    // 文件读写
    string toFileString() const;
    void fromFileString(const string &str);
};

#endif
