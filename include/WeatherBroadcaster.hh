#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>

#include <cpprest/json.h>

#include "weather.h"
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
    void publishDailyForcast(web::json::value data);
    void publishHourlyForcast(web::json::value data);
    void publishAlerts (web::json::value data);

    WeatherIcon parseWeatherIcon (std::string text);
    PrecipType parsePrecipType (std::string text);
    Precipitation parsePrecipitation (web::json::value data);
    Atmospheric parseAtmospheric (web::json::value data);

    eprosima::fastrtps::Participant* m_participant;
    eprosima::fastrtps::Publisher* m_conditionPub;
    eprosima::fastrtps::Publisher* m_dailyPub;
    eprosima::fastrtps::Publisher* m_hourlyPub;
    eprosima::fastrtps::Publisher* m_alertPub;

    WeatherConditionPubSubType m_conditionType;
    WeatherForcastPubSubType m_forcastType;
};

}; // namespace Home
