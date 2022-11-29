#include "JsonParse.h"
#pragma once
///////////////////////////////////////////////////////////
// JsonParse.cpp
// JsonParse.cpp is the implmentation class that reads a json .txt file and converts that to a object 
// that contains all the stats stored in the Json.
// This class holds all the tools necessary for manipulating the Json object
// 
// CSE 681 Software Modeling
// Project 1 
// Jiawen Zhen
///////////////////////////////////////////////////////////


JsonParse::JsonGameObj gameArray[20];

JsonParse::JsonParse(std::string filename)
{
    ifstream txtfile; // create the object for txtfile
    txtfile.open(filename); // open said file
    string line;
    string firstWord;
    string inputWord;
    int brackOpen = 0;
    int brackClose = 0;
    int i = 0; // numGames

    if (txtfile.is_open())
    {
        while (txtfile) //while not end of file
        {
            getline(txtfile, line);

            if (line.find("{") != std::string::npos) {
                brackOpen++;
            }
            if (line.compare("[") != 0 && line.compare("]") != 0) {
                if (line.find("\"neutral\":") != std::string::npos) {
                    gameArray[i].neutral = findSecondWord(line);
                }
                if (line.find("\"visTeamName\":") != std::string::npos) {
                    gameArray[i].visTeamName = findSecondWord(line);
                }
                if (line.find("\"visStats\":") != std::string::npos) {
                    while (line.find("},") == std::string::npos) {
                        getline(txtfile, line);
                        fillVisitStats(line, i);
                    }
                }
                if (line.find("\"homeTeamName\":") != std::string::npos) {
                    gameArray[i].homeTeamName = findSecondWord(line);
                }
                else if (line.find("\"homeStats\":") != std::string::npos) {
                    while (line.find("},") == std::string::npos) {
                        getline(txtfile, line);
                        fillHomeStats(line, i);
                    }
                }
                if (line.find("\"isFinal\":") != std::string::npos) {
                    gameArray[i].isFinal = findSecondWord(line);
                }
                if (line.find("\"date\":") != std::string::npos) {
                    gameArray[i].date = findSecondWord(line);
                    i++; //increment to know which game in the json we are on
                }
            }
        }
        txtfile.close();
    }

    else cout << "Unable to open file";

}

std::string JsonParse::connect(std::string webUrl)
{

    return "hi";
}

void JsonParse::getter() // purpose of this function is to get input from the user and parse the json txt file into a readable format
{
    int year;
    int month;
    int day;
    string dateString;
    std::stringstream MM;
    std::stringstream DD;
    int index = 0;
    int prntIndex = -1;

    cout << "Please enter a date to run the data on. Please enter whole integers:" << endl;
    cout << "Year: ";
    cin >> year;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    MM << std::setw(2) << std::setfill('0') << month;
    DD << std::setw(2) << std::setfill('0') << day;
    dateString = std::to_string(year) + "-" + MM.str() + "-" + DD.str();
    while (index <= 20) {
        if (gameArray[index].date.find(dateString) != std::string::npos) {
            prntIndex = index;
            break;
        }
        index++;
    }
    if (prntIndex == -1) {
        cout << "Entry not found in table" << endl;
    }
    else {
        printStats(prntIndex);
    }

}

void JsonParse::setter(std::string inputStr)
{
    int year;
    int month;
    int day;
    string dateString;
    std::stringstream MM;
    std::stringstream DD;
    int index = 0;
    int prntIndex = -1;

    cout << "Please enter a date to set the data on. Please enter whole integers:" << endl;
    cout << "Year: ";
    cin >> year;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    MM << std::setw(2) << std::setfill('0') << month;
    DD << std::setw(2) << std::setfill('0') << day;
    dateString = std::to_string(year) + "-" + MM.str() + "-" + DD.str();
    while (index <= 20) {
        if (gameArray[index].date.find(dateString) != std::string::npos) {
            prntIndex = index;
            break;
        }
        index++;
    }
    if (prntIndex == -1) {
        cout << "Entry not found in table" << endl;
    }
    else {
        gameArray[index].HomeTeamStats.passYds = inputStr;
        cout << "Test that the setter worked properly." << endl;
        cout << "The home team's passing yards were: " + gameArray[index].HomeTeamStats.passYds << endl; //query json object
    }
}

