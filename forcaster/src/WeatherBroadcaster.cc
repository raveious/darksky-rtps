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
    if (data.has_field("currently"))
        publishConditions(data.at("currently"));

    if (data.has_field("daily"))
        publishDailyForcast(data.at("daily"));

    if (data.has_field("hourly"))
        publishHourlyForcast(data.at("hourly"));

    if (data.has_field("alerts"))
        publishAlerts(data.at("alerts"));
}

void WeatherBroadcaster::publishConditions (web::json::value data) {
    #ifndef NDEBUG
        data.serialize(std::cout);
        std::cout << std::endl << std::endl;
    #endif
    WeatherCondition pubData;

    pubData.apparentTemperature(data.at("apparentTemperature").as_double());
    pubData.temperature(data.at("temperature").as_double());

    pubData.time(data.at("time").as_integer());

    pubData.summary(data.at("summary").as_string());
    pubData.icon(parseWeatherIcon(data.at("icon").as_string()));

    pubData.precipitationData(parsePrecipitation(data));
    pubData.atmosphericData(parseAtmospheric(data));

    m_conditionPub->write((void*) &pubData);
}

void WeatherBroadcaster::publishDailyForcast (web::json::value data) {
    WeatherForcast pubData;
    std::vector<DailyWeather> forcastData;

    pubData.summary(data.at("summary").as_string());
    pubData.icon(parseWeatherIcon(data.at("icon").as_string()));

    auto jsonForcast = data.at("data").as_array();

    for (web::json::array::iterator it = jsonForcast.begin(); it != jsonForcast.end(); ++it) {
        #ifndef NDEBUG
            it->serialize(std::cout);
            std::cout << std::endl << std::endl;
        #endif

        DailyWeather temp;

        temp.time(it->at("time").as_integer());
        temp.apparentTemperatureHighTime(it->at("apparentTemperatureHighTime").as_integer());
        temp.apparentTemperatureLowTime(it->at("apparentTemperatureLowTime").as_integer());
        temp.sunriseTime(it->at("sunriseTime").as_integer());
        temp.sunsetTime(it->at("sunsetTime").as_integer());
        temp.temperatureHighTime(it->at("temperatureHighTime").as_integer());
        temp.temperatureLowTime(it->at("temperatureLowTime").as_integer());

        temp.summary(it->at("summary").as_string());
        temp.icon(parseWeatherIcon(it->at("icon").as_string()));

        temp.apparentTemperatureHigh(it->at("apparentTemperatureHigh").as_double());
        temp.apparentTemperatureLow(it->at("apparentTemperatureLow").as_double());
        temp.moonPhase(it->at("moonPhase").as_double());
        temp.temperatureHigh(it->at("temperatureHigh").as_double());
        temp.temperatureLow(it->at("temperatureLow").as_double());

        temp.precipitationData(parsePrecipitation(*it));
        temp.atmosphericData(parseAtmospheric(*it));

        forcastData.push_back(temp);
    }

    pubData.forcast(forcastData);

    m_dailyPub->write((void*) &pubData);
}

void WeatherBroadcaster::publishHourlyForcast (web::json::value data) {
    WeatherForcast pubData;
    std::vector<DailyWeather> forcastData;

    pubData.summary(data.at("summary").as_string());
    pubData.icon(parseWeatherIcon(data.at("icon").as_string()));

    auto jsonForcast = data.at("data").as_array();

    for (web::json::array::iterator it = jsonForcast.begin(); it != jsonForcast.end(); ++it) {
        #ifndef NDEBUG
            it->serialize(std::cout);
            std::cout << std::endl << std::endl;
        #endif

        DailyWeather temp;

        temp.apparentTemperature(it->at("apparentTemperature").as_double());
        temp.temperature(it->at("temperature").as_double());

        temp.time(it->at("time").as_integer());

        temp.summary(it->at("summary").as_string());
        temp.icon(parseWeatherIcon(it->at("icon").as_string()));

        temp.precipitationData(parsePrecipitation(*it));
        temp.atmosphericData(parseAtmospheric(*it));

        forcastData.push_back(temp);
    }

    pubData.forcast(forcastData);

    m_dailyPub->write((void*) &pubData);
}

void WeatherBroadcaster::publishAlerts (web::json::value data) {

}

WeatherIcon WeatherBroadcaster::parseWeatherIcon (std::string text) {
    if (text == "clear-night")
        return WeatherIcon::CLEAR_NIGHT;
    if (text == "rain")
        return WeatherIcon::RAIN;
    if (text == "snow")
        return WeatherIcon::SNOW;
    if (text == "sleet")
        return WeatherIcon::SLEET;
    if (text == "wind")
        return WeatherIcon::WIND;
    if (text == "fog")
        return WeatherIcon::FOG;
    if (text == "cloudy")
        return WeatherIcon::CLOUDY;
    if (text == "partly-cloudy-day")
        return WeatherIcon::PARTLY_CLOUDY_DAY;
    if (text == "partly-cloudy-night")
        return WeatherIcon::PARTLY_CLOUDY_NIGHT;
    if (text == "hail")
        return WeatherIcon::HAIL;
    if (text == "thunderstorm")
        return WeatherIcon::THUNDERSTORM;
    if (text == "tornado")
        return WeatherIcon::TORNADO;

    return WeatherIcon::CLEAR_DAY;
}

PrecipType WeatherBroadcaster::parsePrecipType (std::string text) {
    if (text == "rain")
        return PrecipType::RAINING;
    if (text == "snow")
        return PrecipType::SNOWING;
    if (text == "sleet")
        return PrecipType::SLEETING;

    return PrecipType::NO_PRECIP;
}

Precipitation WeatherBroadcaster::parsePrecipitation (web::json::value data) {
    Precipitation retVal;

    retVal.precipIntensity(data.at("precipIntensity").as_double());
    retVal.precipProbability(data.at("precipProbability").as_double());

    // This data is not always present...
    if (data.has_field("precipType"))
        retVal.precipType(parsePrecipType(data.at("precipType").as_string()));

    if (data.has_field("precipIntensityError"))
        retVal.precipProbability(data.at("precipIntensityError").as_double());

    if (data.has_field("precipAccumulation"))
        retVal.precipProbability(data.at("precipAccumulation").as_double());

    if (data.has_field("precipIntensityMax"))
        retVal.precipProbability(data.at("precipIntensityMax").as_double());

    return retVal;
}


Atmospheric WeatherBroadcaster::parseAtmospheric (web::json::value data) {
    Atmospheric retVal;

    retVal.cloudCover(data.at("cloudCover").as_double());
    retVal.dewPoint(data.at("dewPoint").as_double());
    retVal.humidity(data.at("humidity").as_double());
    retVal.ozone(data.at("ozone").as_double());
    retVal.pressure(data.at("pressure").as_double());
    retVal.uvIndex(data.at("uvIndex").as_double());
    retVal.visibility(data.at("visibility").as_double());
    retVal.windBearing(data.at("windBearing").as_double());
    retVal.windGust(data.at("windGust").as_double());
    retVal.windSpeed(data.at("windSpeed").as_double());

    // This data is not always present...
    if (data.has_field("uvIndexTime"))
        retVal.uvIndexTime(data.at("uvIndexTime").as_integer());

    if (data.has_field("windGustTime"))
        retVal.windGustTime(data.at("windGustTime").as_integer());

    return retVal;
}

} // namespace Home
