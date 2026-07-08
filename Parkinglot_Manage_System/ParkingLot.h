#ifndef PARKINGLOT_H  // 防止头文件重复包含
#define PARKINGLOT_H  // 定义宏

#include <iostream>   // 使用cout和endl输出信息
#include "Car.h"      // 引入Car类（停车场里要停Car对象）

// ============================================
// ParkingLot 类 - 表示一个停车场
// 管理车辆的入场、出场、收费、显示车位数等功能
// ============================================
class ParkingLot {
private:
    // ---- 车位信息 ----
    int eastTotal;       // 东边总车位数量
    int westTotal;       // 西边总车位数量
    int eastCount;       // 东边已停车辆数
    int westCount;       // 西边已停车辆数

    // ---- 充电桩信息 ----
    // 停车场东西两边各有25个充电桩
    int eastChargingTotal;   // 东边充电桩总数（固定25个）
    int westChargingTotal;   // 西边充电桩总数（固定25个）
    int eastChargingUsed;    // 东边已被占用的充电桩数
    int westChargingUsed;    // 西边已被占用的充电桩数

    // ---- 车辆存储 ----
    Car parkedCars[100];     // 用数组来存当前停在停车场里的车（最多100辆）
    int carCount;            // 当前停了多少辆车

    Car history[500];        // 用数组来存历史记录（已经离开的车）
    int historyCount;        // 有多少条历史记录

public:
    // ---- 构造函数：初始化停车场 ----
    // 默认东边50个位，西边50个位，各25个充电桩
    ParkingLot(int east = 50, int west = 50) {
        eastTotal = east;                // 设置东边总车位数
        westTotal = west;                // 设置西边总车位数
        eastCount = 0;                   // 刚开始东边没有车
        westCount = 0;                   // 刚开始西边没有车
        carCount = 0;                    // 刚开始没有车停着
        historyCount = 0;                // 刚开始没有历史记录

        // 充电桩初始化
        eastChargingTotal = 25;          // 东边25个充电桩
        westChargingTotal = 25;          // 西边25个充电桩
        eastChargingUsed = 0;            // 刚开始没有充电桩被占用
        westChargingUsed = 0;            // 刚开始没有充电桩被占用
    }

    // ---- 获取剩余车位 ----

    // 获取东边可用车位数 = 总位数 - 已停数量
    // 白牌车可以超量进入，所以如果出负数就显示0
    int getEastFree() {
        int free = eastTotal - eastCount;
        if (free < 0) return 0;  // 白牌车超量时显示0
        return free;
    }

    // 获取西边可用车位数 = 总位数 - 已停数量
    int getWestFree() {
        int free = westTotal - westCount;
        if (free < 0) return 0;  // 白牌车超量时显示0
        return free;
    }

    // 获取东边总车位数
    int getEastTotal() { return eastTotal; }

    // 获取西边总车位数
    int getWestTotal() { return westTotal; }

    // 获取当前停着的车数量
    int getCarCount() { return carCount; }

    // ---- 获取充电桩信息 ----

    // 获取东边可用充电桩数
    int getEastChargingFree() {
        return eastChargingTotal - eastChargingUsed;
    }

    // 获取西边可用充电桩数
    int getWestChargingFree() {
        return westChargingTotal - westChargingUsed;
    }

    // 获取东边充电桩总数
    int getEastChargingTotal() { return eastChargingTotal; }

    // 获取西边充电桩总数
    int getWestChargingTotal() { return westChargingTotal; }

