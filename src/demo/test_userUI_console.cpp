#include "demo/testAll.h"

import <iostream>;
import <stdexcept>;
import <exception>;
import <format>;
import <string>;

import database;
import employee;

using namespace std;
using namespace Records;

int displayMenu();
//void doHire(Database& db) 传引用：不拷贝对象，函数里操作的是调用者的同一个对象，可修改原对象，效率高。
//void doHire(Database db) 传值：会拷贝一份，函数里改的是副本，不影响原对象，开销更大。
void doHire (Database& db);
void doFire (Database& db);
void doPromote (Database& db);


int Test_UserUI_Console()
{
    cout << "测试用户界面（控制台版）" << endl;
    Database employeeDB;
    bool done {false};
    while (!done)  //阻塞循环
    {
        int selection { displayMenu() };
        switch (selection) {
            case 0:
                done = true;
                break;
            case 1:
            //doHire(Database& db)需要左值引用参数，employeeDB是一个具名对象（左值），
            //传参时会绑定到该左值引用，因此不会拷贝对象。
                doHire(employeeDB); 
                break;
            case 2:
                doFire(employeeDB);
                break;
            case 3:
                doPromote(employeeDB);
                break;
            case 4:
                employeeDB.displayAll();
                break;
            case 5:
                employeeDB.displayCurrent();
                break;
            case 6:
                employeeDB.displayFormer();
                break;
            default:
                cerr << "未知的选项！" << endl;
                break;
        } //switch
    } //while
    return 0;
}


int displayMenu()
{
    int selection;
    cout << endl;
    cout << "员工数据库菜单：" << endl;
    cout << "---------------------------" << endl;
    cout << "1) 雇用新员工" << endl;
    cout << "2) 解雇员工" << endl;
    cout << "3) 提升员工" << endl; 
    cout << "4) 显示所有员工" << endl;
    cout << "5) 显示现有员工" << endl;
    cout << "6) 显示前员工" << endl;
    cout << "0) 退出" << endl;
    cout << "---------------------------" << endl;
    cout << "请选择一个选项：  ----->";
    cin >> selection;
    return selection;
}


void doHire (Database& db)
{
    string firstName;
    string lastName;
    cout << "输入新员工的名字： ";
    cin >> firstName;
    cout << "输入新员工的姓氏： ";
    cin >> lastName;
    
    auto& employee { db.addEmployee(firstName, lastName) };
    cout << format("已雇用员工： {} {}", employee.getEmployeeNumber(), employee.getFirstName()) << endl;
}


void doFire (Database& db)
{
    int employeeNumber;
    cout << "输入要解雇的员工编号： ";
    cin >> employeeNumber;

    try {
        auto& employee { db.getEmployee(employeeNumber) };
        employee.fire();
        cout << format("已解雇员工： {} {}", employee.getEmployeeNumber(), employee.getFirstName()) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "错误： " << e.what() << endl;
    }
}


void doPromote (Database& db)
{
    int employeeNumber;
    int raiseAmount;
    cout << "输入要提升的员工编号： ";
    cin >> employeeNumber;
    cout << "输入加薪金额： ";
    cin >> raiseAmount;

    try {
        auto& employee { db.getEmployee(employeeNumber) };
        employee.promote(raiseAmount);
        cout << format("已提升员工： {} {}, 新薪水： {}", employee.getEmployeeNumber(), employee.getFirstName(), employee.getSalary()) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "错误： " << e.what() << endl;
    }
}