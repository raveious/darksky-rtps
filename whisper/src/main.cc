#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/Domain.h>

#include "ConditionListener.hh"

#include <iostream>
#include <exception>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace Home;

int main(int argc, char const *argv[]) {
    ParticipantAttributes PParam;
    PParam.rtps.setName("WeatherSubscriber");
    PParam.rtps.builtin.domainId = 42;

    // Create a participant
    Participant* participant = Domain::createParticipant(PParam);

    // Make sure that the participant was created
    if (participant == nullptr)
      throw std::runtime_error("Unable to create Domain Participant.");

    // Register types
    WeatherConditionPubSubType conditionType;

    Domain::registerType(participant, &conditionType);

    // Set a topic name
    SubscriberAttributes sub_attr;
    sub_attr.topic.topicDataType = "WeatherCondition";
    sub_attr.topic.topicName = "/weather/conditions";

    // Create a subscriber with our subscriber listener
    ConditionListener sub_listener;
    Subscriber* subscriber = Domain::createSubscriber(participant, sub_attr, &sub_listener);

    // Check to make sure that the subscriber actually worked...
    if (subscriber == nullptr)
        throw std::runtime_error("Unable to create subscriber");

    // Just pause and let the subscriber listener print stuff
    std::cin.ignore();

    // Remove participant when we're done
    Domain::removeParticipant(participant);

    return 0;
}
