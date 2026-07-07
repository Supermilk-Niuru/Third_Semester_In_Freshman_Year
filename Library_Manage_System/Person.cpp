// Person.cpp —— 人员基类的实现
#include "Person.h"
#include <iostream>
#include <sstream>
using namespace std;

Person::Person(string n, string g, string p, string e)
    : Name(n), Gender(g), Phone(p), Email(e) {}

string Person::getName() const { return Name; }
string Person::getGender() const { return Gender; }
string Person::getPhone() const { return Phone; }
string Person::getEmail() const { return Email; }

void Person::setName(string n) { Name = n; }
void Person::setGender(string g) { Gender = g; }
void Person::setPhone(string p) { Phone = p; }
void Person::setEmail(string e) { Email = e; }

void Person::display() const {
    cout << "姓名: " << Name << " | 性别: " << Gender
         << " | 电话: " << Phone << " | 邮件: " << Email;
}

// 将基类的四个字段序列化为"|"分隔字符串
string Person::personToFileString() const {
    return Name + "|" + Gender + "|" + Phone + "|" + Email;
}

// 从"|"分隔字符串解析基类的四个字段
void Person::personFromFileString(const string &str) {
    stringstream ss(str);
    string segment;
    int idx = 0;
    while (getline(ss, segment, '|')) {
        switch (idx) {
            case 0: Name = segment; break;
            case 1: Gender = segment; break;
            case 2: Phone = segment; break;
            case 3: Email = segment; break;
        }
        idx++;
    }
}
