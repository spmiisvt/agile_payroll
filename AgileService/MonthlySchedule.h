#pragma once

#include "PaymentSchedule.h"

class MonthlySchedule : public PaymentSchedule
{
public:
	virtual ~MonthlySchedule() {};
	MonthlySchedule() {};
};