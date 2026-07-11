#ifndef PARKINGLOT_H  
#define PARKINGLOT_H
#include <iostream>   
#include "Car.h" 
//实现停车场内部管理，车辆进场，出场缴费的功能
class ParkingLot {
private:
    //车位信息
    int eastTotal;       
    int westTotal;       
    int eastCount;       
    int westCount;      
    //充电桩信息
    int eastChargingTotal;   
    int westChargingTotal;   
    int eastChargingUsed;    
    int westChargingUsed; 

    //车辆信息存储，存储类型car 
    Car parkedCars[100];     
    int carCount;        
    //停车场停车历史信息存储，存储类型car
    Car history[500];        
    int historyCount;       
public:
    //初始化停车场内部信息
    ParkingLot(int east = 50, int west = 50) {
        //停车位初始化
        eastTotal = east;                
        westTotal = west;                
        eastCount = 0;                   
        westCount = 0;                  
        carCount = 0;                    
        historyCount = 0;                
        // 充电桩初始化
        eastChargingTotal = 25;          
        westChargingTotal = 25;          
        eastChargingUsed = 0;            
        westChargingUsed = 0;           
    }
    //剩余车位获取
    // 白牌车可以超量进入，所以如果出负数就显示0
    int getEastFree() {
        int free = eastTotal - eastCount;
        if (free < 0) return 0;  // 白牌车超量时显示0
        return free;
    }
    // 获取西边可用车位数
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
    
    //充电桩信息获取
    //获取东边可用充电桩数
    int getEastChargingFree() {
        return eastChargingTotal - eastChargingUsed;
    }
    //获取西边可用充电桩数
    int getWestChargingFree() {
        return westChargingTotal - westChargingUsed;
    }
    //获取东边充电桩总数
    int getEastChargingTotal() { return eastChargingTotal; }
    //获取西边充电桩总数
    int getWestChargingTotal() { return westChargingTotal; }

    //车辆入场
    //0 = 入场成功
    //1 = 黄牌车禁止入场
    //2 = 对应侧车位已满
    //3 = 对应侧充电桩已满
    //4 = 其他未知错误
    int enterCar(Car car) {
        string color = car.getPlateColor();  // 车牌颜色
        string side = car.getSide();         // 停车位置,东边还是西边

        //规则1：黄牌车禁止入场 
        if (color == "黄色") {
            return 1;  //1表示"黄牌车禁止入场"
        }

        //规则2：白牌车（特种车辆）特殊处理
        bool isWhite = (color == "白色军用车辆");

        // 检查车位
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
        //规则3：绿牌车检查充电桩
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
        //车辆入场
        // 更新车位计数（白牌车也会占用剩余车位，会导致 count > total）
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
    //车辆出场
    // 根据车牌号找到车并移出停车场
    // 返回找到的车，如果没找到则返回一个空的Car对象
    Car exitCar(string plateNo) {
        Car emptyCar;          // 用于表示没找到车
        //遍历停车存放数组
        for (int i = 0; i < carCount; i++) {
            if (parkedCars[i].getPlateNo() == plateNo) {
                // 找到了车
                Car found = parkedCars[i];  // 把找到的车记下来
                //充电桩数量管理
                if (found.getNeedCharging()) {
                    if (found.getSide() == "东边") {
                        eastChargingUsed--;   
                    } else {
                        westChargingUsed--;   
                    }
                }
                // 减少相应边侧的车位计数
                if (found.getSide() == "东边") {
                    eastCount--;            
                } else {
                    westCount--;           
                }
                // 把后面的车往前移，填补空位
                for (int j = i; j < carCount - 1; j++) {
                    parkedCars[j] = parkedCars[j + 1];
                }
                carCount--;                 
                // 把出场的车加入历史记录
                history[historyCount] = found;
                historyCount++;
                return found;  // 返回找到的车
            }
        }
        return emptyCar;  // 没找到，返回空车
    }
    // 根据车牌号查找当前在停的车 
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

    //显示在场车辆信息
    void showParkedCars() {
        cout << "当前在场车辆：" << endl;
        cout << "------------------------------------------------------------" << endl;
        if (carCount == 0) {
            cout << "  暂无车辆" << endl;
        } else {
            // 遍历所有停着的车并显示信息
            for (int i = 0; i < carCount; i++) {
                cout << "  " << (i + 1) << ". "
                     << "车牌：" << parkedCars[i].getPlateNo()
                     << "  颜色：" << parkedCars[i].getPlateColor()
                     << "  类型：" << parkedCars[i].getCarType();

                // 如果这辆绿牌车用了充电桩，加标记
                if (parkedCars[i].getNeedCharging()) {
                    cout << " ⚡";
                }

                cout << "  " << parkedCars[i].getSide()
                     << "  入场：" << parkedCars[i].getTimeStr()
                     << endl;
            }
        }
        cout << "------------------------------------------------------------" << endl;
    }

    //显示历史记录
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
