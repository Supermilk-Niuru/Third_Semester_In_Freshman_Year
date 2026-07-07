# 图书管理系统 —— 文档

## 一、项目简介

一个基于C++面向对象思想实现的图书管理系统，支持**图书管理**、**借阅管理**、**工作人员管理**和**数据持久化存储**。

### 技术特性

- 🧬 **OOP封装**：所有类成员变量均为`private`，通过getter/setter访问
- 🧬 **OOP继承**：`Person`作为基类，`Borrower`和`Staff`派生，复用公共字段
- 🧬 **OOP多态**：基类`display()`声明为`virtual`，子类`override`各自展示
- 💾 **持久化**：数据保存为本地txt文件，程序重启自动加载
- 🛡️ **安全输入**：菜单选项带范围校验，防止非法输入导致崩溃

---

## 二、文件结构

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

### 为什么分为 .h 和 .cpp？

| 文件类型 | 作用 |
|---------|------|
| `.h` 头文件 | 类的**声明**：列出有哪些成员变量、成员函数。供其他文件`#include`引用 |
| `.cpp` 实现文件 | 类的**实现**：写出每个函数的具体代码逻辑。编译时与`.h`文件链接 |

这种分离的好处：修改实现时不影响声明，头文件改动少，编译更快，结构更清晰。

---

## 三、类的继承关系

```
         Person（人员基类）
         ├── Name, Gender, Phone, Email
         │
    ┌────┴────┐
    │         │
Borrower    Staff
+ StudentId  + StaffId
+ Borrowed   + 无额外属性
  Books[]
+ Violation
  Count

            Book（图书类，独立）
            ├── Title, Isbn, Author, Publisher
            ├── PrintCount, IsBorrowed, BorrowDuration
```

---

## 四、各文件及函数说明

### 4.1 Book.h / Book.cpp —— 图书类

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `Book()` | 无 | — | 默认构造函数，初始化为空/0 |
| `Book(t, isbn, a, pub, pc)` | 书名、ISBN、作者、出版社、印次 | — | 带参构造函数 |
| `getTitle()` / `getIsbn()` / 等7个getter | 无 | 对应类型值 | 获取私有成员的值 |
| `setTitle()` / `setIsbn()` / 等5个setter | 对应值 | void | 修改私有成员的值 |
| `borrowIt()` | 无 | void | 将`IsBorrowed`设为`true`，标记已借出 |
| `returnIt(days)` | 借阅天数 | void | 将`IsBorrowed`设为`false`，记录借阅时长 |
| `display()` | 无 | void | 在控制台打印图书完整信息 |
| `toFileString()` | 无 | string | 将对象序列化为`\|`分隔的字符串（写入文件用） |
| `fromFileString(str)` | 文件中的一行字符串 | void | 从`\|`分隔的字符串解析字段（从文件读取用） |

---

### 4.2 Person.h / Person.cpp —— 人员基类

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `Person()` | 无 | — | 默认构造函数 |
| `Person(n, g, p, e)` | 姓名、性别、电话、邮件 | — | 带参构造函数 |
| `getName()` / `getGender()` / `getPhone()` / `getEmail()` | 无 | string | 获取私有成员 |
| `setName()` / `setGender()` / `setPhone()` / `setEmail()` | new值 | void | 修改私有成员 |
| `virtual display()` | 无 | void | **虚函数**，显示人员公共信息，子类可override扩展 |
| `virtual ~Person()` | 无 | — | 虚析构函数（保证多态场景下正确释放） |
| `personToFileString()` | 无 | string | 将基类4个字段序列化（子类调用） |
| `personFromFileString(str)` | 字符串 | void | 从字符串解析基类字段（子类调用） |

---

