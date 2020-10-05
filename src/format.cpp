#include <string>
#include "format.h"

#define AN_HOUR 3600
#define A_MINUTE 60

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long totaltime) { 
    int hours;
    int minutes;
    int seconds;

    hours = totaltime / AN_HOUR;
    seconds = totaltime % AN_HOUR;
    minutes = seconds / A_MINUTE;
    seconds %= A_MINUTE;

    string timepassed = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
    return timepassed; 
}