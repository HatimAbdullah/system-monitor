#include <string>
#include <iomanip>
#include "format.h"

#define AN_HOUR 3600
#define A_MINUTE 60

using std::string;

string Format::ElapsedTime(long totaltime) { 
    int hours;
    int minutes;
    int seconds;

    hours = totaltime / AN_HOUR;
    seconds = totaltime % AN_HOUR;
    minutes = seconds / A_MINUTE;
    seconds %= A_MINUTE;
    
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << hours << ":";
    stream << std::setfill('0') << std::setw(2) << minutes << ":";
    stream << std::setfill('0') << std::setw(2) << seconds;

    string timepassed = stream.str();

    //string timepassed = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
    return timepassed; 
}