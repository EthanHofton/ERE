#ifndef ERE_CORE_LOGGER_HPP
#define ERE_CORE_LOGGER_HPP

#include <util/logger.hpp>
#include <util/logger_console_sink.hpp>

namespace ere {

class ereLogger {
private:

    inline ereLogger() 
    { m_logger.addSink<util::logger_console_sink>("ereConsoleLogger"); m_logger.logInfo("logger initalized"); }

public:
    
    /**
    * @brief ereLogger destructor, display distruction message
    */
    inline ~ereLogger() { m_logger.logInfo("destroying logger"); }

    /**
    * @brief ereLogger get static instance
    *
    * @return the static instance of the logger
    */
    inline static ereLogger &instance() {
        static ereLogger instance;
        return instance;
    }

    /**
    * @brief explisity deleted copy constructor
    *
    * @param the logger to copy
    */
    ereLogger(ereLogger const &) = delete;
    /**
    * @brief explitity delete assignement operator
    *
    * @param the logger to copy
    */
    void operator=(ereLogger const &) = delete;

    /**
    * @brief public exposed util logger
    */
    util::logger m_logger;
};

#define ERE_TRACE(...)    ere::ereLogger::instance().m_logger.logTrace(__VA_ARGS__)
#define ERE_DEBUG(...)    ere::ereLogger::instance().m_logger.logDebug(__VA_ARGS__)
#define ERE_INFO(...)     ere::ereLogger::instance().m_logger.logInfo(__VA_ARGS__)
#define ERE_WARN(...)     ere::ereLogger::instance().m_logger.logWarning(__VA_ARGS__)
#define ERE_ERROR(...)    ere::ereLogger::instance().m_logger.logError(__VA_ARGS__)
#define ERE_CRITICAL(...) ere::ereLogger::instance().m_logger.logCritical(__VA_ARGS__)

} // namespace ere

#endif
