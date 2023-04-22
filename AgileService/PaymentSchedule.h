#pragma once
#include "Date.h"


class PaymentSchedule
{
public:
	virtual ~PaymentSchedule() {};
	PaymentSchedule() {};

	virtual bool IsPayDate(const Date&) const = 0;
	virtual Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const = 0;
};
