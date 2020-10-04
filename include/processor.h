#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
    float Utilization();  // TODO: See src/processor.cpp
    void Jiffies(long jiffies) {
        jiffies_ = jiffies;
    };
    long Jiffies() {
        return jiffies_;
    };
    void PrevActive(long active) {
        active_ = active;
    }
    long PrevActive() {
        return active_;
    }
    void PrevIdle (long idle) {
        idle_ = idle;
    }
    long PrevIdle () {
        return idle_;
    }

  // TODO: Declare any necessary private members
 private:
    long jiffies_;
    long active_;
    long idle_;
};

#endif