#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Done: Return this process's ID
int Process::Pid() {
    return pid_;
}
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    return cpuutilization_;
 }

// Done: Return the command that generated this process
string Process::Command() { 
    return command_;
}
// Done: Return this process's memory utilization
string Process::Ram() { 
    return ram_; 
}
// Done: Return the user (name) that generated this process
string Process::User() { 
    return  user_; 
}
// Done: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return uptime_;
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    if(cpuutilization_<a.cpuutilization_) {
        return true;
    } else return false;
}

void Process::Pid(int pid) {
  pid_ = pid;
}

void Process::User(int pid) {
  user_ = LinuxParser::User(pid);
}

void Process::Command(int pid) {
  command_ = LinuxParser::Command(pid);
}

void Process::CpuUtilization(int pid) {
  float a_process = static_cast<float>(LinuxParser::ActiveJiffies(pid));
  float a_processor = static_cast<float>(LinuxParser::ActiveJiffies());
  cpuutilization_ = a_process / a_processor;
}

void Process::Ram(int pid) {
  int kbytes = std::atoi(LinuxParser::Ram(pid).c_str());
  int mbytes = kbytes / 1000; // in MB
  ram_ = std::to_string(mbytes);
}

void Process::UpTime(int pid){
  uptime_ = LinuxParser::UpTime(pid);
}