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

int Process::Pid() {
  return this->pid_; 
}

float Process::CpuUtilization() const { 
  const float uptime = (float) LinuxParser::UpTime(this->pid_); 
  const float aj = (float) LinuxParser::ActiveJiffies(this->pid_);
  const float tps = (float) sysconf(_SC_CLK_TCK);
  const float ajinsec = (float) aj / tps;
  const float cutil = (float) ajinsec / uptime;
  return cutil; 
}

string Process::Command() { 
  return this->cmd_; 
}

string Process::Ram() { 
  float ram = LinuxParser::Ram(this->pid_);
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << ram;
  std::string prettyram = stream.str();
  return prettyram; 
}

string Process::User() { 
  return this->user_; 
}

long int Process::UpTime() { 
  return LinuxParser::UpTime(this->pid_); 
}

bool Process::operator<(Process const& a) const {
    if ( a.CpuUtilization() < this->CpuUtilization()) {
        return true;
    } else {
    return false; 
    }
}
