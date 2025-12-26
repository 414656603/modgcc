export module employee;    //首行声明：本模块名。
export struct Employee {   //export关键字：导入本模块时的可见内容。
    char firstInitial;
    char lastInitial;
    int employeeNumber;
    int salary;
};