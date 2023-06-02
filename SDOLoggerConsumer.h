#ifndef RTC_SDOLOGGERCONSUMER_H
#define RTC_SDOLOGGERCONSUMER_H

#include "LoggerConsumer.h"
#include "SDOLogger.h"

class SDOLoggerConsumer : public RTC::LoggerConsumer
{
public:
	SDOLoggerConsumer();
	~SDOLoggerConsumer();
	bool init(RTC::RTObject_impl& rtobj,
		const SDOPackage::ServiceProfile& profile) override;
	bool reinit(const SDOPackage::ServiceProfile& profile) override;
	//const SDOPackage::ServiceProfile& getProfile() const override;
	void finalize() override;
private:
	SDOLogger m_sdologger;
};

extern "C"
{
	DLL_EXPORT void SDOLoggerConsumerInit();
}

#endif // RTC_SDOLOGGERCONSUMER_H