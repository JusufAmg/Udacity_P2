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
  float data,MemTotal,MemFree,Buffers;
  string line, key;
    std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream){
    while(std::getline(stream,line)) {
      std::istringstream linestream(line);
      linestream >> key >> data;
      if (key == "MemTotal:") MemTotal= data;
      else if (key == "MemFree:") MemFree = data;
      else if (key == "Buffers:") {
        Buffers = data;
        break;
      }
    }
  }
  float TotalUsedMem = MemTotal - MemFree;
  float UsedMem = TotalUsedMem - Buffers; 
  return (UsedMem/MemTotal) ;
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
  long jiffies;
  jiffies = ActiveJiffies() + IdleJiffies();
  return jiffies;
}

// Done: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  vector<std::string> data;
  string line;
  long jiffies = 0;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +kStatFilename);
  if (filestream) {
    std::getline(filestream, line);
    std::stringstream sstream(line);
    while (std::getline(sstream, line, ' ')) {
      buffer.push_back(line);
    }
    for (int ii =13;ii <17;ii++){
      jiffies+= std::stol(data[ii])  
    }
  }
  return jiffies;
}
// Done: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  vector<string> data = CpuUtilization();
  long active = stol(data[kUser_]) + stol(data[kNice_]) + stol(data[kSystem_]) + stol(data[kIRQ_]) +
            stol(data[kSoftIRQ_]) + stol(data[kSteal_]);
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
  vector<string> cpu = {};  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream) {
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> data;
    for(int ii = 0;ii<10;ii++){
        linestream >> data;
        cpu.push_back(data);
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
        while(std::getline(stream,line)){
          std::istringstream linestream(line);
          linestream >> key >> total;
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
        while(std::getline(stream,line)){
          std::istringstream linestream(line);
          linestream >> key >> running;
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
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
    if (stream) {
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream >> command; 
        }
        return command;
    }
// Done: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
    string key;
    int temp_memory,memory;
    string line;
    std::ifstream stream(kProcDirectory  + "/" + to_string(pid) + kStatusFilename);
    if (stream) {
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while(linestream >> key >> temp_memory){
                if (key == "VmSize:") {
                    memory = temp_memory;
                    break;
                } 
            }
        }
    }
  return to_string((memory / 1000)); // in MB
}
// Done: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
    string key,temp_uid,uid;
    string line;
    std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
    if (stream) {
        while(std::getline(stream,line)){
            std::istringstream linestream(line);
            while(linestream >> key >> temp_uid){
                if ( key == "Uid:") {
                  uid = temp_uid;
                  break;
                }
            }
        }
    }
    return uid;
}
// Done: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string key,temp_user,buffer,user;
  string line;
  string uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream) {
    while(std::getline(stream, line)){
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        linestream >> temp_user >> buffer >> key;
        if (uid == key) {
          user = temp_user;
          break;
        }
    }  
  }
  return user;
}
// Done: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  long up_time;
  string temp;
  vector<string> data;
  string line;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  if (stream) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> temp){
    data.push_back(temp);
    }
  }
  return up_time = stol(data[21])/sysconf(_SC_CLK_TCK);
}
