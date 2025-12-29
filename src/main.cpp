import <iostream>;
import <format>;
// import employee;

using namespace std;

int main()
{
/*     //Create and populate an employee.
    Employee anEmployee;
    anEmployee.firstInitial='J';
    anEmployee.lastInitial='D';
    anEmployee.employeeNumber = 42;
    anEmployee.salary=80000;
    //Output the values of an employee.
    cout << format("Employee:{}{}",anEmployee.firstInitial,anEmployee.lastInitial) << endl;
    cout << format("Number:{}",anEmployee.employeeNumber) << endl;
    cout << format("Salary:${}",anEmployee.salary) << endl;
    cin.get() ;
    return 0; */
  
    enum class Mode { Default, Custom, Standard };
    int value { 42 };
    Mode mode {  Mode::Custom }; //此处没有use enum Mode; 因此初始化时需要加【Mode::】
    switch (mode) {
        using enum Mode;
        case Custom:
            value = 84;
            cout << format("Custom mode: value={}\n", value);
        case Standard:
            value = 21;
            cout << format("Standard mode: value={}\n", value);
        case Default:
            value = 42;
            cout << format("Standard mode: value={}\n", value);
        break;
    }
}