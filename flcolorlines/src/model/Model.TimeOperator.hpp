#ifndef MODEL_TIMEOPERATOR
#define MODEL_TIMEOPERATOR

//custom includes
//...

//global includes
#include <ctime>
#include <cassert>
#include <chrono>

namespace model
{

class TimeOperator
{

public:

    /**
     * Creates a new time operator.
     */
    TimeOperator();
    virtual ~TimeOperator();

    /**
     * Returns the time passed since the begin marker in milliseconds.
     *
     * @return The time passed.
     */
    virtual long getTimeSinceBegin() const;

    /**
     * Returns the time passed since the set marker in milliseconds.
     *
     * @return The time passed.
     */
    virtual long getTimeSinceMark() const;

    /**
     * Returns the time passed since the timestamp in milliseconds.
     *
     * @param timestamp The timestamp.
     * @return The time passed.
     */
    virtual long getTimeSince(timeval timestamp) const;

    /**
     * Returns the time difference between the two timestamps in milliseconds.
     *
     * @param timeA The first timestamp.
     * @param timeB The second timestamp.
     * @return The passed time.
     */
    virtual long getTimeDifference(timeval timeA, timeval timeB) const;

    /**
     * Sets the time marker at the current time.
     */
    virtual void setMark();

    /**
     * Returns the current timestamp as a timeval struct (microsecond precision).
     *
     * @return The timeval.
     */
    virtual timeval getCurrentTime() const;


private:
    /**
     * The begin time marker.
     */
    timeval beginTimestamp;

    /**
     * The set time marker.
     */
    timeval markTimestamp;

};

}//namespace model

#endif // MODEL_TIMEOPERATOR
