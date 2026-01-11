export module airline_ticket;

import <string>;

export class AirlineTicket
{
    public:
		AirlineTicket();
		~AirlineTicket();

        double calculatePriceInDollars() const;

        std::string getPassengerName() const;
        void setPassengerName(std::string name);

        int getNumberOfMiles() const;
        void setNumberOfMiles(int miles);

        bool hasEliteSuperRewardsStatus() const;
        void setEliteSuperRewardsStatus(bool status);

    private:
        std::string m_passengerName;
        int m_numberOfMiles;
        bool m_hasEliteSuperRewardsStatus;

        //1、在类内初始化数据成员
        //std::string m_passengerName{"unkown Passenger"}; 
        //int m_numberOfMiles{0};
        //bool m_hasEliteSuperRewardsStatus{false};
};


//也可以把实现直接放在接口文件里：
export class AirlineTicketInline
{
    public:
        AirlineTicketInline() {}

        ~AirlineTicketInline() {}

        double calculatePriceInDollars()
        {
            if (hasEliteSuperRewardsStatus()) {
                return 0.0;
            }
            return getNumberOfMiles() * 0.1;
        }

        std::string getPassengerName() { return m_passengerName; }
        void setPassengerName(std::string name) { m_passengerName = name; }

        int getNumberOfMiles() { return m_numberOfMiles; }
        void setNumberOfMiles(int miles) { m_numberOfMiles = miles; }

        bool hasEliteSuperRewardsStatus() { return m_hasEliteSuperRewardsStatus; }
        void setEliteSuperRewardsStatus(bool status) { m_hasEliteSuperRewardsStatus = status; }

    private:
        std::string m_passengerName {"unkown Passenger"};
        int m_numberOfMiles {0};
        bool m_hasEliteSuperRewardsStatus {false};
};