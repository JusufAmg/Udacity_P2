#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  void CpuUtilization(int);
  std::string Ram();                       // TODO: See src/process.cpp
  void Ram(int);
  long int UpTime();                       // TODO: See src/process.cpp
  void UpTime(int);
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  // TODO: Declare any necessary private members
 private:
    int pid_;
    float cpuutilization_;
    std::string command_;
    std::string user_;
    long int uptime_;
    std::string ram_;
    friend class System;
};

#endif