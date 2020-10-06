#include <string>
#include <stdio.h>
#include <iomanip>   

#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int HH =00;
    int MM = 00;
    int SS = 00;
    std::ostringstream formatted;                            
    HH = seconds / 3600;
	seconds = seconds % 3600;
	MM = seconds / 60;
	SS = seconds % 60;
    formatted << std::setw(2) << std::setfill('0') << HH << ":"  <<std::setw(2) << std::setfill('0')  << MM   << ":" << std::setw(2) << std::setfill('0') << SS;
    to_string(HH) + ":" + to_string(MM) + ":" + to_string(SS);
    return formatted;
}