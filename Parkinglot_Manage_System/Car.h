#ifndef CAR_H   // 防止头文件重复包含
#define CAR_H   // 定义宏

#include <string>   // 使用 string 类型
#include <ctime>    // 使用 time() 和 ctime() 函数获取系统时间
using namespace std; // 使用标准命名空间

// ============================================
// Car 类 - 表示一辆车
// 体现面向对象的封装：把车的属性和操作放在一起
// ============================================
class Car {
private:
    // ---- 私有成员变量（外部不能直接访问） ----
    string plateNo;      // 车牌号，比如 "京A88888"
    string plateColor;   // 车牌颜色，比如 "蓝色"
    long entryTime;      // 入场时间（用秒数表示，从1970年开始的秒数）
    string side;         // 停在哪边："东边" 或 "西边"
    bool paid;           // 是否已缴费：true=已缴，false=未缴

public:
    // ---- 构造函数 ----

    // 默认构造函数（什么都不做，给一个默认值）
    Car() {
        entryTime = 0;    // 入场时间设为0
        paid = false;     // 默认未缴费
    }

    // 有参数的构造函数（创建车对象时传入车牌号、颜色、位置）
    Car(string no, string color, string s) {
        plateNo = no;           // 设置车牌号
        plateColor = color;     // 设置车牌颜色
        side = s;               // 设置停车位置
        entryTime = time(0);    // 设置入场时间为当前系统时间（time(0)返回当前秒数）
        paid = false;           // 刚入场，未缴费
    }

    // ---- 获取私有成员的值（Getter） ----

    string getPlateNo() { return plateNo; }        // 获取车牌号
    string getPlateColor() { return plateColor; }  // 获取车牌颜色
    long getEntryTime() { return entryTime; }      // 获取入场时间（秒数）
    string getSide() { return side; }              // 获取停车位置
    bool isPaid() { return paid; }                 // 获取缴费状态

    // ---- 设置私有成员的值（Setter） ----

    void setPaid(bool p) { paid = p; }             // 设置缴费状态

    // ---- 工具方法 ----

    // 获取入场时间的字符串格式（比如 "2026-07-08 14:30:25"）
    string getTimeStr() {
        time_t t = entryTime;          // 把long类型转成time_t类型
        char* str = ctime(&t);         // ctime()把时间转成字符串，如 "Wed Jul  8 14:30:25 2026"
        string s(str);                 // 转成C++的string
        return s.substr(0, s.length() - 1); // 去掉末尾的换行符
    }

    // 计算已经停了多长时间（返回分钟数）
    // 用当前时间减去入场时间
    double getMinutes() {
        long now = time(0);            // 获取当前时间（秒数）
        long diff = now - entryTime;   // 时间差（秒数）
        return diff / 60.0;            // 转换成分钟
    }

    // 计算停车费用
    // 收费标准：3元/小时，不足1小时按分钟算（每分钟 3/60 = 0.05 元）
    double getFee() {
        double mins = getMinutes();    // 先获取停车分钟数
        return mins * (3.0 / 60.0);    // 分钟数 × 每分钟价格
    }
};

#endif // 结束头文件
