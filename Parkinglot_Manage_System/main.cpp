// ============================================
// 停车场管理系统 - 主程序
// 功能：车辆入场、车辆出场（收费）、查看在场车辆、
//        查看历史记录、显示车位状态
// ============================================

#include <iostream>   // 用于 cin（键盘输入）和 cout（屏幕输出）
#include <cstdlib>    // 用于 system() 函数（清屏命令）
#ifdef _WIN32
    #include <windows.h>  // Windows系统：Sleep函数（暂停等待）
#else
    #include <unistd.h>   // Linux/Mac系统：sleep函数（暂停等待）
#endif

#include "ParkingLot.h"  // 引入停车场类（管理车位、车辆的入场出场）
#include "Car.h"         // 引入车辆类（存储车辆信息）

using namespace std;    // 使用标准命名空间，写 cout 不用写 std::cout

// ============================================
// 全局变量
// ============================================

// 创建一个停车场对象：东边50个车位，西边50个车位
ParkingLot lot(50, 50);

// ============================================
// 工具函数（清屏、暂停、按回车继续）
// ============================================

// 清屏函数：根据操作系统执行不同的清屏命令
void clearScreen() {
#ifdef _WIN32
    system("cls");   // Windows：用 cls 命令清屏
#else
    system("clear"); // Mac / Linux：用 clear 命令清屏
#endif
}

// 暂停函数：让程序等待几秒钟
// 参数 s：要等待的秒数
void pause(int s) {
#ifdef _WIN32
    Sleep(s * 1000);   // Windows 的 Sleep 单位是毫秒，要乘以1000
#else
    sleep(s);          // Mac / Linux 的 sleep 单位就是秒
#endif
}

// 等待用户按回车键后再继续
// 这样可以给用户时间看清屏幕上的信息
void pressEnter() {
    cout << endl;                          // 先换一行
    cout << "按回车键继续...";              // 提示用户
    cin.get();                             // 吃掉上次输入剩下的换行符
    cin.get();                             // 等待用户按下回车
}

