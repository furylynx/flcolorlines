#ifndef MODEL_TIMEOPERATOR
#define MODEL_TIMEOPERATOR

//custom includes
//...

//global includes
#include <ctime>
#include <cassert>

namespace model
{

class TimeOperator
{

public:

    /**
     * Creates a new time operator.
     *
     * @param precision The precision of the time operator.
     */
    TimeOperator(int precision = 1000000);
    virtual ~TimeOperator();

    /**
     * Returns the time passed since the begin marker.
     *
     * @return The time passed.
     */
    virtual long getTimeSinceBegin();

    /**
     * Returns the time passed since the set marker.
     *
     * @return The time passed.
     */
    virtual long getTimeSinceMark();

    /**
     * Returns the time difference between the two timestamps.
     *
     * @param timeA The first timestamp.
     * @param timeB The second timestamp.
     * @return The passed time.
     */
    virtual long getTimeDifference(timespec timeA, timespec timeB);

    /**
     * Sets the time marker at the current time.
     */
    virtual void setMark();


private:
    /**
     * The begin time marker.
     */
    timespec beginTimestamp;

    /**
     * The set time marker.
     */
    timespec markTimestamp;

    /**
     * The precision to be applied.
     */
    int precision;

};

}//namespace model

#endif // MODEL_TIMEOPERATOR
