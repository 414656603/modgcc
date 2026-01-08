//告诉编译器这是一个模块实现单元
module airline_ticket;

import <string>;

//2：用 构造函数初始化器 列表 初始化数据成员
AirlineTicket::AirlineTicket()
    : m_passengerName("unkown Passenger") 
    , m_numberOfMiles(0)
    , m_hasEliteSuperRewardsStatus(false)
{}


//3：另一种初始化数据成员的方式
// AirlineTicket::AirlineTicket()
// {
//     //initialize data members if needed
//     m_passengerName = "unkown Passenger";
//     m_numberOfMiles = 0;
//     m_hasEliteSuperRewardsStatus = false;
// }

AirlineTicket::~AirlineTicket()
{
    //destructor body if needed
}

double AirlineTicket::calculatePriceInDollars()
{
    if (hasEliteSuperRewardsStatus()) {
        //Elite Super Rewards members fly for free!
        return 0.0;
    }
    // The cost of the ticket is the number of miles times 0.1
    // Real airlines probably have more complex pricing formulas!
    return getNumberOfMiles() * 0.1;
}

std::string AirlineTicket::getPassengerName() { return m_passengerName; }
void AirlineTicket::setPassengerName(std::string name) { m_passengerName = name; }

int AirlineTicket::getNumberOfMiles() { return m_numberOfMiles; }
void AirlineTicket::setNumberOfMiles(int miles) { m_numberOfMiles = miles; }

bool AirlineTicket::hasEliteSuperRewardsStatus() { return m_hasEliteSuperRewardsStatus; }
void AirlineTicket::setEliteSuperRewardsStatus(bool status) { m_hasEliteSuperRewardsStatus = status; }
//other get and set methods have a similar implementation