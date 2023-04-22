#include "BiweeklySchedule.h"


bool BiweeklySchedule::IsPayDate(const Date& theDate) const
{
    const Date firstPayableFriday(11, 9, 2001);
    const int daysSinceFirstPayableFriday = theDate - firstPayableFriday;
    return (daysSinceFirstPayableFriday % 14) == 0;
}

Date BiweeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return payPeriodEndDate - 13;
}