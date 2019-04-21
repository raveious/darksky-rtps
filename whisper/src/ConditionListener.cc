#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/Domain.h>

#include "ConditionListener.hh"

#include <iostream>
#include <chrono>
#include <ctime>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

namespace Home {

ConditionListener::ConditionListener(void) {

}

ConditionListener::~ConditionListener(void) {

}

void ConditionListener::onSubscriptionMatched(Subscriber* /*sub*/, MatchingInfo& info) {
  info = info; // Make unused warning go away while in release

  // Only want this stuff to print out while in debug mode
  #ifndef NDEBUG
    if (info.status == MATCHED_MATCHING)
      std::cout << "Subscriber Matched" << std::endl;
    else
      std::cout << "Subscriber Unmatched" << std::endl;
  #endif
}

void ConditionListener::onNewDataMessage(Subscriber* sub) {
  if (sub->takeNextData((void*)&m_sample, &m_sample_info)) {
    if (m_sample_info.sampleKind == ALIVE) {
      std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

      std::cout << "New data at " << std::ctime(&now) << std::endl;

      std::cout << m_sample.summary() << std::endl;
      std::cout << "It is " << m_sample.apparentTemperature() << " degrees outside." << std::endl;
    }
  }
}

}; // namespace Home
