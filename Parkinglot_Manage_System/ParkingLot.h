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
    // ---- 私有成员变量 ----
    int eastTotal;       // 东边总车位数量
    int westTotal;       // 西边总车位数量
    int eastCount;       // 东边已停车辆数
    int westCount;       // 西边已停车辆数

    // 用一个数组来存当前停在停车场里的车（最多100辆）
    Car parkedCars[100];
    int carCount;        // 当前停了多少辆车

    // 用一个数组来存历史记录（已经离开的车）
    Car history[500];
    int historyCount;    // 有多少条历史记录

public:
    // ---- 构造函数：初始化停车场（默认东边50个位，西边50个位） ----
    ParkingLot(int east = 50, int west = 50) {
        eastTotal = east;        // 设置东边总车位数
        westTotal = west;        // 设置西边总车位数
        eastCount = 0;           // 刚开始东边没有车
        westCount = 0;           // 刚开始西边没有车
        carCount = 0;            // 刚开始没有车停着
        historyCount = 0;        // 刚开始没有历史记录
    }

    // ---- 获取剩余车位 ----

    // 获取东边可用车位数 = 总位数 - 已停数量
    int getEastFree() {
        return eastTotal - eastCount;
    }

    // 获取西边可用车位数 = 总位数 - 已停数量
    int getWestFree() {
        return westTotal - westCount;
    }

    // 获取东边总车位数
    int getEastTotal() { return eastTotal; }

    // 获取西边总车位数
    int getWestTotal() { return westTotal; }

    // 获取当前停着的车数量
    int getCarCount() { return carCount; }

    // ---- 车辆入场 ----
    // 返回值：true=入场成功，false=入场失败
    bool enterCar(Car car) {
        // 先检查还有没有空位
        if (car.getSide() == "东边") {
            if (eastCount >= eastTotal) {
                return false;  // 东边车位满了
            }
            eastCount++;       // 东边已停数量+1
        }
        else if (car.getSide() == "西边") {
            if (westCount >= westTotal) {
                return false;  // 西边车位满了
            }
            westCount++;       // 西边已停数量+1
        }

        // 把车存入停车场数组
        parkedCars[carCount] = car;
        carCount++;            // 当前车辆数+1
        return true;           // 入场成功
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
                     << "  颜色：" << parkedCars[i].getPlateColor()
                     << "  位置：" << parkedCars[i].getSide()
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
