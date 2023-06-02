#include "SDOLogger.h"
#include <iostream>
#include <rtm/SystemLogger.h>


SDOLoggerStream::SDOLoggerStream() : 
  m_level(RTC::Logger::RTL_INFO), m_logger(nullptr)
{
}

SDOLoggerStream::~SDOLoggerStream()
{
}

bool SDOLoggerStream::init(const coil::Properties& prop)
{
  std::string level(prop["logger.log_level"]);
  if (level == "SILENT")
  {
    m_level = RTC::Logger::RTL_SILENT;
  }
  if (level == "FATAL")
  {
    m_level = RTC::Logger::RTL_FATAL;
  }
  if (level == "ERROR")
  {
    m_level = RTC::Logger::RTL_ERROR;
  }
  else if (level == "WARN")
  {
    m_level = RTC::Logger::RTL_WARN;
  }
  else if (level == "INFO")
  {
    m_level = RTC::Logger::RTL_INFO;
  }
  else if (level == "NORMAL")
  {
    m_level = RTC::Logger::RTL_INFO;
  }
  else if (level == "DEBUG")
  {
    m_level = RTC::Logger::RTL_DEBUG;
  }
  else if (level == "TRACE")
  {
    m_level = RTC::Logger::RTL_TRACE;
  }
  else if (level == "VERBOSE")
  {
    m_level = RTC::Logger::RTL_VERBOSE;
  }
  else if (level == "PARANOID")
  {
    m_level = RTC::Logger::RTL_PARANOID;
  }

  m_instance_name = prop["comp.instance_name"];

  return true;
}

void SDOLoggerStream::setConsumer(RTC::CorbaConsumer<OpenRTM::Logger>* logger)
{
  m_logger = logger;
}

void SDOLoggerStream::write(int level, const std::string& name, const std::string& date, const std::string& mes)
{
  if (level >= m_level)
  {
    return;
  }
  OpenRTM::LogRecord record;

  auto now = std::chrono::system_clock::now().time_since_epoch();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
  auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sec);
  record.time.sec = static_cast<decltype(record.time.sec)>(sec.count());
  record.time.nsec = static_cast<decltype(record.time.nsec)>(nsec.count());

  switch (level)
  {
  case(0):
    record.level = OpenRTM::LogLevel::RTM_SILENT;
    break;
  case(1):
    record.level = OpenRTM::LogLevel::RTM_ERROR;
    break;
  case(2):
    record.level = OpenRTM::LogLevel::RTM_ERROR;
    break;
  case(3):
    record.level = OpenRTM::LogLevel::RTM_WARN;
    break;
  case(4):
    record.level = OpenRTM::LogLevel::RTM_INFO;
    break;
  case(5):
    record.level = OpenRTM::LogLevel::RTM_DEBUG;
    break;
  case(6):
    record.level = OpenRTM::LogLevel::RTM_TRACE;
    break;
  case(7):
    record.level = OpenRTM::LogLevel::RTM_VERBOSE;
    break;
  case(8):
    record.level = OpenRTM::LogLevel::RTM_PARANOID;
    break;
  default:
    record.level = OpenRTM::LogLevel::RTM_INFO;
  };
  
  record.loggername = CORBA::string_dup(name.c_str());
  record.message = CORBA::string_dup(mes.c_str());
  
  if (m_logger != nullptr)
  {
    try
    {
      m_logger->_ptr()->publish(record);
    }
    catch (...)
    {

    }
  }
}


SDOLogger::SDOLogger()
{
}

SDOLogger::~SDOLogger()
{
}

bool SDOLogger::init(const coil::Properties& prop)
{
  m_logstream.init(prop);
  return true;
}

coil::LogStreamBuffer* SDOLogger::getStreamBuffer()
{
  return &m_logstream;
}

void SDOLogger::setConsumer(RTC::CorbaConsumer<OpenRTM::Logger>* logger)
{
  m_logstream.setConsumer(logger);
}