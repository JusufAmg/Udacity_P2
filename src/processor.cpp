#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    long jiffies = LinuxParser::Jiffies();
    long active = LinuxParser::ActiveJiffies();
    float CPU_Percentage = active / jiffies;
    return (CPU_Percentage) ;
}