#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    //long idle = LinuxParser::IdleJiffies();
    long active = LinuxParser::ActiveJiffies();
    long total =  LinuxParser::Jiffies();
    float CPU_Percentage = active / total;
    return (CPU_Percentage) ;
}