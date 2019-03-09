#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri_builder.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <exception>

using namespace web;
using namespace http;
using namespace client;

template <typename T> T get_configuration_data(std::string key) {
    // Open up a Docker secret file for reading data from it
    std::fstream fs("/run/secrets/" + key, std::fstream::in);
    T retVal;
    char* temp = nullptr;

    if (fs.is_open()) {
        // Read the contents of the file.
        fs >> retVal;
    } else if ((temp = std::getenv(key.c_str())) != nullptr) {
        // Try to see if we can find that value from the environment instead?
        std::stringstream ss(temp);
        ss >> retVal;
    } else {
        // Throw an exception if we couldn't find anything
        throw std::runtime_error("Unable to find a value for " + key + ".");
    }

    return retVal;
}

int main(int argc, char const *argv[]) {
/*    uri_builder weather_uri(U("https://api.darksky.net/forecast/"));

    // Check for all of the things
    std::string key;
    try {
        key = get_configuration_data<std::string>("DARKSKY_KEY");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine DarkSky API key: " << e.what() << std::endl;
        return -1;
    }

    weather_uri.append_path(key);

    double latitude;
    try {
        latitude = get_configuration_data<double>("DARKSKY_LATITUDE");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine latitude for DarkSky API: " << e.what() << std::endl;
        return -2;
    }

    double longitude;
    try {
        longitude = get_configuration_data<double>("DARKSKY_LONGITUDE");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine longitude for DarkSky API: " << e.what() << std::endl;
        return -3;
    }

    std::stringstream ss;
    ss << latitude << ',' << longitude;
    weather_uri.append(ss.str());

    std::chrono::milliseconds polling_rate;
    try {
        polling_rate = std::chrono::milliseconds(get_configuration_data<int>("DARKSKY_POLLING_RATE"));
    } catch (std::exception& e) {
        std::cout << "Unable to determine DarkSky API polling rate, so we're just going to use 90000ms (90sec): " << e.what() << std::endl;
        polling_rate = std::chrono::milliseconds(90000);
    }

    weather_uri.set_query("exclude=minutely,flags");

    // Creating client to make calls with
    http_client client(weather_uri.to_uri());
    Home::WeatherBroadcaster broadcaster;

    while (true) {
        client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
        {
            if(response.status_code() == status_codes::OK)
            {
                return response.extract_json();
            }

            // Handle error cases, for now return empty json value...
            return pplx::task_from_result(json::value());
        })
            .then([&broadcaster](pplx::task<json::value> previousTask)
        {
            try
            {
                const json::value& v = previousTask.get();
                // Perform actions here to process the JSON value...
                broadcaster.publish(v);
            }
            catch (const http_exception& e)
            {
                // Print error.
                std::ostringstream ss;
                ss << e.what() << std::endl;
                std::cout << ss.str();
            }
        });

        // Sleep for some amount of time
        std::this_thread::sleep_for(polling_rate);
    }*/
}