string JsonParse::findSecondWord(std::string line)
{
    string::size_type ind = 0;
    ind = line.find_first_not_of(" \t", ind);
    ind = line.find_first_of(" \t", ind);
    line.erase(0, line.find_first_not_of(" \t", ind));
    if (line.back() == ',') {
        line.pop_back();
    }
    return line;
}

void JsonParse::fillVisitStats(std::string line, int i) //function for obtaining the visiting team stats
{
    if (line.find("\"statIdCode\":") != std::string::npos) {
        gameArray[i].VisTeamStats.statIdCode = findSecondWord(line);
    }
    else if (line.find("\"gameCode\":") != std::string::npos) {
        gameArray[i].VisTeamStats.gameCode = findSecondWord(line);
    }
    else if (line.find("\"teamCode\":") != std::string::npos) {
        gameArray[i].VisTeamStats.teamCode = findSecondWord(line);
    }
    else if (line.find("\"gameDate\":") != std::string::npos) {
        gameArray[i].VisTeamStats.gameDate = findSecondWord(line);
    }
    else if (line.find("\"rushYds\":") != std::string::npos) {
        gameArray[i].VisTeamStats.rushYds = findSecondWord(line);
    }
    else if (line.find("\"rushAtt\":") != std::string::npos) {
        gameArray[i].VisTeamStats.rushAtt = findSecondWord(line);
    }
    else if (line.find("\"passYds\":") != std::string::npos) {
        gameArray[i].VisTeamStats.passYds = findSecondWord(line);
    }
    else if (line.find("\"passAtt\":") != std::string::npos) {
        gameArray[i].VisTeamStats.passAtt = findSecondWord(line);
    }
    else if (line.find("\"passComp\":") != std::string::npos) {
        gameArray[i].VisTeamStats.passComp = findSecondWord(line);
    }
    else if (line.find("\"penalties\":") != std::string::npos) {
        gameArray[i].VisTeamStats.penalties = findSecondWord(line);
    }
    else if (line.find("\"penaltYds\":") != std::string::npos) {
        gameArray[i].VisTeamStats.penaltYds = findSecondWord(line);
    }
    else if (line.find("\"fumblesLost\":") != std::string::npos) {
        gameArray[i].VisTeamStats.fumblesLost = findSecondWord(line);
    }
    else if (line.find("\"interceptionsThrown\":") != std::string::npos) {
        gameArray[i].VisTeamStats.interceptionsThrown = findSecondWord(line);
    }
    else if (line.find("\"firstDowns\":") != std::string::npos) {
        gameArray[i].VisTeamStats.firstDowns = findSecondWord(line);
    }
    else if (line.find("\"thirdDownAtt\":") != std::string::npos) {
        gameArray[i].VisTeamStats.thirdDownAtt = findSecondWord(line);
    }
    else if (line.find("\"thirdDownConver\":") != std::string::npos) {
        gameArray[i].VisTeamStats.thirdDownConver = findSecondWord(line);
    }
    else if (line.find("\"fourthDownAtt\":") != std::string::npos) {
        gameArray[i].VisTeamStats.fourthDownAtt = findSecondWord(line);
    }
    else if (line.find("\"fourthDownConver\":") != std::string::npos) {
        gameArray[i].VisTeamStats.fourthDownConver = findSecondWord(line);
    }
    else if (line.find("\"timePoss\":") != std::string::npos) {
        gameArray[i].VisTeamStats.timePoss = findSecondWord(line);
    }
    else if (line.find("\"score\":") != std::string::npos) {
        gameArray[i].VisTeamStats.score = findSecondWord(line);
    }
}

