#include <iostream>   
#include <cstdlib>
#ifdef _WIN32
    #include <windows.h> 
#else
    #include <unistd.h> 
#endif
#include "ParkingLot.h"  
#include "Car.h"

using namespace std;

//创建一个停车场对象：东边50个车位，西边50个车位
ParkingLot lot(50, 50);

//清屏函数
void clearScreen() {
#ifdef _WIN32
    system("cls");   
#else
    system("clear"); 
#endif
}

// 暂停函数
void pause(int s) {
#ifdef _WIN32
    Sleep(s * 1000);   // Windows 的 Sleep 单位是毫秒，要乘以1000
#else
    sleep(s);          // Mac / Linux 的 sleep 单位就是秒
#endif
}

// 等待用户按回车键后再继续
void pressEnter() {
    cout << endl;                          
    cout << "按回车键继续...";              
    cin.get();                             // 吃掉上次输入剩下的换行符
    cin.get();                            
}


// 显示顶部标题栏和车位状态,每个函数使用前需要调用，让用户明白哪些是必须的
void showHeader() {
    clearScreen();   // 屏幕初始化
    cout << "========================================" << endl;
    cout << "       欢迎使用停车场管理系统" << endl;
    cout << "========================================" << endl;
    cout << endl;

    //显示车位状态
    cout << "  【车位状态】" << endl;
    cout << "  东边车位：" << lot.getEastFree() << " / " << lot.getEastTotal() << " 个可用";
    cout << "    ";
    cout << "西边车位：" << lot.getWestFree() << " / " << lot.getWestTotal() << " 个可用";
    cout << endl;

    //显示充电桩状态
    cout << "  东边充电桩：" << lot.getEastChargingFree() << " / " << lot.getEastChargingTotal() << " 个空闲";
    cout << "    ";
    cout << "西边充电桩：" << lot.getWestChargingFree() << " / " << lot.getWestChargingTotal() << " 个空闲";
    cout << endl;

    cout << "  当前在场车辆：" << lot.getCarCount() << " 辆" << endl;
    cout << "========================================" << endl;
    cout << endl;
}
// 功能 1：车辆入场函数
void carEntry() {
    showHeader();   // 显示标题和车位信息

    cout << "  【车辆入场】" << endl;
    cout << "----------------------------------------" << endl;

    // 输入车牌号
    string plateNo;                    // 存用户输入的车牌号
    cout << "  请输入车牌号：";
    cin >> plateNo;                    // 从键盘读入车牌号

    // 检查这辆车在停车场是否存在
    // findCar 返回 -1 代表没找到，其他值代表找到了
    if (lot.findCar(plateNo) != -1) {
        cout << endl;
        cout << "  【提示】该车牌号已在停车场内，不能重复入场！" << endl;
        pressEnter();                  // 用户按回车进行下一步
        return;                        // 返回到主菜单
    }
    //车牌颜色
    int colorChoice;                   
    string plateColor;                 //为避免输入中文麻烦，采用数字代替颜色的方式

    cout << "  请选择车牌颜色：" << endl;
    cout << "    1. 蓝色" << endl;
    cout << "    2. 黄色" << endl;
    cout << "    3. 白色军用车辆" << endl;
    cout << "    4. 港牌" << endl;
    cout << "    5. 澳门牌" << endl;
    cout << "    6. 台湾牌" << endl;
    cout << "    7. 绿色（新能源）" << endl;
    cout << "  请输入编号（1-7）：";
    cin >> colorChoice;

    // 将颜色对应的编号转成中文，方便显示
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
    } else if (colorChoice == 7) {
        plateColor = "绿色";           
    } else {
        plateColor = "其他";           // 输入了 1-7 以外的数字
    }
    // 规则检查：黄牌车禁止入场
    if (plateColor == "黄色") {
        cout << endl;
        cout << "  ⛔ 黄牌车禁止入场！" << endl;
        cout << "  原因：黄牌车（大型车辆）车身过大，本停车场不接收。" << endl;
        pressEnter();
        return;  // 返回主菜单，不能入场
    }
    // 绿牌车特殊：询问是否需要充电桩
    bool needCharging = false;  // 默认不需要充电桩
    
    if (plateColor == "绿色") {
        // 显示当前充电桩空闲情况
        cout << endl;
        cout << "  ⚡ 当前充电桩空闲情况：" << endl;
        cout << "     东边：" << lot.getEastChargingFree()
             << " / " << lot.getEastChargingTotal() << " 个空闲" << endl;
        cout << "     西边：" << lot.getWestChargingFree()
             << " / " << lot.getWestChargingTotal() << " 个空闲" << endl;
        cout << endl;
        //是否需要充电桩
        cout << "  是否需要使用充电桩？（1=需要，2=不需要）：";
        int chargeChoice;
        cin >> chargeChoice;
        if (chargeChoice == 1) {
            needCharging = true;  // 绿牌车需要充电桩
        }
        cout << endl;
    }
    // 选择车辆类型（长租车 / 临时车）
    int typeChoice;                      
    string carType;                      //为避免用户输入中文麻烦，采用和颜色一样的处理方式
    cout << "  请选择车辆类型：" << endl;
    cout << "    1. 临时车（按时收费）" << endl;
    cout << "    2. 长租车（月保车辆）" << endl;
    cout << "  请输入编号（1-2）：";
    cin >> typeChoice;
    if (typeChoice == 2) {
        carType = "长租车";              
        cout << endl;
        cout << "  ℹ️  长租月保车辆，出场时不另外收费。" << endl;
    } else {
        carType = "临时车";             
    }

    //选择停车位置（东边 / 西边）
    int sideChoice;                    
    string side;                       
    cout << "  请选择停车位置：" << endl;
    cout << "    1. 东边" << endl;
    cout << "    2. 西边" << endl;
    cout << "  请输入编号（1-2）：";
    cin >> sideChoice;
    if (sideChoice == 1) {
        side = "东边";                 
    } else {
        side = "西边";                
    }

    
    // 车位检查：白牌车除外
    if (plateColor != "白色军用车辆") {
        // 普通车辆需要检查车位
        if (side == "东边" && lot.getEastFree() <= 0) {
            cout << endl;
            cout << "  【提示】东边车位已满！" << endl;
            pressEnter();
            return;                    // 车位满了，不能入场，重新选择另外一边
        }
        if (side == "西边" && lot.getWestFree() <= 0) {
            cout << endl;
            cout << "  【提示】西边车位已满！" << endl;
            pressEnter();
            return;                    // 车位满了，不能入场
        }
    } else {
        // 白牌车特殊提示
        cout << endl;
        cout << "  ℹ️  白牌特种车辆，不受车位限制，允许入场。" << endl;
    }
    // 充电桩检查
    // 如果绿牌车需要充电桩，检查对应侧是否还有空闲充电桩
    if (needCharging) {
        if (side == "东边" && lot.getEastChargingFree() <= 0) {
            cout << endl;
            cout << "  【提示】东边充电桩已满！无法提供充电服务。" << endl;
            cout << "  请选择西边，或不使用充电桩。" << endl;
            pressEnter();
            return;
        }
        if (side == "西边" && lot.getWestChargingFree() <= 0) {
            cout << endl;
            cout << "  【提示】西边充电桩已满！无法提供充电服务。" << endl;
            cout << "  请选择东边，或不使用充电桩。" << endl;
            pressEnter();
            return;
        }
    }

    //创建车辆对象，执行入场。将刚输入的参数传给newcar
    Car newCar(plateNo, plateColor, side, carType, needCharging);

    
    // 接受entercar返回值：0=成功，1=黄牌禁入，2=车位满，3=充电桩满，4=其他错误
    int result = lot.enterCar(newCar);

    // 显示入场结果
    if (result == 0) {
        // 入场成功
        cout << endl;
        cout << "  ✅ 车辆入场成功！" << endl;
        cout << "     车牌号：" << plateNo << endl;
        cout << "     车牌颜色：" << plateColor << endl;

        //绿牌车且需要充电桩，显示充电桩信息
        if (needCharging) {
            cout << "     状态：使用充电桩 ⚡" << endl;
        }

        //显示车辆类型（长租车/临时车）
        cout << "     车辆类型：" << carType << endl;

        // 白牌特种车辆随意进入
        if (plateColor == "白色军用车辆") {
            cout << "     类型：特种车辆 ⭐" << endl;
        }

        //长租车，免缴费
        if (carType == "长租车") {
            cout << "     类型：月保长租车 🏠" << endl;
        }
        cout << "     停车位置：" << side << endl;
        cout << "     入场时间：" << newCar.getTimeStr() << endl;
    }
    else if (result == 1) {
        //入场失败：黄牌车
        cout << endl;
        cout << "  ❌ 入场失败：黄牌车车身过大，禁止入场！" << endl;
    }
    else if (result == 2) {
        // 入场失败：车位满 
        cout << endl;
        cout << "  ❌ 入场失败：" << side << "车位已满！" << endl;
    }
    else if (result == 3) {
        // 入场失败：充电桩满
        cout << endl;
        cout << "  ❌ 入场失败：" << side << "充电桩已满！" << endl;
    }
    else {
        cout << endl;
        cout << "  ❌ 入场失败，请稍后重试。" << endl;
    }
    pressEnter();   //返回主菜单
}

