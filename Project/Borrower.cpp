// Borrower.cpp —— 借阅人员类的实现
#include "Borrower.h"
#include <iostream>
#include <sstream>
using namespace std;

Borrower::Borrower() : ViolationCount(0) {}

Borrower::Borrower(string n, string sid, string g, string p, string e)
    : Person(n, g, p, e), StudentId(sid), ViolationCount(0) {}

string Borrower::getStudentId() const { return StudentId; }
int Borrower::getViolationCount() const { return ViolationCount; }
vector<string> Borrower::getBorrowedBooks() const { return BorrowedBooks; }
int Borrower::getBorrowedCount() const { return BorrowedBooks.size(); }

void Borrower::setStudentId(string sid) { StudentId = sid; }
void Borrower::setViolationCount(int v) { ViolationCount = v; }

void Borrower::addBorrowedBook(string isbn) { BorrowedBooks.push_back(isbn); }

void Borrower::removeBorrowedBook(string isbn) {
    for (auto it = BorrowedBooks.begin(); it != BorrowedBooks.end(); ++it) {
        if (*it == isbn) { BorrowedBooks.erase(it); break; }
    }
}

void Borrower::addViolation() { ViolationCount++; }

void Borrower::display() const {
    Person::display();
    cout << " | 学号: " << StudentId
         << " | 借阅: " << BorrowedBooks.size() << "本"
         << " | 违约: " << ViolationCount << "次" << endl;
}

// ---- 文件读写 ----
// 格式：姓名|性别|电话|邮件|学号|违约次数|ISBN1,ISBN2,...
string Borrower::toFileString() const {
    string result = personToFileString() + "|" + StudentId + "|"
                  + to_string(ViolationCount) + "|";
    // 借阅的ISBN列表用逗号连接
    for (size_t i = 0; i < BorrowedBooks.size(); i++) {
        if (i > 0) result += ",";
        result += BorrowedBooks[i];
    }
    return result;
}

// 从文件字符串解析
void Borrower::fromFileString(const string &str) {
    stringstream ss(str);
    string segment;
    int idx = 0;
    while (getline(ss, segment, '|')) {
        switch (idx) {
            case 0: setName(segment); break;
            case 1: setGender(segment); break;
            case 2: setPhone(segment); break;
            case 3: setEmail(segment); break;
            case 4: StudentId = segment; break;
            case 5: ViolationCount = stoi(segment); break;
            case 6:  // ISBN列表段：按逗号拆开
                BorrowedBooks.clear();
                if (!segment.empty()) {
                    stringstream isbnStream(segment);
                    string isbn;
                    while (getline(isbnStream, isbn, ',')) {
                        BorrowedBooks.push_back(isbn);
                    }
                }
                break;
        }
        idx++;
    }
}
