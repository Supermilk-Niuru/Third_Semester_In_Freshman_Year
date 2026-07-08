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
###### 本停车场管理系统主要结构
###### version 1.00
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
###### version 2.00
```
main()
 ├── showHeader()             ← 标题 + 车位数 + 充电桩数
 ├── showMenu()               ← 显示 5 个选项
 │
 ├── [选1] carEntry()         ← 车辆入场
 │    ├── lot.findCar()             检查车牌重复
 │    ├── 选颜色
 │    │    ├── 黄色 → 提示禁入，返回
 │    │    ├── 绿色 → 显示充电桩空闲数，询问是否需要
 │    │    └── 其他 → 继续
 │    ├── 选位置（东边/西边）
 │    ├── 车位检查（白色跳过，其他检查）
 │    ├── 充电桩检查（绿色需要充电时检查）
 │    ├── Car(no, color, side, needCharge)  创建车辆
 │    └── lot.enterCar(car)                 执行入场
 │
 ├── [选2] carExit()          ← 车辆出场
 │    ├── lot.findCar()              查找车辆
 │    ├── lot.getCar(index)          获取车辆信息
 │    ├── car.getFee()               计算费用
 │    ├── car.getDiscountInfo()      获取折扣说明
 │    ├── 不满15分钟 → 自动免费出场
 │    ├── 正常 → 确认缴费
 │    │    ├── lot.exitCar(plateNo)  执行出场（释放充电桩）
 │    │    └── 显示"临时车 XX 已缴费 一路顺风！"
 │    └── 取消 → 保留在场
 │
 ├── [选3] showParked()       ← 在场车辆
 │    └── lot.showParkedCars()
 │
 ├── [选4] showHistory()      ← 历史记录
 │    └── lot.showHistory()
 │
 └── [选5] return 0           ← 退出
 ```
 **本次更新**
 1. 针对进场少于15分钟的同志收费不太合理，进场少于15分钟的车辆可以免缴停车费
 2. 为响应能源战略，针对新能源车辆停车9折优惠
 3. 显示停车场充电桩数量
 4. 修复了一些已知问题
 感谢您的支持！

###### version 3.00

```
main()
 ├── showHeader()             ← 标题 + 车位数 + 充电桩数
 ├── showMenu()               ← 显示 5 个选项
 │
 ├── [选1] carEntry()         ← 车辆入场
 │    ├── lot.findCar()             检查车牌重复
 │    ├── 选颜色
 │    │    ├── 黄色 → 提示禁入，返回
 │    │    ├── 绿色 → 显示充电桩空闲数，询问是否需要
 │    │    └── 其他 → 继续
 │    ├── 选位置（东边/西边）
 │    ├── 车位检查（白色跳过，其他检查）
 │    ├── 充电桩检查（绿色需要充电时检查）
 │    ├── Car(no, color, side, needCharge)  创建车辆
 │    └── lot.enterCar(car)                 执行入场
 │
 ├── [选2] carExit()          ← 车辆出场
 │    ├── lot.findCar()              查找车辆
 │    ├── lot.getCar(index)          获取车辆信息
 │    ├── car.getFee()               计算费用
 │    ├── car.getDiscountInfo()      获取折扣说明
 │    ├── 不满15分钟 → 自动免费出场
 │    ├── 正常 → 确认缴费
 │    │    ├── lot.exitCar(plateNo)  执行出场（释放充电桩）
 │    │    └── 显示"临时车 XX 已缴费 一路顺风！"
 │    └── 取消 → 保留在场
 │
 ├── [选3] showParked()       ← 在场车辆
 │    └── lot.showParkedCars()
 │
 ├── [选4] showHistory()      ← 历史记录
 │    └── lot.showHistory()
 │
 └── [选5] return 0           ← 退出
```
**本次更新**
1. 为方便测试，除特殊车辆和长租车辆之外，只要进停车场就开始收费
2. 将车辆进行分类，分为长租车和短租车
3. 增加弹出收款码截图功能。

