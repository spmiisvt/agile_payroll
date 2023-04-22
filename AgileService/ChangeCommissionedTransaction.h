#pragma once

#include "ChangeClassificationTransaction.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

class ChangeCommissionedTransaction : public ChangeClassificationTransaction
{
public:
	virtual ~ChangeCommissionedTransaction() {};
	ChangeCommissionedTransaction(int empid, double salary, double commissionRate);

	virtual PaymentSchedule* GetSchedule() const override;
	virtual PaymentClassification* GetClassification() const override;
private:
	double itsSalary;
	double itsCommissionRate;
};