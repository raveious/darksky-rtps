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

std::string get_configuration_data(std::string key) {
    // Open up a Docker secret file for reading data from it
    std::fstream fs;
    fs.open ("/run/secrets/" + key, std::fstream::in);

    std::string retVal;

    if (fs.is_open()){
        fs >> retVal;
    } else {
        // If that didn't work, look for an environment variable instead.
        char* temp = nullptr;
        if ((temp = std::getenv(key.c_str())) != nullptr) {
            retVal = std::string(temp);
        }
    }

    // Throw an exception if we couldn't find anything
    if (retVal.empty()) {
        throw std::runtime_error("Unable to find a value for " + key + ".");
    }

    return retVal;
}

int main(int argc, char const *argv[]) {

    // Check for all of the things
    std::string key;
    try {
        key = get_configuration_data("DARKSKY_KEY");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine DarkSky API key: " << e.what() << std::endl;
        return -1;
    }

    std::string latitude;
    try {
        latitude = get_configuration_data("DARKSKY_LATITUDE");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine latitude for DarkSky API: " << e.what() << std::endl;
        return -2;
    }

    std::string longitude;
    try {
        longitude = get_configuration_data("DARKSKY_LONGITUDE");
    } catch (std::exception& e) {
        std::cerr << "Unable to determine longitude for DarkSky API: " << e.what() << std::endl;
        return -3;
    }

    std::chrono::milliseconds polling_rate;
    try {
        polling_rate = std::chrono::milliseconds(std::stoi(get_configuration_data("DARKSKY_POLLING_RATE")));
    } catch (std::exception& e) {
        std::cout << "Unable to determine DarkSky API polling rate, so we're just going to use 3000ms: " << e.what() << std::endl;
        polling_rate = std::chrono::milliseconds(3000);
    }

    const uri weather_uri = uri_builder(U("https://api.darksky.net/forecast/98899c22b8f6057b063959ffd7086e4e/42.488769,-71.154438")).to_uri();

    // Creating client to make calls with
    http_client client(weather_uri);

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
            .then([](pplx::task<json::value> previousTask)
        {
            try
            {
                const json::value& v = previousTask.get();
                // Perform actions here to process the JSON value...

                v.serialize(std::cout);
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
    }
}
