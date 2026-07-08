### Summer_Semester
###### 本图书管理系统主要结构（version 1.00）
```
Project/
├── Book.h              # Book 类声明
├── Book.cpp            # Book 类实现
├── Person.h            # Person 基类声明
├── Person.cpp          # Person 基类实现
├── Borrower.h          # Borrower 借阅者类声明
├── Borrower.cpp        # Borrower 借阅者类实现
├── Staff.h             # Staff 工作人员类声明
├── Staff.cpp           # Staff 工作人员类实现
├── LibrarySystem.h     # LibrarySystem 管理类声明
├── LibrarySystem.cpp   # LibrarySystem 管理类实现
├── main.cpp            # 主函数 + 菜单交互
├── books.txt           # 图书数据（运行后自动生成）
├── borrowers.txt       # 借阅者数据（运行后自动生成）
├── staff.txt           # 工作人员数据（运行后自动生成）
└── README.md           # 本文档
```
###### 本停车场管理系统主要结构（version 1.00）
```
main()
 ├── showHeader()          ← 每次循环都先刷新界面
 ├── showMenu()            ← 显示菜单选项
 │
 ├── [选1] carEntry()      ← 车辆入场
 │    ├── lot.findCar()         检查是否重复
 │    ├── lot.getEastFree()     检查东边车位
 │    ├── lot.getWestFree()     检查西边车位
 │    ├── Car(no, color, side)  创建车辆对象
 │    └── lot.enterCar(car)     执行入场
 │
 ├── [选2] carExit()       ← 车辆出场
 │    ├── lot.findCar()         查找车辆
 │    ├── lot.getCar(index)     获取车辆信息
 │    ├── car.getFee()          计算费用
 │    ├── lot.exitCar(plateNo)  执行出场
 │    └── exited.setPaid(true)  标记已缴费
 │
 ├── [选3] showParked()    ← 查看在场车辆
 │    └── lot.showParkedCars()
 │
 ├── [选4] showHistory()   ← 查看历史记录
 │    └── lot.showHistory()
 │
 └── [选5] return 0        ← 退出程序
```
