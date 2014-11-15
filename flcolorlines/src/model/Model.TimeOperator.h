#ifndef MODEL_TIMEOPERATOR
#define MODEL_TIMEOPERATOR

#include <ctime>

namespace model{

class TimeOperator{

public:

    TimeOperator(int precision = 1000000);
    ~TimeOperator();

    long getTimeSinceBegin();
    long getTimeSinceMark();
    long getTimeDifference(timespec timeA, timespec timeB);

    void setMark();


private:
    timespec beginTimestamp;
    timespec markTimestamp;

    int precision;

};
}

#endif // MODEL_TIMEOPERATOR
