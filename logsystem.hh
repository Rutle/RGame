#ifndef LOGSYSTEM_HH
#define LOGSYSTEM_HH
#include <fstream>
#include <iostream>

class LogSystem
{
    public:
        static LogSystem& instance();
        void log(const std::string &message);
        LogSystem &operator<<(const std::string& message);
    private:
        // default constructor
        LogSystem();
        // copy constructor
        LogSystem(const LogSystem&);
        // assignment operator
        LogSystem& operator=(const LogSystem&);
        static const std::string m_sFileName_;
        static std::ofstream m_Logfile_;

};

#endif // LOGSYSTEM_HH
