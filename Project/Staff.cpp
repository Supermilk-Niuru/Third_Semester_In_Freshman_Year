// Staff.cpp —— 工作人员类的实现
#include "Staff.h"
#include <iostream>
#include <sstream>
using namespace std;

Staff::Staff(string n, string sid, string g, string p, string e)
    : Person(n, g, p, e), StaffId(sid) {}

string Staff::getStaffId() const { return StaffId; }
void Staff::setStaffId(string sid) { StaffId = sid; }

void Staff::display() const {
    Person::display();
    cout << " | 工号: " << StaffId << endl;
}

// ---- 文件读写 ----
// 格式：姓名|性别|电话|邮件|工号
string Staff::toFileString() const {
    return personToFileString() + "|" + StaffId;
}

void Staff::fromFileString(const string &str) {
    stringstream ss(str);
    string segment;
    int idx = 0;
    while (getline(ss, segment, '|')) {
        switch (idx) {
            case 0: setName(segment); break;
            case 1: setGender(segment); break;
            case 2: setPhone(segment); break;
            case 3: setEmail(segment); break;
            case 4: StaffId = segment; break;
        }
        idx++;
    }
}
