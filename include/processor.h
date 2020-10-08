#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
    float Utilization();  // TODO: See src/processor.cpp
    
  // TODO: Declare any necessary private members
 private:
    long Total_;
    long NonIdle_;
    long Idle_;
    long PrevTotal_=0;
    long PrevNonIdle_=0;
    long PrevIdle_=0;
    float idled;
    float totald;
    
};

#endif