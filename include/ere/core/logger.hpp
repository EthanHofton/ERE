#ifndef __ERE_LOGGER_HPP__
#define __ERE_LOGGER_HPP__

#include <util/logger.hpp>
#include <util/logger_console_sink.hpp>

class ere_logger {
private:

    /**
    * @brief Private constructor.
    */
    inline ere_logger()
    { m_logger.addSink<util::logger_console_sink>("ere_console_logger"); m_logger.logInfo("Logger initialized"); }

public:

    /**
    * @brief logger distructor
    */
    inline ~ere_logger() { m_logger.logInfo("Logger destroyed"); }

    /**
    * @brief get the logger instance
    *
    * @return logger instance
    */
    inline static ere_logger& get() {
        static ere_logger instance;
        return instance;
    }

    /**
    * @brief deleted copy constructor
    *
    * @param const& other
    */
    ere_logger(ere_logger const&) = delete;
    /**
    * @brief operator = delete
    *
    * @param const& other
    */
    void operator=(ere_logger const&) = delete;

    /**
    * @brief logger instance
    */
    util::logger m_logger;
};

// logger macros
#define ERE_TRACE(...)    ere::ereLogger::instance().m_logger.logTrace(__VA_ARGS__)
#define ERE_DEBUG(...)    ere::ereLogger::instance().m_logger.logDebug(__VA_ARGS__)
#define ERE_INFO(...)     ere::ereLogger::instance().m_logger.logInfo(__VA_ARGS__)
#define ERE_WARN(...)     ere::ereLogger::instance().m_logger.logWarning(__VA_ARGS__)
#define ERE_ERROR(...)    ere::ereLogger::instance().m_logger.logError(__VA_ARGS__)
#define ERE_CRITICAL(...) ere::ereLogger::instance().m_logger.logCritical(__VA_ARGS__)

#endif
