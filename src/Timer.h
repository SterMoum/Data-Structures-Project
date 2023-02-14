#ifndef TIMER_H
#define TIMER_H
#include <chrono> //chrono library is used to count the running time of searching and adding algorithms of our DS(Data Structures)
#include <iostream>
class Timer
{
public:

    Timer(); //constructor

    ~Timer(); //destructor
private:
    std::chrono::high_resolution_clock::time_point start,end;

    std::chrono::duration<float> duration;

};

#endif // TIMER_H
