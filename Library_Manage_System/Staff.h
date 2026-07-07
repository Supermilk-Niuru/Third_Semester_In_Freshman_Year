// Staff.h —— 工作人员类的声明
// 公有继承 Person，比借阅者简单，只多了工号
#ifndef STAFF_H
#define STAFF_H
#include "Person.h"
#include <string>
using namespace std;

class Staff : public Person {
private:
    string StaffId;  // 工号

public:
    Staff() {}
    Staff(string n, string sid, string g, string p, string e);

    string getStaffId() const;
    void setStaffId(string sid);

    void display() const override;

    // 文件读写
    string toFileString() const;
    void fromFileString(const string &str);
};

#endif