// ============================================
// 显示顶部标题栏和车位状态
// 每个功能界面顶部都会调用这个函数
// ============================================
void showHeader() {
    clearScreen();   // 先把屏幕清干净

    // ---- 显示系统标题 ----
    cout << "========================================" << endl;
    cout << "       欢迎使用停车场管理系统" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // ---- 显示车位状态（东边和西边） ----
    cout << "  【车位状态】" << endl;
    cout << "  东边车位：" << lot.getEastFree() << " / " << lot.getEastTotal() << " 个可用";
    cout << "    ";
    cout << "西边车位：" << lot.getWestFree() << " / " << lot.getWestTotal() << " 个可用";
    cout << endl;
    cout << "  当前在场车辆：" << lot.getCarCount() << " 辆" << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// ============================================
// 功能 1：车辆入场
// 用户输入车牌号、车牌颜色、停车位置
// ============================================
void carEntry() {
    showHeader();   // 显示标题和车位信息

    cout << "  【车辆入场】" << endl;
    cout << "----------------------------------------" << endl;

    // ---- 输入车牌号 ----
    string plateNo;                    // 用来存用户输入的车牌号
    cout << "  请输入车牌号：";
    cin >> plateNo;                    // 从键盘读入车牌号

    // 检查这辆车是不是已经在停车场里了
    // findCar 返回 -1 代表没找到，其他值代表找到了
    if (lot.findCar(plateNo) != -1) {
        cout << endl;
        cout << "  【提示】该车牌号已在停车场内，不能重复入场！" << endl;
        pressEnter();                  // 等用户按回车
        return;                        // 返回到主菜单
    }

    // ---- 选择车牌颜色 ----
    int colorChoice;                   // 用户选的颜色编号
    string plateColor;                 // 用户选的颜色名称（中文）

    cout << "  请选择车牌颜色：" << endl;
    cout << "    1. 蓝色" << endl;
    cout << "    2. 黄色" << endl;
    cout << "    3. 白色军用车辆" << endl;
    cout << "    4. 港牌" << endl;
    cout << "    5. 澳门牌" << endl;
    cout << "    6. 台湾牌" << endl;
    cout << "  请输入编号（1-6）：";
    cin >> colorChoice;

    // 用 if-else 把数字转成中文颜色名
    if (colorChoice == 1) {
        plateColor = "蓝色";
    } else if (colorChoice == 2) {
        plateColor = "黄色";
    } else if (colorChoice == 3) {
        plateColor = "白色军用车辆";
    } else if (colorChoice == 4) {
        plateColor = "港牌";
    } else if (colorChoice == 5) {
        plateColor = "澳门牌";
    } else if (colorChoice == 6) {
        plateColor = "台湾牌";
    } else {
        plateColor = "其他";           // 输入了 1-6 以外的数字
    }

    // ---- 选择停车位置（东边 / 西边） ----
    int sideChoice;                    // 用户选的位置编号
    string side;                       // 位置名称

    cout << "  请选择停车位置：" << endl;
    cout << "    1. 东边" << endl;
    cout << "    2. 西边" << endl;
    cout << "  请输入编号（1-2）：";
    cin >> sideChoice;

    if (sideChoice == 1) {
        side = "东边";                 // 用户选了东边
        // 检查东边还有没有空位
        if (lot.getEastFree() <= 0) {
            cout << endl;
            cout << "  【提示】东边车位已满！请选择西边。" << endl;
            pressEnter();
            return;                    // 车位满了，不能入场
        }
    } else {
        side = "西边";                 // 用户选了西边
        // 检查西边还有没有空位
        if (lot.getWestFree() <= 0) {
            cout << endl;
            cout << "  【提示】西边车位已满！请选择东边。" << endl;
            pressEnter();
            return;                    // 车位满了，不能入场
        }
    }

    // ---- 创建车辆对象，执行入场 ----
    // 用输入的信息创建一辆新车（入场时间自动设为现在）
    Car newCar(plateNo, plateColor, side);

    // 调停车场对象的 enterCar 方法，让车入场
    bool ok = lot.enterCar(newCar);

    // 显示入场结果
    if (ok == true) {
        cout << endl;
        cout << "  ✅ 车辆入场成功！" << endl;
        cout << "     车牌号：" << plateNo << endl;
        cout << "     车牌颜色：" << plateColor << endl;
        cout << "     停车位置：" << side << endl;
        cout << "     入场时间：" << newCar.getTimeStr() << endl;
    } else {
        cout << endl;
        cout << "  ❌ 入场失败，请稍后重试。" << endl;
    }

    pressEnter();   // 按回车回到主菜单
}

// ============================================
// 功能 2：车辆出场 + 缴费
// 计算停车时长、显示费用、确认收费出场
// ============================================
void carExit() {
    showHeader();   // 显示标题和车位信息

    cout << "  【车辆出场 / 缴费】" << endl;
    cout << "----------------------------------------" << endl;

    // ---- 输入要出场的车牌号 ----
    string plateNo;
    cout << "  请输入出场车辆的车牌号：";
    cin >> plateNo;

    // 在停车场里找这辆车
    int index = lot.findCar(plateNo);

    if (index == -1) {
        // -1 表示没找到这辆车
        cout << endl;
        cout << "  【提示】未找到该车牌号的车辆！" << endl;
        pressEnter();
        return;  // 返回主菜单
    }

    // ---- 取出车辆信息并显示 ----
    Car car = lot.getCar(index);   // 通过下标获取车辆对象

    cout << endl;
    cout << "  ========== 车辆信息 ==========" << endl;
    cout << "  车牌号：" << car.getPlateNo() << endl;
    cout << "  车牌颜色：" << car.getPlateColor() << endl;
    cout << "  停车位置：" << car.getSide() << endl;
    cout << "  入场时间：" << car.getTimeStr() << endl;
    cout << "  停车时长：" << car.getMinutes() << " 分钟" << endl;
    cout << "  ===============================" << endl;
    cout << endl;

    // ---- 计算并显示费用 ----
    // 收费标准：3元/小时，不足1小时按分钟计费（3÷60=0.05元/分钟）
    double fee = car.getFee();

    cout << "  💰 应缴费用：";
    printf("%.2f", fee);               // 用printf保留2位小数
    cout << " 元" << endl;
    cout << "  （收费标准：3元/小时，不足1小时按分钟计费）" << endl;
    cout << endl;

    // ---- 确认缴费 ----
    cout << "  是否确认缴费出场？（1=是，2=否）：";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // 用户确认缴费 → 把车从停车场移出
        Car exited = lot.exitCar(plateNo);   // 执行出场（从数组移除）
        exited.setPaid(true);                 // 标记已缴费

        cout << endl;
        cout << "  ==========================================" << endl;
        cout << "  ✅ 缴费成功！" << endl;
        cout << endl;

        // ----- 用户要求的出场格式 -----
        cout << "    临时车 " << plateNo << " 已缴费 一路顺风！" << endl;
        // -------------------------------

        cout << endl;
        cout << "  缴费金额：";
        printf("%.2f", fee);
        cout << " 元" << endl;
        cout << "  停车时长：" << car.getMinutes() << " 分钟" << endl;
        cout << "  ==========================================" << endl;
    } else {
        // 用户取消缴费
        cout << endl;
        cout << "  已取消出场操作，车辆仍在场内。" << endl;
    }

    pressEnter();
}