void JsonParse::fillHomeStats(std::string line, int i) // function for obtaining the home team stats
{
    if (line.find("\"statIdCode\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.statIdCode = findSecondWord(line);
    }
    else if (line.find("\"gameCode\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.gameCode = findSecondWord(line);
    }
    else if (line.find("\"teamCode\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.teamCode = findSecondWord(line);
    }
    else if (line.find("\"gameDate\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.gameDate = findSecondWord(line);
    }
    else if (line.find("\"rushYds\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.rushYds = findSecondWord(line);
    }
    else if (line.find("\"rushAtt\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.rushAtt = findSecondWord(line);
    }
    else if (line.find("\"passYds\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.passYds = findSecondWord(line);
    }
    else if (line.find("\"passAtt\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.passAtt = findSecondWord(line);
    }
    else if (line.find("\"passComp\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.passComp = findSecondWord(line);
    }
    else if (line.find("\"penalties\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.penalties = findSecondWord(line);
    }
    else if (line.find("\"penaltYds\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.penaltYds = findSecondWord(line);
    }
    else if (line.find("\"fumblesLost\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.fumblesLost = findSecondWord(line);
    }
    else if (line.find("\"interceptionsThrown\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.interceptionsThrown = findSecondWord(line);
    }
    else if (line.find("\"firstDowns\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.firstDowns = findSecondWord(line);
    }
    else if (line.find("\"thirdDownAtt\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.thirdDownAtt = findSecondWord(line);
    }
    else if (line.find("\"thirdDownConver\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.thirdDownConver = findSecondWord(line);
    }
    else if (line.find("\"fourthDownAtt\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.fourthDownAtt = findSecondWord(line);
    }
    else if (line.find("\"fourthDownConver\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.fourthDownConver = findSecondWord(line);
    }
    else if (line.find("\"timePoss\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.timePoss = findSecondWord(line);
    }
    else if (line.find("\"score\":") != std::string::npos) {
        gameArray[i].HomeTeamStats.score = findSecondWord(line);
    }
}

void JsonParse::printStats(int i)
{
    cout << "The game you selected occured on " + gameArray[i].date << endl;
    cout << "The home team was " + gameArray[i].visTeamName + " and the away team was "
        + gameArray[i].homeTeamName << endl;
    cout << "The score was " + gameArray[i].visTeamName + " " + gameArray[i].VisTeamStats.score
        + " to " + gameArray[i].homeTeamName + " " + gameArray[i].HomeTeamStats.score << endl << endl;
    cout << "The home team " + gameArray[i].homeTeamName + " had the following stats: " << endl;
    cout << gameArray[i].HomeTeamStats.rushYds + " Rushing Yards on " + gameArray[i].HomeTeamStats.rushAtt
        + " Rush Attempts." << endl;
    cout << gameArray[i].HomeTeamStats.passYds + " Passing Yards on " + gameArray[i].HomeTeamStats.passAtt
        + " Pass Attempts with " + gameArray[i].HomeTeamStats.passComp + " completions." << endl;
    cout << gameArray[i].HomeTeamStats.penalties + " penalties for " + gameArray[i].HomeTeamStats.penaltYds
        + " penalty yards." << endl;
    cout << gameArray[i].HomeTeamStats.fumblesLost + " fumbles lost and "
        + gameArray[i].HomeTeamStats.interceptionsThrown + " interceptions thrown." << endl;
    cout << gameArray[i].HomeTeamStats.firstDowns + " First downs with " + gameArray[i].HomeTeamStats.thirdDownAtt
        + " Third downs attempted at " + gameArray[i].HomeTeamStats.thirdDownConver + " Third downs converted." << endl;
    cout << gameArray[i].HomeTeamStats.fourthDownAtt + " Fourth downs with " + gameArray[i].HomeTeamStats.fourthDownConver
        + " Fourth downs converted." << endl << endl;

    cout << "The away team " + gameArray[i].visTeamName + " had the following stats: " << endl;
    cout << gameArray[i].VisTeamStats.rushYds + " Rushing Yards on " + gameArray[i].VisTeamStats.rushAtt
        + " Rush Attempts." << endl;
    cout << gameArray[i].VisTeamStats.passYds + " Passing Yards on " + gameArray[i].VisTeamStats.passAtt
        + " Pass Attempts with " + gameArray[i].VisTeamStats.passComp + " completions." << endl;
    cout << gameArray[i].VisTeamStats.penalties + " penalties for " + gameArray[i].VisTeamStats.penaltYds
        + " penalty yards." << endl;
    cout << gameArray[i].VisTeamStats.fumblesLost + " fumbles lost and "
        + gameArray[i].VisTeamStats.interceptionsThrown + " interceptions thrown." << endl;
    cout << gameArray[i].VisTeamStats.firstDowns + " First downs with " + gameArray[i].VisTeamStats.thirdDownAtt
        + " Third downs attempted at " + gameArray[i].VisTeamStats.thirdDownConver + " Third downs converted." << endl;
    cout << gameArray[i].VisTeamStats.fourthDownAtt + " Fourth downs with " + gameArray[i].VisTeamStats.fourthDownConver
        + " Fourth downs converted." << endl << endl;
}