#pragma once

#include "ChangeClassificationTransaction.h"
#include "MonthlySchedule.h"
#include "SalariedClassification.h"

class ChangeSalariedTransaction : public ChangeClassificationTransaction
{
public:
	virtual ~ChangeSalariedTransaction() {};
	ChangeSalariedTransaction(int empid, double salary);
	virtual PaymentSchedule* GetSchedule() const override;
	virtual PaymentClassification* GetClassification() const override;
private:
	double itsSalary;
};