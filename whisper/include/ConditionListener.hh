#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>

#include "weather.h"
#include "weatherPubSubTypes.h"

#pragma once

namespace Home {

class ConditionListener: public eprosima::fastrtps::SubscriberListener {
  public:
    ConditionListener(void);
    virtual ~ConditionListener(void);

    void onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub, eprosima::fastrtps::MatchingInfo& info);

    void onNewDataMessage(eprosima::fastrtps::Subscriber* sub);

  private:

    WeatherCondition m_sample; //Storage for incoming messages
    eprosima::fastrtps::SampleInfo_t m_sample_info; //Auxiliary structure with meta-data on the message
};

}; // namespace Home
