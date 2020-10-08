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
void Process::Ram(int ii){
    ram_ = LinuxParser::Ram(ii) ;
}
// Done: Return the user (name) that generated this process
string Process::User() { 
    return  user_; 
}
// Done: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return uptime_;
}
void Process::UpTime(int ii){
    uptime_ = LinuxParser::UpTime(ii);
}
void Process::CpuUtilization(int pid) {
  float a_process = static_cast<float>(LinuxParser::ActiveJiffies(pid));
  float a_processor = static_cast<float>(LinuxParser::ActiveJiffies());
  cpuutilization_ = a_process / a_processor;
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    return  a.cpuutilization_ < this->cpuutilization_;
}