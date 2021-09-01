#include "logsystem.hh"

const std::string LogSystem::m_sFileName_ = "Log.txt";
std::ofstream LogSystem::m_Logfile_;
LogSystem::LogSystem()
{

}
LogSystem &LogSystem::instance()
{
    // Lazy initialization
    static LogSystem *instance = new LogSystem();
    return *instance;
}

void LogSystem::log(const std::string &message)
{

}

LogSystem &LogSystem::operator<<(const std::string &message)
{

}

LogSystem::LogSystem(const LogSystem &)
{

}

LogSystem &LogSystem::operator=(const LogSystem &)
{
    return *this;
}
