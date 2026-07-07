// main.cpp —— 程序入口点
// 包含主函数和所有菜单函数（主菜单 + 3个子菜单）
#include "LibrarySystem.h"
#include <iostream>
using namespace std;

// 前向声明：三个子菜单函数
void showBookMenu(LibrarySystem &sys);
void showBorrowerMenu(LibrarySystem &sys);
void showStaffMenu(LibrarySystem &sys);

// ============================================
//  主菜单
// ============================================
void showMainMenu(LibrarySystem &sys) {
    int choice;
    do {
        // 显示菜单边框
        cout << "\n╔══════════════════════════╗\n";
        cout << "║      图书管理系统        ║\n";
        cout << "╠══════════════════════════╣\n";
        cout << "║  1. 图书管理             ║\n";
        cout << "║  2. 借阅人员管理         ║\n";
        cout << "║  3. 工作人员管理         ║\n";
        cout << "║  4. 借书                 ║\n";
        cout << "║  5. 还书                 ║\n";
        cout << "║  6. 保存数据             ║\n";
        cout << "║  7. 退出系统             ║\n";
        cout << "╚══════════════════════════╝\n";
        // 底部显示当前数据量
        cout << "【当前数据：图书 " << sys.getBookCount()
             << "本 | 借阅者 " << sys.getBorrowerCount()
             << "人 | 工作人员 " << sys.getStaffCount() << "人】\n";
        cout << "请选择：";
        choice = sys.getChoice(1, 7);

        // 根据选择执行相应功能
        switch (choice) {
            case 1: showBookMenu(sys); break;
            case 2: showBorrowerMenu(sys); break;
            case 3: showStaffMenu(sys); break;
            case 4: sys.borrowBook(); break;
            case 5: sys.returnBook(); break;
            case 6: sys.saveData(); break;
            case 7: cout << "\n感谢使用图书管理系统，再见！\n"; break;
        }
    } while (choice != 7);
}

// ============================================
//  图书管理子菜单
// ============================================
void showBookMenu(LibrarySystem &sys) {
    int choice;
    do {
        cout << "\n── 图书管理 ──\n";
        cout << "1. 添加图书\n2. 删除图书\n3. 修改图书\n";
        cout << "4. 查询图书\n5. 显示所有图书\n6. 返回主菜单\n";
        cout << "请选择：";
        choice = sys.getChoice(1, 6);
        switch (choice) {
            case 1: sys.addBook(); break;
            case 2: sys.deleteBook(); break;
            case 3: sys.modifyBook(); break;
            case 4: sys.searchBook(); break;
            case 5: sys.listAllBooks(); break;
        }
    } while (choice != 6);
}

// ============================================
//  借阅人员管理子菜单
// ============================================
void showBorrowerMenu(LibrarySystem &sys) {
    int choice;
    do {
        cout << "\n── 借阅人员管理 ──\n";
        cout << "1. 添加借阅者\n2. 删除借阅者\n3. 修改信息\n";
        cout << "4. 查询借阅者\n5. 显示所有借阅者\n6. 返回主菜单\n";
        cout << "请选择：";
        choice = sys.getChoice(1, 6);
        switch (choice) {
            case 1: sys.addBorrower(); break;
            case 2: sys.deleteBorrower(); break;
            case 3: sys.modifyBorrower(); break;
            case 4: sys.searchBorrower(); break;
            case 5: sys.listAllBorrowers(); break;
        }
    } while (choice != 6);
}

// ============================================
//  工作人员管理子菜单
// ============================================
void showStaffMenu(LibrarySystem &sys) {
    int choice;
    do {
        cout << "\n── 工作人员管理 ──\n";
        cout << "1. 添加工作人员\n2. 删除工作人员\n3. 修改信息\n";
        cout << "4. 查询工作人员\n5. 显示所有工作人员\n6. 返回主菜单\n";
        cout << "请选择：";
        choice = sys.getChoice(1, 6);
        switch (choice) {
            case 1: sys.addStaff(); break;
            case 2: sys.deleteStaff(); break;
            case 3: sys.modifyStaff(); break;
            case 4: sys.searchStaff(); break;
            case 5: sys.listAllStaff(); break;
        }
    } while (choice != 6);
}

// ============================================
//  主函数：程序入口
// ============================================
int main() {
    LibrarySystem system;  // 创建系统（自动加载文件数据）
    showMainMenu(system);  // 进入主菜单循环
    return 0;              // 正常退出
}
