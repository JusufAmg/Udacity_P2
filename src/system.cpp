    #include <unistd.h>
    #include <cstddef>
    #include <set>
    #include <string>
    #include <vector>

    #include "process.h"
    #include "processor.h"
    #include "linux_parser.h"
    #include "system.h"

    using std::set;
    using std::size_t;
    using std::string;
    using std::vector;

    // Done: Return the system's CPU
    Processor& System::Cpu() { 
        return this->cpu_;
        }
    // Done: Return a container composed of the system's processes
    vector<Process>& System::Processes() {
        processes_.clear();
        vector<int> pid = LinuxParser::Pids();
        for (int ii : pid ) {
            Process x;
            x.pid_ = ii;
            x.command_ = LinuxParser::Command(ii);
            x.Ram(ii); 
            x.CpuUtilization(ii);
            x.user_ =  LinuxParser::User(ii);
            x.UpTime(); 
            processes_.push_back(x);
        }
        sort(processes_.begin(),processes_.end());
        return processes_;
    }
    // Done: Return the system's kernel identifier (string)
    std::string System::Kernel() {    
        return LinuxParser::Kernel(); 
    } 
    // Done: Return the system's memory utilization
    float System::MemoryUtilization() { 
        return LinuxParser::MemoryUtilization(); 
    }
    // Done: Return the operating system name
    std::string System::OperatingSystem() { 
        return LinuxParser::OperatingSystem(); 
    }
    // Done: Return the number of processes actively running on the system
    int System::RunningProcesses() { 
        return LinuxParser::RunningProcesses();
    }
    // Done: Return the total number of processes on the system
    int System::TotalProcesses() { 
        return LinuxParser::TotalProcesses();
    }
    // Done: Return the number of seconds since the system started running
    long int System::UpTime() { 
        return LinuxParser::UpTime(); 
    }