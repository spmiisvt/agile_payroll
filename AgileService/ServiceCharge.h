#pragma once
#include "Date.h"

class ServiceCharge
{
public:
	virtual ~ServiceCharge() {};
	ServiceCharge(Date date, double amount);

	Date GetDate() { return itsDate; }
	double GetAmount() { return itsAmount; }

private:
	Date itsDate;
	double itsAmount;
};