// ============================================
// 功能 3：查看在场车辆列表
// ============================================
void showParked() {
    showHeader();
    lot.showParkedCars();   // 调停车场对象的显示方法
    pressEnter();
}

// ============================================
// 功能 4：查看历史停车记录
// ============================================
void showHistory() {
    showHeader();
    lot.showHistory();      // 调停车场对象的显示历史方法
    pressEnter();
}

// ============================================
// 显示主菜单
// ============================================
void showMenu() {
    cout << "  【主菜单】" << endl;
    cout << "----------------------------------------" << endl;
    cout << "    1. 🚗 车辆入场" << endl;
    cout << "    2. 🚙 车辆出场（缴费）" << endl;
    cout << "    3. 📋 在场车辆" << endl;
    cout << "    4. 📜 停车记录" << endl;
    cout << "    5. ❌ 退出系统" << endl;
    cout << "----------------------------------------" << endl;
    cout << "  请输入您的选择（1-5）：";
}

// ============================================
// 主函数 —— 程序的起点
// ============================================
int main() {
    int choice;   // 存放用户在菜单中的选择

    // 无限循环，只有选"退出"才会结束
    while (true) {
        showHeader();   // 先刷新屏幕、显示标题和车位信息
        showMenu();     // 再显示菜单选项

        cin >> choice;  // 读取用户输入的数字

        // 根据选择执行不同的功能
        if (choice == 1) {
            carEntry();      // 功能1：车辆入场
        }
        else if (choice == 2) {
            carExit();       // 功能2：车辆出场 + 缴费
        }
        else if (choice == 3) {
            showParked();    // 功能3：查看在场车辆
        }
        else if (choice == 4) {
            showHistory();   // 功能4：查看历史记录
        }
        else if (choice == 5) {
            // 退出系统
            cout << endl;
            cout << "  感谢使用停车场管理系统，再见！" << endl;
            pause(1);         // 等1秒
            return 0;         // 正常结束程序
        }
        else {
            // 输入了 1-5 以外的数字
            cout << endl;
            cout << "  【提示】输入有误，请选择 1-5 之间的数字！" << endl;
            pause(1);         // 等1秒后重新显示菜单
        }
    }

    return 0;   // 程序结束
}
