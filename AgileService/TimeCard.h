#pragma once
#include "Date.h"

class TimeCard
{
public:
	virtual ~TimeCard() {};
	TimeCard(Date date, double hours);

	Date GetDate() { return itsDate; }
	long GetHours() { return itsHours; }

private:
	Date itsDate;
	double itsHours;
};