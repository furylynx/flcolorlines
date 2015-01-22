#include "Model.TimeOperator.hpp"

using namespace model;

TimeOperator::TimeOperator()
{
    clock_gettime(1, &beginTimestamp);
    clock_gettime(1, &markTimestamp);
}

TimeOperator::~TimeOperator()
{
}

long TimeOperator::getTimeSinceBegin() const
{
//    timeval timeB;
//    clock_gettime(1, &timeB);

//    return getTimeDifference(beginTimestamp, timeB);
    return getTimeSince(beginTimestamp);
}


long TimeOperator::getTimeSinceMark() const
{
//    timeval timeB;
//    clock_gettime(1, &timeB);

//    return getTimeDifference(markTimestamp, timeB);
    return getTimeSince(markTimestamp);
}

long TimeOperator::getTimeSince(timeval timestamp) const
{
    timeval now;
    clock_gettime(1, &now);

    return getTimeDifference(timestamp, now);
}

long TimeOperator::getTimeDifference(timeval timeA, timeval timeB) const
{      
    //get difference in ms
    return ((timeB.tv_sec - timeA.tv_sec) * 1000) + ((timeB.tv_usec - timeA.tv_usec) / 1000);
}

void TimeOperator::setMark()
{
    clock_gettime(1, &markTimestamp);
}

