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

// TODO: Return this process's ID
int Process::Pid() {
    return this->pid_;
}
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    return cpuutilization_;
 }
 void Process::CpuUtilization(int pid) {
    float pid_jiffies = LinuxParser::ActiveJiffies(pid);
    float system_jiffies = LinuxParser::ActiveJiffies();
    cpuutilization_ = (pid_jiffies / system_jiffies);
 }
// DOne: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this-> pid_);
}
// DOne: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(this-> pid_); 
}
// DOne: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(this-> pid_); 
}
// DOne: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(this -> pid_);
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    Process::CpuUtilization() < a.
    return true; 
}