#pragma once
///////////////////////////////////////////////////////////
// Main.cpp
// Main is the start of the program and is the driver that enables the project to run
// In main we create the Json object which initializes an internal struct of structs that acts
// as the data store for all json txt.
// Here we will call methods inside of the json object to manipulate the object such as the setter
// and getter.
// 
// CSE 681 Software Modeling
// Project 1 
// Jiawen Zhen
// 
// Revision 1
// Date 10/30/2022
// 
///////////////////////////////////////////////////////////


// Use preprocessor directives to allow us to utilize input/output and access BarChartPrint class
#include <iostream>
#include "JsonParse.h";
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

// Add using declarations to allow us to utilize input/output functions within the c++ standard library  
using std::cout;
using std::cin;
using std::endl;
bool validWord = true;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


int main(int argc, char** argv) {

    cout << "****************************************************************" << endl;
    cout << "This program reads in a JSON file, creates an object and allows" << endl;
    cout << "user to to read or add to the JSON object" << endl;
    cout << "****************************************************************" << endl;


    /*
    JsonParse JsonParse("team49ers_season2020.txt"); // Run the parser 
    cout << "Json Object generated" << endl;
    JsonParse.getter(); // read json object
    std::string inputStr;
    cout << "Invoke test for setter. Change the home team stats for passing yards. Please enter integer: " << endl;
    cin >> inputStr;
    for (int i = 0; i < inputStr.length(); i++) { // check if user input is valid
        if (!isdigit(inputStr[i])) {
            validWord = false;
            break;
        }
    }
    if (validWord) {
        JsonParse.setter(inputStr); // set data in json object
    }
    else {
        cout << "Invalid user input" << endl;
    }
    */

    // Open stream to output file.
    auto fileStream = std::make_shared<ostream>();

    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
        {
            *fileStream = outFile;

            // Create http_client to send the request.
            http_client client(U("https://sports.snoozle.net/search/nfl/index.jsp?error=true"));

            // Build request URI and start the request.
            uri_builder builder(U("/search"));
            builder.append_query(U("q"), U("cpprestsdk github"));
            return client.request(methods::GET, builder.to_string());
        })

        // Handle response headers arriving.
            .then([=](http_response response)
                {
                    printf("Received response status code:%u\n", response.status_code());

                    // Write response body into the file.
                    return response.body().read_to_end(fileStream->streambuf());
                })

            // Close the file stream.
                    .then([=](size_t)
                        {
                            return fileStream->close();
                        });

                // Wait for all the outstanding I/O to complete and handle any exceptions
                try
                {
                    requestTask.wait();
                }
                catch (const std::exception& e)
                {
                    printf("Error exception:%s\n", e.what());
                }
 return 0;
}