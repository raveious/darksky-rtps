# DarkSky RTPS Node
RTPS bridge for DarkSky API using eProsima's FastRTPS.

## What happened to Weather Underground?
 Turns out that Weather Underground will be [shutting down it's API service as on 12/31/2018](https://apicommunity.wunderground.com/weatherapi/topics/end-of-service-for-the-weather-underground-api), so I decided to use [DarkSky](https://darksky.net) instead.

# Requirements

These variables can be set as either Docker secrets, or just as environment variables

- DARKSKY_KEY
- DARKSKY_LATITUDE
- DARKSKY_LONGITUDE
- DARKSKY_POLLING_RATE

# Building

Building from source using cmake

```bash
$ git clone https://github.com/raveious/darksky-rtps.git darksky-rtps
$ cd darksky-rtps
$ git submodule init && git submodule update
$ mkdir build
$ cd build
$ cmake .. && make
```

# Data Sharing

This application will publish DarkSky API data on the following topics, using the corresponding data types.

Topic Name | Data Type
:---:|:---:
/weather/conditions | WeatherCondition
/weather/forcast/minutely | WeatherForcast
/weather/forcast/hourly | WeatherForcast
/weather/forcast/daily | WeatherForcast
