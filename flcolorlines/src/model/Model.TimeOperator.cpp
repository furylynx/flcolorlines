#include "Model.TimeOperator.hpp"

using namespace model;

TimeOperator::TimeOperator(int precision)
{
    assert(precision > 0);

    this->precision = precision;

    clock_gettime(1, &beginTimestamp);
    clock_gettime(1, &markTimestamp);
}

TimeOperator::~TimeOperator()
{
}

long TimeOperator::getTimeSinceBegin()
{
    timespec timeB;
    clock_gettime(1, &timeB);

    return getTimeDifference(beginTimestamp, timeB);
}


long TimeOperator::getTimeSinceMark()
{

    timespec timeB;
    clock_gettime(1, &timeB);

    return getTimeDifference(markTimestamp, timeB);
}

long TimeOperator::getTimeDifference(timespec timeA, timespec timeB)
{
    return ((timeB.tv_sec - timeA.tv_sec) * 1000) + ((timeB.tv_nsec - timeA.tv_nsec) / precision);
}

void TimeOperator::setMark()
{
    clock_gettime(1, &markTimestamp);
}

