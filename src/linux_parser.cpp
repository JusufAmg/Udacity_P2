#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stol;
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
  string os,version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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
// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemTotal,MemFree,MemAvailable,Buffers,Cached;
  string line, buffer;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> buffer >> MemTotal >> buffer;
    std::getline(stream,line);
    linestream >> buffer >> MemFree >> buffer;
    std::getline(stream,line);
    linestream >> buffer >> MemAvailable >> buffer;
    std::getline(stream,line);
    linestream >> buffer >> Buffers >> buffer;
    std::getline(stream,line);
    linestream >> buffer >> Cached;
  }
  float TotalUsedMem = MemTotal - MemFree;
  return (TotalUsedMem - (Buffers+Cached)) ;
}
// Done: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
 }
// Done: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<string> data = CpuUtilization();
  long jiffies;
  jiffies = stol(data[kUser_]) + stol(data[kNice_]) + stol(data[kSystem_]) + stol(data[kIRQ_]) +
            stol(data[kSoftIRQ_]) + stol(data[kSteal_]);
  return jiffies;
}
// Done: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  string data ;
  int jiffies =0;
  string line;
  vector<string> cpu;
  std::ifstream stream(kProcDirectory + to_string(pid) +kStatFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        while(1){
          int ii = 1;
          linestream >> data;
          if (ii == 14) {
            for(int jj =0;jj<4;jj++){
              jiffies += stol(data);
              linestream >> data;
            }
            ii = 18;
            break;
          }
          ii++;
        }
    }
  return jiffies;
}
// Done: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long active = Jiffies() - IdleJiffies();
  return active;
}
// Done: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long idle ;
  vector<string> data = CpuUtilization();
  idle = stol(data[kIdle_]) + stol(data[kIOwait_]);
  return idle;
}
// Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string data;
  string line;
  vector<string> cpu;
  std::ifstream stream(kProcDirectory +kStatFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        for(int ii = -1;ii<11;ii++){
          linestream >> data;
          if (ii == -1) continue;
          else {
            cpu.push_back(data);
          }
        }
    }
  return cpu;
}
// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
    string key;
    int total;
    string line;
    std::ifstream stream(kProcDirectory +kStatFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        while(linestream >> key >> total){
            if (key == "processes") {
                break;
            }
        }
    }
    return total;
}
// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {    
    string key;
    int running;
    string line;
    std::ifstream stream(kProcDirectory +kStatFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        while(linestream >> key >> running){
            if (key == "procs_running") {
                break;
            }
        }
    }
    return running;
}
// Done: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
    string command;
    string line;
    std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream >> command; 
        }
        return command;
    }
// Done: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
    string key,buffer;
    int memory;
    string line;
    std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (stream) {
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while(linestream >> key >> memory >> buffer){
                if (key == "Vmsize") {
                    break;
                }
            }
        }
    }
  return to_string((memory / 1000)); // in MB
}
// Done: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
    string key,uid;
    string line;
    std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (stream) {
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while(linestream >> key >> uid){
                if ( key == "Uid") break;
            }
        }
    }
    return uid;
}
// Done: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string key,user,buffer;
  string line;
  string uid = LinuxParser::Uid( pid);
  std::ifstream stream(kPasswordPath);
  if (stream) {
    while(std::getline(stream, line)){
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while(linestream >> user >> buffer >> key){
            if (key == uid) {
                break;
            }
        }   
    }   
  }
  return user;
}
// Done: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  long up_time;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream) {
    while(std::getline(stream, line)){
        std::istringstream linestream(line);
        for(int ii = 0;ii<=22;ii++){
            linestream >> up_time;   
        }   
    }
  }
  return (up_time/sysconf(_SC_CLK_TCK));
}
