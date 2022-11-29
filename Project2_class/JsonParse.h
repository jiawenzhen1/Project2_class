#pragma once
///////////////////////////////////////////////////////////
// JsonParse.h
// JsonParse.h is the header class for the implementation class JsonParse.cpp
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
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <curl/curl.h>

// Add using declarations to allow us to utilize input/output functions within the c++ standard library  
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;


class JsonParse {

public:
    // Use a constructor to initialize the reading the JSON text
    JsonParse(std::string txtfile);
    // Member function for printing the JSON text to the display
    std::string connect(std::string);
    void getter();
    void setter(std::string);
    string findSecondWord(std::string);

    struct JsonGameObj {
        std::string neutral;
        std::string visTeamName;
        std::string homeTeamName;
        std::string isFinal;
        std::string date;

        struct VisTeamStats {
            std::string statIdCode;
            std::string gameCode;
            std::string teamCode;
            std::string gameDate;
            std::string rushYds;
            std::string rushAtt;
            std::string passYds;
            std::string passAtt;
            std::string passComp;
            std::string penalties;
            std::string penaltYds;
            std::string fumblesLost;
            std::string interceptionsThrown;
            std::string firstDowns;
            std::string thirdDownAtt;
            std::string thirdDownConver;
            std::string fourthDownAtt;
            std::string fourthDownConver;
            std::string timePoss;
            std::string score;
        } VisTeamStats;

        struct HomeTeamStats {
            std::string statIdCode;
            std::string gameCode;
            std::string teamCode;
            std::string gameDate;
            std::string rushYds;
            std::string rushAtt;
            std::string passYds;
            std::string passAtt;
            std::string passComp;
            std::string penalties;
            std::string penaltYds;
            std::string fumblesLost;
            std::string interceptionsThrown;
            std::string firstDowns;
            std::string thirdDownAtt;
            std::string thirdDownConver;
            std::string fourthDownAtt;
            std::string fourthDownConver;
            std::string timePoss;
            std::string score;
        } HomeTeamStats;
    };

    void fillVisitStats(std::string line, int i);
    void fillHomeStats(std::string line, int i);
    void printStats(int i);

private:




};