// 功能 2：车辆出场 + 缴费
// 显示收款码（尝试弹出图片，并在终端显示提示）
void showPaymentQR() {
    cout << endl;
    cout << "  ╔═══════════════════════════════════╗" << endl;
    cout << "  ║      请使用微信 / 支付宝扫码支付    ║" << endl;
    cout << "  ╚═══════════════════════════════════╝" << endl;
    cout << endl;
    cout << "  ┌─────────────────────────────────┐" << endl;
    cout << "  │  █████████████████████████████  │" << endl;
    cout << "  │  ██  ████  ██    ██  ██  ████  │" << endl;
    cout << "  │  ██  ████  ██  ██  ██  ██  ██  │" << endl;
    cout << "  │  ██  ████  ██  ██  ██  ██  ██  │" << endl;
    cout << "  │  ██                          ██  │" << endl;
    cout << "  │  ██  ██    ██████    ██████  ██  │" << endl;
    cout << "  │  ██  ██████████████████████  ██  │" << endl;
    cout << "  │  ██          ██████          ██  │" << endl;
    cout << "  │  ██                          ██  │" << endl;
    cout << "  │  █████████████████████████████  │" << endl;
    cout << "  └─────────────────────────────────┘" << endl;
    cout << endl;

    //尝试用系统命令打开收款码图片
    string cmd = "";
#ifdef _WIN32
    cmd = "start qrcode.png";             // Windows
#else
    cmd = "open qrcode.png 2>/dev/null || xdg-open qrcode.png 2>/dev/null || echo ''";
#endif
    system(cmd.c_str());                  // 执行打开命令

    cout << "  📱 如果已弹出收款码图片，请扫码付款" << endl;
    cout << "  💡 如果没有弹出，请手动打开项目目录下的 qrcode.png" << endl;
    cout << "  ⏎  付款完成后按回车键确认..." << endl;
    cout << "  ==========================================" << endl;
    cout << endl;

    cin.get();  // 吃掉上一个输入留下的换行符
    cin.get();  // 等待用户按回车
}

