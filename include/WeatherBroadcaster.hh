#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>

#include <cpprest/json.h>

#include "weatherPubSubTypes.h"

#pragma once

namespace Home {

class WeatherBroadcaster {
  public:
    WeatherBroadcaster();
    virtual ~WeatherBroadcaster() noexcept;

    void publish(web::json::value data);

  private:
    void publishConditions (web::json::value data);
    void publishForcast(web::json::value data);

    eprosima::fastrtps::Participant* m_participant;
    eprosima::fastrtps::Publisher* m_conditionPub;
    eprosima::fastrtps::Publisher* m_dailyPub;

    WeatherConditionPubSubType m_conditionType;
    WeatherForcastPubSubType m_forcastType;
};

}; // namespace Home
