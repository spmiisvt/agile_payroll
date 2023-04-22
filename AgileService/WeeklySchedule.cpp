#include "WeeklySchedule.h"


bool WeeklySchedule::IsPayDate(const Date& theDate) const
{
    return theDate.GetDayOfWeek() == Date::DayOfWeek::friday;
}

Date WeeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return payPeriodEndDate - 6;
}