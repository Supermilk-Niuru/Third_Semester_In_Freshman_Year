#ifndef CAR_H   
#define CAR_H   
#include <string>  
#include <ctime>   
using namespace std; 
//车辆类：主要实现车辆信息存储的功能
class Car {
private:
    string plateNo;      // 车牌号
    string plateColor;   // 车牌颜色
    long entryTime;      // 入场时间
    string side;         // 停的边
    bool paid;           //是否缴费
    bool needCharging;   //是否充电
    string carType;      //车类型
public:
    //默认构造函数
    Car() {
        entryTime = 0;   
        paid = false;    
        needCharging = false;  
        carType = "临时车";   
    }
    Car(string no, string color, string s,
        string type = "临时车", bool needCharge = false) {
        plateNo = no;           
        plateColor = color;     
        side = s;               
        entryTime = time(0);    // 设置入场时间为当前系统时间（time(0)返回当前秒数）
        paid = false;           // 刚入场，未缴费
        carType = type;         // 设置车辆类型（长租车/临时车）
        needCharging = needCharge;  
    }
    //获取私有成员的值Getter
    string getPlateNo() { return plateNo; }        
    string getPlateColor() { return plateColor; } 
    long getEntryTime() { return entryTime; }      
    string getSide() { return side; }              
    bool isPaid() { return paid; }                 
    bool getNeedCharging() { return needCharging; } 
    string getCarType() { return carType; }        
    //设置私有成员的值Setter
    void setPaid(bool p) { paid = p; }             
    void setNeedCharging(bool n) { needCharging = n; } 
    void setCarType(string t) { carType = t; } 
    // 获取入场时间
    string getTimeStr() {
        time_t t = entryTime;          // 把long类型强制转成time_t类型
        char* str = ctime(&t);         // ctime()把时间转成字符串
        string s(str);                 // 强制转成string
        return s.substr(0, s.length() - 1); // 去掉末尾的换行符
    }
    // 计算停车时间
    double getMinutes() {
        long now = time(0);            // 获取当前时间（秒数）
        long diff = now - entryTime;   // 时间差（秒数）
        return diff / 60.0;            // 转换成分钟
    }
    // 计算停车费用
    double getFee() {
        double mins = getMinutes();    // 先获取停车分钟数
        // 规则1：停车不满15分钟，免费。为方便调试，设置成仅停车场就收费
        
        if (mins < 0) {
            return 0.0;
        }

        // 正常计费：分钟数 × 每分钟价格。没有不足1小时按1小时计算的规则，更人性化管理
        double fee = mins * (3.0 / 60.0);
        // 规则2：绿牌车（新能源电动车）停车费打九折
        if (plateColor == "绿色") {
            fee = fee * 0.9;           
        }
        return fee;                    // 返回最终费用
    }
    // 针对绿牌车折扣的说明文字
    string getDiscountInfo() {
        double mins = getMinutes();    // 获取停车分钟数

        if (mins < 0) {
            return "（停车不满15分钟，免费）";  // 不满15分钟免费
        }
        if (plateColor == "绿色") {
            return "（绿牌新能源车，享受九折优惠）";  // 绿牌打折说明
        }

        return "";  // 对于普通车辆没有额外说明
    }
};
#endif // 结束头文件