### 4.3 Borrower.h / Borrower.cpp —— 借阅人员类（继承 Person）

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `Borrower()` | 无 | — | 默认构造函数，违约次数=0 |
| `Borrower(n, sid, g, p, e)` | 姓名、学号、性别、电话、邮件 | — | 带参构造函数 |
| `getStudentId()` | 无 | string | 获取学号 |
| `getViolationCount()` | 无 | int | 获取违约次数 |
| `getBorrowedBooks()` | 无 | vector\<string\> | 获取借阅ISBN列表 |
| `getBorrowedCount()` | 无 | int | 获取当前借了几本书 |
| `setStudentId(sid)` | 新学号 | void | 修改学号 |
| `setViolationCount(v)` | 新违约次数 | void | 修改违约次数 |
| `addBorrowedBook(isbn)` | 图书ISBN | void | **借书时用**：将ISBN加入借阅列表 |
| `removeBorrowedBook(isbn)` | 图书ISBN | void | **还书时用**：从借阅列表移除ISBN |
| `addViolation()` | 无 | void | 违约次数+1 |
| `display()` | 无 | void | **override**：先调用`Person::display()`，再显示学号/借阅数/违约次数 |
| `toFileString()` | 无 | string | 序列化为文件行 |
| `fromFileString(str)` | 字符串 | void | 从文件行反序列化 |

---

### 4.4 Staff.h / Staff.cpp —— 工作人员类（继承 Person）

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `Staff()` | 无 | — | 默认构造函数 |
| `Staff(n, sid, g, p, e)` | 姓名、工号、性别、电话、邮件 | — | 带参构造函数 |
| `getStaffId()` | 无 | string | 获取工号 |
| `setStaffId(sid)` | 新工号 | void | 修改工号 |
| `display()` | 无 | void | **override**：先调用`Person::display()`，再显示工号 |
| `toFileString()` | 无 | string | 序列化为文件行 |
| `fromFileString(str)` | 字符串 | void | 从文件行反序列化 |

---

### 4.5 LibrarySystem.h / LibrarySystem.cpp —— 管理系统核心类

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `LibrarySystem()` | 无 | — | **构造函数**：自动调用`loadBooks()`/`loadBorrowers()`/`loadStaff()`加载已有数据 |
| `getChoice(min, max)` | 最小值、最大值 | int | 安全输入函数，只接受min~max范围的整数 |
| **图书管理** | | | |
| `addBook()` | 无 | void | 从控制台读取信息，创建Book加入容器 |
| `deleteBook()` | 无 | void | 按ISBN删除（已借出的不可删除） |
| `modifyBook()` | 无 | void | 按ISBN查找，支持"回车跳过"部分修改 |
| `searchBook()` | 无 | void | 按书名/ISBN/作者模糊搜索 |
| `listAllBooks()` | 无 | void | 遍历容器显示所有图书 |
| **借阅人员管理** | | | |
| `addBorrower()` | 无 | void | 从控制台读取信息，创建Borrower加入容器 |
| `deleteBorrower()` | 无 | void | 按学号删除（有未还书的不可删除） |
| `modifyBorrower()` | 无 | void | 按学号查找，支持部分修改 |
| `searchBorrower()` | 无 | void | 按姓名/学号模糊搜索 |
| `listAllBorrowers()` | 无 | void | 遍历容器显示所有借阅者（含借阅/违约状态） |
| **工作人员管理** | | | |
| `addStaff()` | 无 | void | 添加工作人员 |
| `deleteStaff()` | 无 | void | 按工号删除 |
| `modifyStaff()` | 无 | void | 按工号修改信息 |
| `searchStaff()` | 无 | void | 按姓名/工号模糊搜索 |
| `listAllStaff()` | 无 | void | 遍历容器显示所有工作人员 |
| **借还操作** | | | |
| `borrowBook()` | 无 | void | 输入学号+ISBN，借书给借阅者 |
| `returnBook()` | 无 | void | 输入学号+ISBN+天数，还书，超30天自动记录违约 |
| **文件读写** | | | |
| `saveData()` | 无 | void | 调用`saveBooks()`+`saveBorrowers()`+`saveStaff()`，写入三个txt文件 |
| `loadBooks()` | 无 | void | **私有**，从books.txt加载数据 |
| `saveBooks()` | 无 | void | **私有**，将Books容器写入books.txt |
| `loadBorrowers()` | 无 | void | **私有**，从borrowers.txt加载数据 |
| `saveBorrowers()` | 无 | void | **私有**，将Borrowers容器写入borrowers.txt |
| `loadStaff()` | 无 | void | **私有**，从staff.txt加载数据 |
| `saveStaff()` | 无 | void | **私有**，将StaffMembers容器写入staff.txt |
| **统计** | | | |
| `getBookCount()` | 无 | int | 返回图书总数（主菜单显示用） |
| `getBorrowerCount()` | 无 | int | 返回借阅者总数 |
| `getStaffCount()` | 无 | int | 返回工作人员总数 |

