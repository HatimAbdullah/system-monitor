#include "processor.h"
#include "linux_parser.h"
#include <iostream>

float Processor::Utilization() { 
    float util = static_cast<float>(LinuxParser::ActiveJiffies()) / LinuxParser::Jiffies();
    return util; 
}