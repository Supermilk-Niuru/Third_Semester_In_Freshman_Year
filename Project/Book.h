// Book.h —— 图书类的声明
#ifndef BOOK_H           // 如果没有定义过 BOOK_H
#define BOOK_H           // 就定义 BOOK_H（防止重复包含）
#include <string>        // 使用 string 类型
using namespace std;

// 图书类：封装了一本书的所有信息和操作
class Book {
private:
    string Title;        // 图书名称
    string Isbn;         // ISBN号（唯一标识）
    string Author;       // 作者
    string Publisher;    // 出版社
    int PrintCount;      // 印次
    bool IsBorrowed;     // 是否被借阅
    int BorrowDuration;  // 被借阅时长（天）

public:
    // 构造函数
    Book();
    Book(string t, string isbn, string a, string pub, int pc);

    // ---- Getter ----
    string getTitle() const;
    string getIsbn() const;
    string getAuthor() const;
    string getPublisher() const;
    int getPrintCount() const;
    bool getIsBorrowed() const;
    int getBorrowDuration() const;

    // ---- Setter ----
    void setTitle(string t);
    void setIsbn(string isbn);
    void setAuthor(string a);
    void setPublisher(string p);
    void setPrintCount(int pc);

    // 借还操作
    void borrowIt();               // 标记为已借出
    void returnIt(int days);       // 标记为可借阅，记录时长

    // 显示图书信息
    void display() const;

    // 文件读写：将对象转为"|"分隔字符串 / 从"|"分隔字符串解析
    string toFileString() const;   // 写出到文件
    void fromFileString(const string &str);  // 从文件读入
};

#endif  // BOOK_H 结束
