#include <iostream>
#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

int main() {
  //System system;
  //NCursesDisplay::Display(system);
  //std::cout << LinuxParser::OperatingSystem() << "\n";
  LinuxParser::User(17743);
}