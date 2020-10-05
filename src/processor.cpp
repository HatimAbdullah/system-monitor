#include "processor.h"
#include "linux_parser.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float util = (float) LinuxParser::ActiveJiffies() / LinuxParser::Jiffies();
    return util; 
}