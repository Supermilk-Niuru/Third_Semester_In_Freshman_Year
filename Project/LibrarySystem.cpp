// LibrarySystem.cpp —— 图书馆管理系统类的实现
// 包含完整的业务逻辑：CRUD、借还书、文件读写
#include "LibrarySystem.h"
#include <iostream>
#include <fstream>      // 文件流：ifstream / ofstream
#include <limits>       // numeric_limits
using namespace std;

// ============================================
//  构造函数：创建系统对象时自动从文件加载已有数据
// ============================================
LibrarySystem::LibrarySystem() {
    loadBooks();       // 从 books.txt 加载图书
    loadBorrowers();   // 从 borrowers.txt 加载借阅者
    loadStaff();       // 从 staff.txt 加载工作人员
}

// ============================================
//  工具函数
// ============================================

// pause：暂停程序，等待用户按回车
void LibrarySystem::pause() {
    cout << "按回车键继续...";
    cin.get();
}

// getChoice：安全的整数输入，只接受 min~max 范围
int LibrarySystem::getChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();  // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请重新输入（" << min << "-" << max << "）：";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

// ============================================
//  文件读写 —— 图书
// ============================================

// saveBooks：将所有图书写入 books.txt，每行一本书
void LibrarySystem::saveBooks() {
    ofstream outFile(BOOK_FILE);   // 打开输出文件流
    if (!outFile.is_open()) {
        cout << "❌ 无法打开 " << BOOK_FILE << " 写入！\n";
        return;
    }
    for (const auto &b : Books) {
        outFile << b.toFileString() << endl;  // 每本书一行
    }
    outFile.close();
}

// loadBooks：从 books.txt 读取所有图书
void LibrarySystem::loadBooks() {
    ifstream inFile(BOOK_FILE);    // 打开输入文件流
    if (!inFile.is_open()) return; // 文件不存在是首次运行，正常跳过
    Books.clear();
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Book b;
            b.fromFileString(line);
            Books.push_back(b);
        }
    }
    inFile.close();
}

// ============================================
//  文件读写 —— 借阅者
// ============================================

void LibrarySystem::saveBorrowers() {
    ofstream outFile(BORROWER_FILE);
    if (!outFile.is_open()) {
        cout << "❌ 无法打开 " << BORROWER_FILE << " 写入！\n";
        return;
    }
    for (const auto &b : Borrowers) {
        outFile << b.toFileString() << endl;
    }
    outFile.close();
}

void LibrarySystem::loadBorrowers() {
    ifstream inFile(BORROWER_FILE);
    if (!inFile.is_open()) return;
    Borrowers.clear();
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Borrower b;
            b.fromFileString(line);
            Borrowers.push_back(b);
        }
    }
    inFile.close();
}

// ============================================
//  文件读写 —— 工作人员
// ============================================

void LibrarySystem::saveStaff() {
    ofstream outFile(STAFF_FILE);
    if (!outFile.is_open()) {
        cout << "❌ 无法打开 " << STAFF_FILE << " 写入！\n";
        return;
    }
    for (const auto &s : StaffMembers) {
        outFile << s.toFileString() << endl;
    }
    outFile.close();
}

void LibrarySystem::loadStaff() {
    ifstream inFile(STAFF_FILE);
    if (!inFile.is_open()) return;
    StaffMembers.clear();
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            Staff s;
            s.fromFileString(line);
            StaffMembers.push_back(s);
        }
    }
    inFile.close();
}

// ============================================
//  图书管理功能
// ============================================

void LibrarySystem::addBook() {
    string title, isbn, author, publisher;
    int printCount;

    cout << "\n📚 添加图书\n";
    cout << "书名: "; getline(cin, title);
    cout << "ISBN: "; getline(cin, isbn);
    cout << "作者: "; getline(cin, author);
    cout << "出版社: "; getline(cin, publisher);
    cout << "印次: "; cin >> printCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Books.push_back(Book(title, isbn, author, publisher, printCount));
    cout << "✅ 图书添加成功！\n";
    pause();
}

void LibrarySystem::deleteBook() {
    string isbn;
    cout << "\n📚 删除图书\n";
    cout << "请输入ISBN: "; getline(cin, isbn);

    for (auto it = Books.begin(); it != Books.end(); ++it) {
        if (it->getIsbn() == isbn) {
            if (it->getIsBorrowed()) {
                cout << "❌ 该书正在被借阅，无法删除！\n";
            } else {
                Books.erase(it);
                cout << "✅ 图书删除成功！\n";
            }
            pause();
            return;
        }
    }
    cout << "❌ 未找到该ISBN的图书！\n";
    pause();
}