---

### 4.6 main.cpp —— 主程序入口

| 函数 | 参数 | 返回值 | 功能 |
|------|------|--------|------|
| `main()` | 无 | int | 创建`LibrarySystem`对象，进入主菜单循环 |
| `showMainMenu(sys)` | LibrarySystem引用 | void | 显示主菜单（7个选项），分发到子菜单或功能 |
| `showBookMenu(sys)` | LibrarySystem引用 | void | 图书管理子菜单（6个选项） |
| `showBorrowerMenu(sys)` | LibrarySystem引用 | void | 借阅人员管理子菜单（6个选项） |
| `showStaffMenu(sys)` | LibrarySystem引用 | void | 工作人员管理子菜单（6个选项） |

---

## 五、数据文件格式

### books.txt（每行一本图书，`|`分隔）

```
书名|ISBN|作者|出版社|印次|是否借出(0/1)|借阅时长(天)
```

示例：
```
C++ Primer|978-7-111-10100-1|Stanley Lippman|机械工业出版社|5|0|0
```

### borrowers.txt（每行一位借阅者，`|`分隔，借阅列表用`,`分隔）

```
姓名|性别|电话|邮件|学号|违约次数|ISBN1,ISBN2,...
```

示例：
```
张三|男|13800138000|zhangsan@edu.cn|2024001|0|
```

### staff.txt（每行一位工作人员，`|`分隔）

```
姓名|性别|电话|邮件|工号
```

---

## 六、如何运行

### 环境要求

- **操作系统**：macOS / Linux / Windows（任一台支持C++编译器的系统）
- **编译器**：`g++` 或 `clang++`（支持C++11标准）

### 步骤一：打开终端

```bash
cd /Users/supermilk/Desktop/暑期实训/Project
```

### 步骤二：编译

```bash
g++ -std=c++11 Book.cpp Person.cpp Borrower.cpp Staff.cpp LibrarySystem.cpp main.cpp -o Library_Manage
```

参数说明：
- `-std=c++11`：使用C++11标准
- `*.cpp`：需要编译的6个源文件
- `-o Library_Manage`：输出的可执行文件名

### 步骤三：运行

```bash
./Library_Manage
```

### 步骤四：按菜单操作

```
╔══════════════════════════╗
║      图书管理系统        ║
╠══════════════════════════╣
║  1. 图书管理             ║
║  2. 借阅人员管理         ║
║  3. 工作人员管理         ║
║  4. 借书                 ║
║  5. 还书                 ║
║  6. 保存数据             ║
║  7. 退出系统             ║
╚══════════════════════════╝
```

- 输入数字选择功能
- 选 `6` 保存数据到文件
- 选 `7` 退出（记得先保存！）

---

## 七、典型操作流程

```
1. 添加图书
   主菜单 → 1 → 1 → 输入书名、ISBN、作者、出版社、印次

2. 添加借阅者
   主菜单 → 2 → 1 → 输入姓名、学号、性别、电话、邮件

3. 借书
   主菜单 → 4 → 输入借阅者学号 → 输入图书ISBN

4. 还书
   主菜单 → 5 → 输入借阅者学号 → 输入图书ISBN → 输入借阅天数

5. 保存
   主菜单 → 6 → 确认保存信息

6. 退出
   主菜单 → 7
```
