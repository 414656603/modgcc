export module employee;    //首行声明：本模块名。
import <string>;        //导入标准库模块。
namespace Records {
    const int DefaultStartingSalary = 30'000;
    export const int DefaultRaiseAndDemeritAmount = 1'000;

    export class Employee
    {
        public:
            Employee(const std::string& firstname, const std::string& lastname);
            void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
            void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);
            void hire();
            void fire();
            void display() const; // output employee information to the screen,to console

            //Getter and setters
            /*
临时对象  也是如此。不能为  临时对象  创建  对非const的  引用  ，但是  const引用  是可以的。例如，假设具有以下返回  std::string对象的函数：
string getString() { return "Hello world!"; }  //这玩意不能直接给引用赋值
可以为getSting()的结果创建一个  const引用  ，该  引用  将使  临时std::string对象【保持生命周期】，直到该引用  超出    作用域  。
string& tempStringRef = createTemporaryString();  //编译错误：不能为临时对象创建对非const的引用
const string& constTempStringRef { createTemporaryString() }; //有效：【const引用】可以引用【临时对象,std::string对象】
            */
            void setFirstName(const std::string& firstname);
            const std::string& getFirstName() const;

            void setLastName(const std::string& lastname);
            const std::string& getLastName() const;

            void setEmployeeNumber(int employeeNumber);
            int getEmployeeNumber() const;

            void setSalary(int newSalary);
            int getSalary() const;

            bool isHired() const;
        
        private:
            std::string m_firstName;
            std::string m_lastName;
            int m_employeeNumber {-1}; //-1 indicates unassigned employee number
            int m_salary {DefaultStartingSalary};
            bool m_hired { false };
    }; //class Employee
} //namespace Records



// 将示例中使用的 POD Employee 放入独立命名空间，避免与 Records::Employee 冲突。
namespace SimpleEmployee {
    export struct Employee {
        char firstInitial;
        char lastInitial;
        int employeeNumber;
        int salary;
    };
}

