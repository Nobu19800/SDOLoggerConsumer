#ifndef SDOLogger_H
#define SDOLogger_H


#include <rtm/LogstreamBase.h>
#include <rtm/CorbaConsumer.h>
#include "LoggerStub.h"

class SDOLoggerStream
  : public coil::LogStreamBuffer
{
public:
  SDOLoggerStream();
  ~SDOLoggerStream() override;
  bool init(const coil::Properties& prop);
  void write(int level, const std::string& name, const std::string& date, const std::string& mes) override;
  void setConsumer(RTC::CorbaConsumer<OpenRTM::Logger>* logger);
private:
  unsigned int m_level;
  std::string m_instance_name;
  RTC::CorbaConsumer<OpenRTM::Logger> *m_logger;
};

class SDOLogger
  : public RTC::LogstreamBase
{
public:
  SDOLogger();
  ~SDOLogger() override;
  bool init(const coil::Properties& prop) override;
  coil::LogStreamBuffer* getStreamBuffer() override;
  void setConsumer(RTC::CorbaConsumer<OpenRTM::Logger>* logger);
private:
  SDOLoggerStream m_logstream;
};

#endif