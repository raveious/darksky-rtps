# DarkSky RTPS Node
RTPS bridge for DarkSky API using eProsima's FastRTPS.

## What happened to Weather Underground?
 Turns out that Weather Underground will be [shutting down it's API service as of 12/31/2018](https://apicommunity.wunderground.com/weatherapi/topics/end-of-service-for-the-weather-underground-api), so I decided to use [DarkSky](https://darksky.net) instead.

# Requirements

These variables can be set as either Docker secrets, or just as environment variables.

Variable Name | Description
:---:|:---:
DARKSKY_KEY | API key that you get by signing up on DarkSky.
DARKSKY_LATITUDE | The latitude of the location you would like to publish.
DARKSKY_LONGITUDE | The longitude of the location you would like to publish.
DARKSKY_POLLING_RATE | Rate (in ms) at which DarkSky should be polled, and data published. With the [calling rate limit](https://darksky.net/dev/docs/faq), the default is set to 90 secs.

# Building

Building from source using cmake

```bash
$ git clone --recursive https://github.com/raveious/darksky-rtps.git darksky-rtps
$ cd darksky-rtps
$ mkdir build
$ cd build
$ cmake .. && make
```

# Data Sharing

This application will publish DarkSky API data on the following topics, using the corresponding data types in domain 42.

Topic Name | Data Type
:---:|:---:
/weather/conditions | WeatherCondition
/weather/alerts | WeatherAlert
/weather/forcast/hourly | WeatherForcast
/weather/forcast/daily | WeatherForcast
