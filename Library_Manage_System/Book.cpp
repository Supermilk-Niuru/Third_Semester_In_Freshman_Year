// Book.cpp —— 图书类的实现
#include "Book.h"          // 引入自己的头文件
#include <iostream>        // 控制台输出
#include <sstream>         // 字符串流（用于拆分"|"分隔的文本）
using namespace std;

// 无参构造函数：所有成员设默认值
Book::Book() : PrintCount(0), IsBorrowed(false), BorrowDuration(0) {}

// 有参构造函数：用传入的参数初始化
Book::Book(string t, string isbn, string a, string pub, int pc)
    : Title(t), Isbn(isbn), Author(a), Publisher(pub),
      PrintCount(pc), IsBorrowed(false), BorrowDuration(0) {}

// ---- Getter 实现 ----
string Book::getTitle() const { return Title; }
string Book::getIsbn() const { return Isbn; }
string Book::getAuthor() const { return Author; }
string Book::getPublisher() const { return Publisher; }
int Book::getPrintCount() const { return PrintCount; }
bool Book::getIsBorrowed() const { return IsBorrowed; }
int Book::getBorrowDuration() const { return BorrowDuration; }

// ---- Setter 实现 ----
void Book::setTitle(string t) { Title = t; }
void Book::setIsbn(string isbn) { Isbn = isbn; }
void Book::setAuthor(string a) { Author = a; }
void Book::setPublisher(string p) { Publisher = p; }
void Book::setPrintCount(int pc) { PrintCount = pc; }

// 借书：标记为已借出
void Book::borrowIt() { IsBorrowed = true; }

// 还书：标记为可借阅，记录借阅天数
void Book::returnIt(int days) { IsBorrowed = false; BorrowDuration = days; }

// 显示图书完整信息
void Book::display() const {
    cout << "书名: " << Title << " | ISBN: " << Isbn
         << " | 作者: " << Author << " | 出版社: " << Publisher
         << " | 印次: " << PrintCount
         << " | 状态: " << (IsBorrowed ? "已借出" : "可借阅");
    if (IsBorrowed) cout << " | 借阅时长: " << BorrowDuration << "天";
    cout << endl;
}

// ---- 文件读写 ----

// toFileString: 将对象序列化为一行文本，用"|"分隔各字段
// 格式：书名|ISBN|作者|出版社|印次|是否借出(0/1)|借阅时长
string Book::toFileString() const {
    return Title + "|" + Isbn + "|" + Author + "|" + Publisher + "|"
         + to_string(PrintCount) + "|" + (IsBorrowed ? "1" : "0") + "|"
         + to_string(BorrowDuration);
}

// fromFileString: 从一行"|"分隔的文本解析出各字段
void Book::fromFileString(const string &str) {
    stringstream ss(str);  // 用字符串流逐段读取
    string segment;
    int idx = 0;           // 第几段（0~6）
    while (getline(ss, segment, '|')) {
        switch (idx) {
            case 0: Title = segment; break;
            case 1: Isbn = segment; break;
            case 2: Author = segment; break;
            case 3: Publisher = segment; break;
            case 4: PrintCount = stoi(segment); break;
            case 5: IsBorrowed = (segment == "1"); break;
            case 6: BorrowDuration = stoi(segment); break;
        }
        idx++;
    }
}
