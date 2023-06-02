#include "SDOLoggerConsumer.h"

SDOLoggerConsumer::SDOLoggerConsumer() : LoggerConsumer()
{
}

SDOLoggerConsumer::~SDOLoggerConsumer() = default;

bool SDOLoggerConsumer::init(RTC::RTObject_impl& rtobj,
	const SDOPackage::ServiceProfile& profile)
{
  coil::Properties prop;
  NVUtil::copyToProperties(prop, profile.properties);
  prop["comp.instance_name"] = rtobj.getInstanceName();
  m_sdologger.init(prop);
  m_sdologger.setConsumer(&m_logger);
  RTC::Manager::instance().getLogStreamBuf().addStream(m_sdologger.getStreamBuffer());
  return LoggerConsumer::init(rtobj, profile);
}

bool SDOLoggerConsumer::reinit(const SDOPackage::ServiceProfile& profile)
{
  RTC::Manager::instance().getLogStreamBuf().removeStream(m_sdologger.getStreamBuffer());
  RTC::Manager::instance().getLogStreamBuf().addStream(m_sdologger.getStreamBuffer());
  return LoggerConsumer::reinit(profile);
}

/*
const SDOPackage::ServiceProfile& SDOLoggerConsumer::getProfile() const
{

}
*/

void SDOLoggerConsumer::finalize()
{
  RTC::Manager::instance().getLogStreamBuf().removeStream(m_sdologger.getStreamBuffer());
  LoggerConsumer::finalize();
}


extern "C"
{
  void SDOLoggerConsumerInit()
  {
    RTC::SdoServiceConsumerFactory& factory
      = RTC::SdoServiceConsumerFactory::instance();
#ifndef ORB_IS_RTORB
    factory.addFactory(CORBA_Util::toRepositoryId<OpenRTM::Logger>(),
#else
    factory.addFactory(CORBA_Util::toRepositoryId<OpenRTM::Logger_ptr>(),
#endif
      ::coil::Creator< ::RTC::SdoServiceConsumerBase,
      SDOLoggerConsumer>,
      ::coil::Destructor< ::RTC::SdoServiceConsumerBase,
      SDOLoggerConsumer>);
  }
}