void LibrarySystem::modifyBook() {
    string isbn;
    cout << "\n📚 修改图书\n";
    cout << "请输入ISBN: "; getline(cin, isbn);

    for (auto &b : Books) {
        if (b.getIsbn() == isbn) {
            string title, author, publisher;
            int printCount;

            cout << "新书名（回车跳过）: "; getline(cin, title);
            if (!title.empty()) b.setTitle(title);
            cout << "新作者（回车跳过）: "; getline(cin, author);
            if (!author.empty()) b.setAuthor(author);
            cout << "新出版社（回车跳过）: "; getline(cin, publisher);
            if (!publisher.empty()) b.setPublisher(publisher);
            cout << "新印次（输入0跳过）: "; cin >> printCount;
            if (printCount > 0) b.setPrintCount(printCount);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "✅ 图书修改成功！\n";
            pause();
            return;
        }
    }
    cout << "❌ 未找到该ISBN的图书！\n";
    pause();
}

void LibrarySystem::searchBook() {
    string keyword;
    cout << "\n📚 查询图书\n";
    cout << "请输入书名/ISBN/作者: "; getline(cin, keyword);

    bool found = false;
    for (const auto &b : Books) {
        if (b.getTitle().find(keyword) != string::npos ||
            b.getIsbn().find(keyword) != string::npos ||
            b.getAuthor().find(keyword) != string::npos) {
            b.display();
            found = true;
        }
    }
    if (!found) cout << "❌ 未找到匹配的图书！\n";
    pause();
}

void LibrarySystem::listAllBooks() {
    cout << "\n📚 所有图书（共" << Books.size() << "本）\n";
    if (Books.empty()) {
        cout << "暂无图书数据。\n";
    } else {
        for (const auto &b : Books) b.display();
    }
    pause();
}

// ============================================
//  借阅人员管理功能
// ============================================

void LibrarySystem::addBorrower() {
    string name, sid, gender, phone, email;
    cout << "\n👤 添加借阅者\n";
    cout << "姓名: "; getline(cin, name);
    cout << "学号: "; getline(cin, sid);
    cout << "性别: "; getline(cin, gender);
    cout << "电话: "; getline(cin, phone);
    cout << "邮件: "; getline(cin, email);

    Borrowers.push_back(Borrower(name, sid, gender, phone, email));
    cout << "✅ 借阅者添加成功！\n";
    pause();
}

void LibrarySystem::deleteBorrower() {
    string sid;
    cout << "\n👤 删除借阅者\n";
    cout << "请输入学号: "; getline(cin, sid);

    for (auto it = Borrowers.begin(); it != Borrowers.end(); ++it) {
        if (it->getStudentId() == sid) {
            if (it->getBorrowedCount() > 0) {
                cout << "❌ 该借阅者还有未还的书，无法删除！\n";
            } else {
                Borrowers.erase(it);
                cout << "✅ 借阅者删除成功！\n";
            }
            pause();
            return;
        }
    }
    cout << "❌ 未找到该学号的借阅者！\n";
    pause();
}

void LibrarySystem::modifyBorrower() {
    string sid;
    cout << "\n👤 修改借阅者信息\n";
    cout << "请输入学号: "; getline(cin, sid);

    for (auto &b : Borrowers) {
        if (b.getStudentId() == sid) {
            string name, gender, phone, email;
            cout << "新姓名（回车跳过）: "; getline(cin, name);
            if (!name.empty()) b.setName(name);
            cout << "新性别（回车跳过）: "; getline(cin, gender);
            if (!gender.empty()) b.setGender(gender);
            cout << "新电话（回车跳过）: "; getline(cin, phone);
            if (!phone.empty()) b.setPhone(phone);
            cout << "新邮件（回车跳过）: "; getline(cin, email);
            if (!email.empty()) b.setEmail(email);

            cout << "✅ 信息修改成功！\n";
            pause();
            return;
        }
    }
    cout << "❌ 未找到该学号的借阅者！\n";
    pause();
}

void LibrarySystem::searchBorrower() {
    string keyword;
    cout << "\n👤 查询借阅者\n";
    cout << "请输入姓名或学号: "; getline(cin, keyword);

    bool found = false;
    for (const auto &b : Borrowers) {
        if (b.getName().find(keyword) != string::npos ||
            b.getStudentId().find(keyword) != string::npos) {
            b.display();
            found = true;
        }
    }
    if (!found) cout << "❌ 未找到匹配的借阅者！\n";
    pause();
}

void LibrarySystem::listAllBorrowers() {
    cout << "\n👤 所有借阅者（共" << Borrowers.size() << "人）\n";
    if (Borrowers.empty()) {
        cout << "暂无借阅者数据。\n";
    } else {
        for (const auto &b : Borrowers) b.display();
    }
    pause();
}

// ============================================
//  工作人员管理功能
// ============================================

void LibrarySystem::addStaff() {
    string name, sid, gender, phone, email;
    cout << "\n👥 添加工作人员\n";
    cout << "姓名: "; getline(cin, name);
    cout << "工号: "; getline(cin, sid);
    cout << "性别: "; getline(cin, gender);
    cout << "电话: "; getline(cin, phone);
    cout << "邮件: "; getline(cin, email);

    StaffMembers.push_back(Staff(name, sid, gender, phone, email));
    cout << "✅ 工作人员添加成功！\n";
    pause();
}

