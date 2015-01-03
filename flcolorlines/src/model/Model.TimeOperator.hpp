#ifndef MODEL_TIMEOPERATOR
#define MODEL_TIMEOPERATOR

//custom includes
//...

//global includes
#include <ctime>
#include <cassert>

namespace model
{

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

}//namespace model

#endif // MODEL_TIMEOPERATOR
