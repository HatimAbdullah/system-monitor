#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {  
  string name, total, free;
  string line;
  float memoryutilization = 0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream firstlinestream(line);
    firstlinestream >> name >> total;
    std::getline(filestream, line);
    std::istringstream secondlinestream(line);
    secondlinestream >> name >> free;
    memoryutilization = std::stof(total) / std::stof(free);
  }

  return memoryutilization; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptimeinseconds;
  string line;
  long uptime = 0;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptimeinseconds;
    uptime = (std::stol(uptimeinseconds) / 60.0) / 60;
  }

  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string jiffie, name;
  string line;
  long jiffies = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> name;
    while (linestream >> jiffie) { 
    jiffies += std::stol(jiffie);
    }
  }
  return jiffies; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {   
  string value;
  string line;
  long activetime = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +kStatFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    int count = 1;
    while (linestream >> value) {
      if (count == 14 || count == 15 || count == 16 || count == 17) {
        activetime += std::stol(value);
      } 
      count++;
    }
  }
  return activetime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string name, jiffie;
  string line;
  long activejiffies = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> name;
    int count = 0;
    while (linestream >> jiffie) {
      if (count != 3 && count != 4) {
        activejiffies += std::stol(jiffie);
      }
      count++;
    }
  }
  return activejiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string name, jiffie;
  string line;
  long idlejiffies = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> name;
    int count = 0;
    while (linestream >> jiffie) {
      if (count == 3 || count == 4) {
        idlejiffies += std::stol(jiffie);
      }
      count++;
    }
  }
  return idlejiffies; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuutilization;
	return cpuutilization; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key, value;
  string line;
  int processes = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        processes = std::stoi(value);
        return processes;
      }
    }
  }
  return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key, value;
  string line;
  int runningprocesses = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "procs_running") {
        linestream >> value;
        runningprocesses = std::stoi(value);
        return runningprocesses;
      }
    }
  }
  return runningprocesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  string command;
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::Ram(int pid) { 
  float ram = 0;
  string line, key, val;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "VmSize:") {
        linestream >> val;
        ram = std::stof(val);
        return ram * 0.001;
      }
    }
  }
  return ram; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid;
  string line, key, val;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "Uid:") {
        linestream >> val;
        return val;
      }
    }
  }

  return string(); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, filler, uid, user;
  std::ifstream secondfilestream(kPasswordPath);

  if (secondfilestream.is_open()) {
    while (std::getline(secondfilestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream secondlinestream(line);
      secondlinestream >> user >> filler >> uid >> filler;
      if (uid == Uid(pid)) {
        return user;
      }
    }
  }
  return string(); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string value;
  string line;
  long starttime = 0;
  long tkspersec = sysconf(_SC_CLK_TCK);
  long uptime = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +kStatFilename);
  int count = 1;
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      if (count == 22) {
        starttime = std::stol(value);
      }
    count++;
    }
  }
  uptime = UpTime() - ( starttime / tkspersec );
  return uptime; 
}