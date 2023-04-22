#pragma once

#include "PaymentSchedule.h"
#include "Date.h"

class MonthlySchedule : public PaymentSchedule
{
public:
	virtual ~MonthlySchedule() {};
	MonthlySchedule() {};

	bool IsPayDate(const Date&) const override;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};