void LibrarySystem::deleteStaff() {
    string sid;
    cout << "\n👥 删除工作人员\n";
    cout << "请输入工号: "; getline(cin, sid);

    for (auto it = StaffMembers.begin(); it != StaffMembers.end(); ++it) {
        if (it->getStaffId() == sid) {
            StaffMembers.erase(it);
            cout << "✅ 工作人员删除成功！\n";
            pause();
            return;
        }
    }
    cout << "❌ 未找到该工号的工作人员！\n";
    pause();
}

void LibrarySystem::modifyStaff() {
    string sid;
    cout << "\n👥 修改工作人员信息\n";
    cout << "请输入工号: "; getline(cin, sid);

    for (auto &s : StaffMembers) {
        if (s.getStaffId() == sid) {
            string name, gender, phone, email;
            cout << "新姓名（回车跳过）: "; getline(cin, name);
            if (!name.empty()) s.setName(name);
            cout << "新性别（回车跳过）: "; getline(cin, gender);
            if (!gender.empty()) s.setGender(gender);
            cout << "新电话（回车跳过）: "; getline(cin, phone);
            if (!phone.empty()) s.setPhone(phone);
            cout << "新邮件（回车跳过）: "; getline(cin, email);
            if (!email.empty()) s.setEmail(email);

            cout << "✅ 信息修改成功！\n";
            pause();
            return;
        }
    }
    cout << "❌ 未找到该工号的工作人员！\n";
    pause();
}

void LibrarySystem::searchStaff() {
    string keyword;
    cout << "\n👥 查询工作人员\n";
    cout << "请输入姓名或工号: "; getline(cin, keyword);

    bool found = false;
    for (const auto &s : StaffMembers) {
        if (s.getName().find(keyword) != string::npos ||
            s.getStaffId().find(keyword) != string::npos) {
            s.display();
            found = true;
        }
    }
    if (!found) cout << "❌ 未找到匹配的工作人员！\n";
    pause();
}

void LibrarySystem::listAllStaff() {
    cout << "\n👥 所有工作人员（共" << StaffMembers.size() << "人）\n";
    if (StaffMembers.empty()) {
        cout << "暂无工作人员数据。\n";
    } else {
        for (const auto &s : StaffMembers) s.display();
    }
    pause();
}

// ============================================
//  借还操作
// ============================================

void LibrarySystem::borrowBook() {
    string sid, isbn;
    cout << "\n📖 借书\n";
    cout << "借阅者学号: "; getline(cin, sid);
    cout << "图书ISBN: "; getline(cin, isbn);

    // 查找借阅者
    Borrower* borrower = nullptr;
    for (auto &b : Borrowers) {
        if (b.getStudentId() == sid) { borrower = &b; break; }
    }
    if (!borrower) { cout << "❌ 未找到该借阅者！\n"; pause(); return; }

    // 查找图书
    for (auto &b : Books) {
        if (b.getIsbn() == isbn) {
            if (b.getIsBorrowed()) {
                cout << "❌ 该书已被借出！\n";
            } else {
                b.borrowIt();
                borrower->addBorrowedBook(isbn);
                cout << "✅ 借书成功！\n";
            }
            pause();
            return;
        }
    }
    cout << "❌ 未找到该图书！\n";
    pause();
}

void LibrarySystem::returnBook() {
    string sid, isbn;
    int days;
    cout << "\n📖 还书\n";
    cout << "借阅者学号: "; getline(cin, sid);
    cout << "图书ISBN: "; getline(cin, isbn);
    cout << "借阅天数: "; cin >> days;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 查找借阅者
    Borrower* borrower = nullptr;
    for (auto &b : Borrowers) {
        if (b.getStudentId() == sid) { borrower = &b; break; }
    }
    if (!borrower) { cout << "❌ 未找到该借阅者！\n"; pause(); return; }

    // 查找图书
    for (auto &b : Books) {
        if (b.getIsbn() == isbn) {
            if (!b.getIsBorrowed()) {
                cout << "❌ 该书未被借出！\n";
            } else {
                b.returnIt(days);
                borrower->removeBorrowedBook(isbn);
                if (days > 30) {
                    borrower->addViolation();
                    cout << "⚠️  借阅超时（" << days << "天），已记录违约！\n";
                }
                cout << "✅ 还书成功！\n";
            }
            pause();
            return;
        }
    }
    cout << "❌ 未找到该图书！\n";
    pause();
}

// ============================================
//  保存数据：将内存数据全部写入文件
// ============================================
void LibrarySystem::saveData() {
    cout << "\n📁 正在保存数据...\n";
    saveBooks();       // 保存图书
    saveBorrowers();   // 保存借阅者
    saveStaff();       // 保存工作人员
    cout << "✅ 数据保存完成！（共 "
         << Books.size() << "本图书，"
         << Borrowers.size() << "位借阅者，"
         << StaffMembers.size() << "位工作人员）\n";
    pause();
}

// ============================================
//  统计数据
// ============================================
int LibrarySystem::getBookCount() const { return Books.size(); }
int LibrarySystem::getBorrowerCount() const { return Borrowers.size(); }
int LibrarySystem::getStaffCount() const { return StaffMembers.size(); }