    // ---- 车辆入场 ----
    // 返回值：
    //   0 = 入场成功
    //   1 = 黄牌车禁止入场（车身过大）
    //   2 = 对应侧车位已满
    //   3 = 对应侧充电桩已满
    //   4 = 其他未知错误
    int enterCar(Car car) {
        string color = car.getPlateColor();  // 获取车牌颜色
        string side = car.getSide();         // 获取停车位置

        // ======== 规则1：黄牌车禁止入场 ========
        // 黄牌车（大型货车、客车）车身过大，停车场不接收
        if (color == "黄色") {
            return 1;  // 返回1表示"黄牌车禁止入场"
        }

        // ======== 规则2：白牌车（特种车辆）特殊处理 ========
        // 白牌车（军车、警车、消防车等特种车辆）即使车位满了也让进
        bool isWhite = (color == "白色军用车辆");

        // ======== 检查车位 ========
        // 白牌车不用检查是否有空位（直接进）
        // 其他车辆需要检查对应侧是否还有空位
        if (!isWhite) {
            if (side == "东边" && eastCount >= eastTotal) {
                return 2;  // 东边车位满了
            }
            if (side == "西边" && westCount >= westTotal) {
                return 2;  // 西边车位满了
            }
        }

        // ======== 规则3：绿牌车检查充电桩 ========
        // 如果绿牌车需要充电桩，检查对应侧还有没有空闲充电桩
        bool needCharge = car.getNeedCharging();
        if (needCharge) {
            if (side == "东边" && getEastChargingFree() <= 0) {
                return 3;  // 东边充电桩已满
            }
            if (side == "西边" && getWestChargingFree() <= 0) {
                return 3;  // 西边充电桩已满
            }
        }

        // ======== 执行入场 ========

        // 更新车位计数（白牌车也会占用车位，可能导致 count > total）
        if (side == "东边") {
            eastCount++;  // 东边已停数量+1
        } else {
            westCount++;  // 西边已停数量+1
        }

        // 如果需要充电桩，更新充电桩占用计数
        if (needCharge) {
            if (side == "东边") {
                eastChargingUsed++;
            } else {
                westChargingUsed++;
            }
        }

        // 把车存入停车场数组
        parkedCars[carCount] = car;
        carCount++;            // 当前车辆数+1
        return 0;              // 返回0表示入场成功
    }

    // ---- 车辆出场 ----
    // 根据车牌号找到车并移出停车场
    // 返回找到的车，如果没找到则返回一个空的Car对象
    Car exitCar(string plateNo) {
        Car emptyCar;          // 用于表示没找到车
        for (int i = 0; i < carCount; i++) {
            if (parkedCars[i].getPlateNo() == plateNo) {
                // 找到了这辆车
                Car found = parkedCars[i];  // 把找到的车记下来

                // ======== 如果该车占用了充电桩，释放充电桩 ========
                if (found.getNeedCharging()) {
                    if (found.getSide() == "东边") {
                        eastChargingUsed--;   // 东边充电桩占用数-1
                    } else {
                        westChargingUsed--;   // 西边充电桩占用数-1
                    }
                }

                // 减少对应侧的车位计数
                if (found.getSide() == "东边") {
                    eastCount--;            // 东边少了一辆车
                } else {
                    westCount--;            // 西边少了一辆车
                }

                // 把后面的车往前移，填补空缺
                for (int j = i; j < carCount - 1; j++) {
                    parkedCars[j] = parkedCars[j + 1];
                }
                carCount--;                  // 当前车辆数-1

                // 把出场的车加入历史记录
                history[historyCount] = found;
                historyCount++;

                return found;  // 返回找到的车
            }
        }
        return emptyCar;  // 没找到，返回空车
    }

    // ---- 根据车牌号查找当前在停的车 ----
    // 返回车的下标，-1表示没找到
    int findCar(string plateNo) {
        for (int i = 0; i < carCount; i++) {
            if (parkedCars[i].getPlateNo() == plateNo) {
                return i;  // 找到了，返回下标
            }
        }
        return -1;  // 没找到
    }

    // 获取指定位置的车
    Car getCar(int index) {
        return parkedCars[index];
    }

    // 获取历史记录数量
    int getHistoryCount() { return historyCount; }

    // 获取指定历史记录
    Car getHistory(int index) {
        return history[index];
    }

    // ---- 显示所有在场车辆信息 ----
    void showParkedCars() {
        cout << "当前在场车辆：" << endl;
        cout << "----------------------------------------" << endl;
        if (carCount == 0) {
            cout << "  暂无车辆" << endl;
        } else {
            // 遍历所有停着的车并显示信息
            for (int i = 0; i < carCount; i++) {
                cout << "  " << (i + 1) << ". "
                     << "车牌：" << parkedCars[i].getPlateNo()
                     << "  颜色：" << parkedCars[i].getPlateColor();

                // 如果这辆绿牌车用了充电桩，加标记
                if (parkedCars[i].getNeedCharging()) {
                    cout << "  ⚡充电";
                }

                cout << "  位置：" << parkedCars[i].getSide()
                     << "  入场：" << parkedCars[i].getTimeStr()
                     << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }

    // ---- 显示历史记录 ----
    void showHistory() {
        cout << "历史停车记录：" << endl;
        cout << "----------------------------------------" << endl;
        if (historyCount == 0) {
            cout << "  暂无记录" << endl;
        } else {
            for (int i = 0; i < historyCount; i++) {
                cout << "  " << (i + 1) << ". "
                     << "车牌：" << history[i].getPlateNo()
                     << "  颜色：" << history[i].getPlateColor()
                     << "  位置：" << history[i].getSide()
                     << "  入场：" << history[i].getTimeStr()
                     << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
};

#endif // PARKINGLOT_H
