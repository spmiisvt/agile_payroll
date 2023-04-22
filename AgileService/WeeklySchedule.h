#pragma once

#include "PaymentSchedule.h"
#include "Date.h"

class WeeklySchedule : public PaymentSchedule
{
public:
	virtual ~WeeklySchedule() {};
	WeeklySchedule() {};

	bool IsPayDate(const Date&) const override;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
