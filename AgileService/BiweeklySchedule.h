#pragma once

#include "PaymentSchedule.h"
#include "Date.h"

class BiweeklySchedule : public PaymentSchedule
{
public:
	virtual ~BiweeklySchedule() {};
	BiweeklySchedule() {};
	bool IsPayDate(const Date&) const override;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};