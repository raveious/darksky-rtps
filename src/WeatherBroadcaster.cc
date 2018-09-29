#include "WeatherBroadcaster.hh"

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/Domain.h>

#include <iostream>
#include <exception>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

namespace Home {

WeatherBroadcaster::WeatherBroadcaster() {
    ParticipantAttributes PParam;
    PParam.rtps.setName("WeatherBroadcaster");
    PParam.rtps.builtin.domainId = 42;

    m_participant = Domain::createParticipant(PParam);

    if (m_participant == nullptr)
      throw std::runtime_error("Unable to create Domain Participant.");

    Domain::registerType(m_participant, &m_conditionType);
    Domain::registerType(m_participant, &m_forcastType);

    PublisherAttributes conditionsPubParam;
    conditionsPubParam.topic.topicDataType = "WeatherCondition";
    conditionsPubParam.topic.topicName = "/weather/conditions";

    m_conditionPub = Domain::createPublisher(m_participant, conditionsPubParam);

    if (m_conditionPub == nullptr)
      throw std::runtime_error("Unable to create Current Conditions Publisher.");

    PublisherAttributes dailyForcastPubParam;
    dailyForcastPubParam.topic.topicDataType = "WeatherForcast";
    dailyForcastPubParam.topic.topicName = "/weather/forcast/daily";

    m_dailyPub = Domain::createPublisher(m_participant, dailyForcastPubParam);

    if (m_dailyPub == nullptr)
      throw std::runtime_error("Unable to create Daily Forcast Publisher.");
}

WeatherBroadcaster::~WeatherBroadcaster(void) {
    Domain::removeParticipant(m_participant);
}

void WeatherBroadcaster::publish (web::json::value data) {
    data.serialize(std::cout);
}

void WeatherBroadcaster::publishConditions (web::json::value data) {

}

void WeatherBroadcaster::publishForcast (web::json::value data) {

}

} // namespace Home
