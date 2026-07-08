#ifndef CAR_H   // 防止头文件重复包含
#define CAR_H   // 定义宏

#include <string>   // 使用 string 类型
#include <ctime>    // 使用 time() 和 ctime() 函数获取系统时间
using namespace std; // 使用标准命名空间

// ============================================
// Car 类 - 表示一辆车
// 体现面向对象的封装：把车的属性和操作放在一起
// v3 新增：车辆类型（长租车/临时车），白牌车免费
// ============================================
class Car {
private:
    // ---- 私有成员变量（外部不能直接访问） ----
    string plateNo;      // 车牌号，比如 "京A88888"
    string plateColor;   // 车牌颜色，比如 "蓝色"
    long entryTime;      // 入场时间（用秒数表示，从1970年开始的秒数）
    string side;         // 停在哪边："东边" 或 "西边"
    bool paid;           // 是否已缴费：true=已缴，false=未缴
    bool needCharging;   // 是否需要充电桩（绿牌车专用）：true=需要，false=不需要
    string carType;      // 车辆类型："临时车"（按时收费）或 "长租车"（月租车辆）

public:
    // ---- 构造函数 ----

    // 默认构造函数（什么都不做，给一个默认值）
    Car() {
        entryTime = 0;    // 入场时间设为0
        paid = false;     // 默认未缴费
        needCharging = false;  // 默认不需要充电桩
        carType = "临时车";   // 默认是临时车
    }

    // 有参数的构造函数（创建车对象时传入车牌号、颜色、位置、车辆类型、是否需要充电桩）
    // carType 默认 "临时车"，needCharge 默认 false
    Car(string no, string color, string s,
        string type = "临时车", bool needCharge = false) {
        plateNo = no;           // 设置车牌号
        plateColor = color;     // 设置车牌颜色
        side = s;               // 设置停车位置
        entryTime = time(0);    // 设置入场时间为当前系统时间（time(0)返回当前秒数）
        paid = false;           // 刚入场，未缴费
        carType = type;         // 设置车辆类型（长租车/临时车）
        needCharging = needCharge;  // 设置是否需要充电桩
    }

    // ---- 获取私有成员的值（Getter） ----

    string getPlateNo() { return plateNo; }        // 获取车牌号
    string getPlateColor() { return plateColor; }  // 获取车牌颜色
    long getEntryTime() { return entryTime; }      // 获取入场时间（秒数）
    string getSide() { return side; }              // 获取停车位置
    bool isPaid() { return paid; }                 // 获取缴费状态
    bool getNeedCharging() { return needCharging; } // 获取是否需要充电桩
    string getCarType() { return carType; }        // 获取车辆类型：长租车/临时车

    // ---- 设置私有成员的值（Setter） ----

    void setPaid(bool p) { paid = p; }             // 设置缴费状态
    void setNeedCharging(bool n) { needCharging = n; } // 设置是否需要充电桩
    void setCarType(string t) { carType = t; }     // 设置车辆类型：长租车/临时车

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
    // 新规则：
    //   - 停车不满15分钟 → 免费
    //   - 绿牌车（新能源）→ 打九折
    //   - 其他正常计费：3元/小时，不足1小时按分钟算（每分钟 3/60 = 0.05 元）
    double getFee() {
        double mins = getMinutes();    // 先获取停车分钟数

        // 规则1：停车不满15分钟，免费
        if (mins < 0) {
            return 0.0;
        }

        // 正常计费：分钟数 × 每分钟价格
        double fee = mins * (3.0 / 60.0);

        // 规则2：绿牌车（新能源电动车）停车费打九折
        if (plateColor == "绿色") {
            fee = fee * 0.9;           // 乘以0.9就是打九折
        }

        return fee;                    // 返回最终费用
    }

    // 获取绿牌车折扣的说明文字（用在出场界面显示）
    string getDiscountInfo() {
        double mins = getMinutes();    // 获取停车分钟数

        if (mins < 0) {
            return "（停车不满15分钟，免费）";  // 不满15分钟免费
        }

        if (plateColor == "绿色") {
            return "（绿牌新能源车，享受九折优惠）";  // 绿牌打折说明
        }

        return "";  // 普通车辆没有额外说明
    }
};

#endif // 结束头文件
