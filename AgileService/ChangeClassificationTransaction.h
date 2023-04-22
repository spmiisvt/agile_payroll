#pragma once

#include "ChangeEmployeeTransaction.h"

class PaymentClassification;
class PaymentSchedule;


class ChangeClassificationTransaction : public ChangeEmployeeTransaction
{
public:
	virtual ~ChangeClassificationTransaction() {};
	ChangeClassificationTransaction(int empid);

	virtual void Change(Employee&) override;
	virtual PaymentClassification* GetClassification() const = 0;
	virtual PaymentSchedule* GetSchedule() const = 0;
};