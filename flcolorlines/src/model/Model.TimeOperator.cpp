#include "Model.TimeOperator.hpp"

using namespace model;

TimeOperator::TimeOperator()
{
    beginTimestamp = getCurrentTime();
    markTimestamp = getCurrentTime();
}

TimeOperator::~TimeOperator()
{
}

long TimeOperator::getTimeSinceBegin() const
{
    return getTimeSince(beginTimestamp);
}


long TimeOperator::getTimeSinceMark() const
{
    return getTimeSince(markTimestamp);
}

long TimeOperator::getTimeSince(timeval timestamp) const
{
    return getTimeDifference(timestamp, getCurrentTime());
}

long TimeOperator::getTimeDifference(timeval timeA, timeval timeB) const
{      
    //get difference in ms
    return ((timeB.tv_sec - timeA.tv_sec) * 1000) + ((timeB.tv_usec - timeA.tv_usec) / 1000);
}

void TimeOperator::setMark()
{
    markTimestamp = getCurrentTime();
}

timeval TimeOperator::getCurrentTime() const
{
    timeval now;

    auto chronoNow = std::chrono::system_clock::now().time_since_epoch();
    now.tv_sec = std::chrono::duration_cast<std::chrono::seconds>(chronoNow).count();
    now.tv_usec = std::chrono::duration_cast<std::chrono::microseconds>(chronoNow).count() - now.tv_sec * 1000000;

    return now;
}

