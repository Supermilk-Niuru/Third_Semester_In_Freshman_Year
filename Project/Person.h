// Person.h —— 人员基类的声明
// Borrower 和 Staff 都继承自本类，复用姓名、性别、电话、邮件四个公共字段
#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person {
private:  // 私有成员：子类也不能直接访问，体现封装
    string Name;
    string Gender;
    string Phone;
    string Email;

public:
    Person() {}
    Person(string n, string g, string p, string e);

    // ---- Getter ----
    string getName() const;
    string getGender() const;
    string getPhone() const;
    string getEmail() const;

    // ---- Setter ----
    void setName(string n);
    void setGender(string g);
    void setPhone(string p);
    void setEmail(string e);

    // 虚函数：允许子类重写，实现多态
    virtual void display() const;
    virtual ~Person() {}

    // 文件读写辅助（基类部分）
    string personToFileString() const;
    void personFromFileString(const string &str);
};

#endif
