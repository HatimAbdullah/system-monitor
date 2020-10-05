#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() {
  return this->pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  float uptime = (float) LinuxParser::UpTime(this->pid_); 
  float aj = (float) LinuxParser::ActiveJiffies(this->pid_);
  float tps = (float) sysconf(_SC_CLK_TCK);
  float ajinsec = (float) aj / tps;
  float cutil = (float) ajinsec / uptime;
  return cutil; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
  return this->cmd_; 
}

float round(float var) 
{ 
    // we use array of chars to store number 
    // as a string. 
    char str[40];  
  
    // Print in string the value of var  
    // with two decimal point 
    sprintf(str, "%.2f", var); 
  
    // scan string value in var  
    sscanf(str, "%f", &var);  
  
    return var;  
} 

// TODO: Return this process's memory utilization
string Process::Ram() { 
  float ram = LinuxParser::Ram(this->pid_);
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << ram;
  std::string prettyram = stream.str();
  return prettyram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return this->user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return LinuxParser::UpTime(this->pid_); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    if ( a.CpuUtilization() < this->CpuUtilization()) {
        return true;
    } else {
    return false; 
    }
}
