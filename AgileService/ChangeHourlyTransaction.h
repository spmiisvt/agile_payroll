#pragma once

#include "ChangeClassificationTransaction.h"
#include "WeeklySchedule.h"
#include "HourlyClassification.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
public:
	virtual ~ChangeHourlyTransaction() {};
	ChangeHourlyTransaction(int empid, double hourlyRate);

	virtual PaymentSchedule* GetSchedule() const override;
	virtual PaymentClassification* GetClassification() const override;
private:
	double itsHourlyRate;
};