//车辆出场
void carExit() {
    showHeader();  
    cout << "  【车辆出场 / 缴费】" << endl;
    cout << "----------------------------------------" << endl;
    //输入要出场的车牌号
    string plateNo;
    cout << "  请输入出场车辆的车牌号：";
    cin >> plateNo;
    //在停车场里找对应的车
    int index = lot.findCar(plateNo);
    if (index == -1) {
        // -1 表示没找到这辆车
        cout << endl;
        cout << "  【提示】未找到该车牌号的车辆！" << endl;
        pressEnter();
        return; 
    }
    //取出车辆信息并显示
    Car car = lot.getCar(index); // 通过下标获取车辆对象
    cout << endl;
    cout << "  ========== 车辆信息 ==========" << endl;
    cout << "  车牌号：" << car.getPlateNo() << endl;
    cout << "  车牌颜色：" << car.getPlateColor() << endl;

    //显示车辆类型（长租车 / 临时车）
    cout << "  车辆类型：" << car.getCarType() << endl;

    if (car.getNeedCharging()) {
        cout << "  状态：使用了充电桩 ⚡" << endl;
    }
    cout << "  停车位置：" << car.getSide() << endl;
    cout << "  入场时间：" << car.getTimeStr() << endl;
    cout << "  停车时长：" << car.getMinutes() << " 分钟" << endl;
    cout << "  ===============================" << endl;
    cout << endl;

    //计算并显示费用
    double minutes = car.getMinutes();    
    double fee = car.getFee();            
    double originalFee = minutes * (3.0 / 60.0); 
    // 显示费用明细
    cout << "  💰 停车费用明细：" << endl;

    // 判断是否免费

    //白牌车免费
    if (car.getPlateColor() == "白色军用车辆") {
        cout << "     金额：0.00 元" << endl;
        cout << "     说明：白牌特种车辆，免费出场 ⭐" << endl;
    }
    //长租车免费
    else if (car.getCarType() == "长租车") {
        cout << "     金额：0.00 元" << endl;
        cout << "     说明：长租月保车辆，出场不收费 🏠" << endl;
    }
    // 不满15分钟免费 //为方便调试，本处改为进场就收费
    else if (minutes < 0) {
        cout << "     原价：";
        printf("%.2f", originalFee);
        cout << " 元" << endl;
        cout << "     优惠：停车不满15分钟，免费 🆓" << endl;
        cout << "     实付：0.00 元" << endl;
    }
    //绿牌车打九折
    else if (car.getPlateColor() == "绿色") {
        cout << "     原价：";
        printf("%.2f", originalFee);
        cout << " 元" << endl;
        cout << "     优惠：绿牌新能源车九折优惠 🔋" << endl;
        cout << "     实付：";
        printf("%.2f", fee);
        cout << " 元" << endl;
    }
    //普通临时车正常收费
    else {
        cout << "     金额：";
        printf("%.2f", fee);
        cout << " 元" << endl;
    }

    cout << "  （收费标准：3元/小时，不足1小时按分钟计费）" << endl;
    cout << endl;

    // 免费出场：自动放行，不收费
    if (car.getPlateColor() == "白色军用车辆" || car.getCarType() == "长租车") {
        cout << "  ✅ 免费出场，直接放行！" << endl;

        //执行出场操作
        Car exited = lot.exitCar(plateNo);
        exited.setPaid(true);

        cout << endl;
        cout << "  ==========================================" << endl;
        cout << "    " << car.getCarType() << " " << plateNo << " 已出场 一路顺风！" << endl;
        cout << "  ==========================================" << endl;
        pressEnter();
        return;
    }

    // 不满15分钟免费，自动出场
    if (minutes < 0) {
        cout << "  🆓 停车不满15分钟，免费出场！" << endl;
        Car exited = lot.exitCar(plateNo);
        exited.setPaid(true);
        cout << endl;
        cout << "  ==========================================" << endl;
        cout << endl;
        cout << "    临时车 " << plateNo << " 已缴费 一路顺风！" << endl;
        cout << endl;
        cout << "  缴费金额：0.00 元（免费）" << endl;
        cout << "  停车时长：" << car.getMinutes() << " 分钟" << endl;
        cout << "  ==========================================" << endl;

        pressEnter();
        return;
    }

    // 正常收费
    // 先显示收款码，让用户扫码付款
    showPaymentQR();
    // 用户付款后，确认出场
    cout << "  是否确认出场？（1=是，2=否）：";
    int choice;
    cin >> choice;
    if (choice == 1) {
        
        Car exited = lot.exitCar(plateNo);
        exited.setPaid(true);

        cout << endl;
        cout << "  ==========================================" << endl;
        cout << "  ✅ 缴费成功！" << endl;
        cout << endl;
        cout << "    临时车 " << plateNo << " 已缴费 一路顺风！" << endl;

        cout << endl;
        cout << "  缴费金额：";
        printf("%.2f", fee);
        cout << " 元" << endl;
        cout << "  停车时长：" << car.getMinutes() << " 分钟" << endl;
        cout << "  ==========================================" << endl;
    } else {
        cout << endl;
        cout << "  已取消出场操作，车辆仍在场内。" << endl;
    }

    pressEnter();
}
//查看在场车辆列表
void showParked() {
    showHeader();
    lot.showParkedCars();   // 调停车场对象的显示方法
    pressEnter();
}
// 功能 4：查看历史停车记录
void showHistory() {
    showHeader();
    lot.showHistory();      // 调停车场对象的显示历史方法
    pressEnter();
}
// 显示主菜单
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
// 主函数
int main() {
    int choice;   // 存放用户在菜单中的选择
    //无限循环，除非退出程序
    while (true) {
        showHeader();   // 显示标题和车位信息
        showMenu();     // 显示菜单选项
        cin >> choice;  
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
            pause(1);         
            return 0;         // 正常结束程序
        }
        else {
            // 输入了 1-5 以外的数字
            cout << endl;
            cout << "  【提示】输入有误，请选择 1-5 之间的数字！" << endl;
            pause(1);
        }
    }
    return 0;   // 程序结束
}
