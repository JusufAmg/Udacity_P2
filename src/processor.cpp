#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    Idle_= LinuxParser::IdleJiffies();
    NonIdle_= LinuxParser::ActiveJiffies();
    Total_=Idle_ + NonIdle_;
    totald = Total_ - PrevIdle_;
    idled = Idle_ - PrevIdle_;
    return ((totald - idled)/totald ) ;
    PrevIdle_ = Idle_;
    PrevNonIdle_ = NonIdle_;
    PrevTotal_ = Total_;
}