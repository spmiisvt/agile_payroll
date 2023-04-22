#pragma once
#include "Date.h"

class SalesReceipt
{
public:
	virtual ~SalesReceipt() {};
	SalesReceipt(Date date, double amount);

	Date GetDate() { return itsDate; }
	double GetAmount() { return itsAmount; }

private:
	Date itsDate;
	double itsAmount;
};