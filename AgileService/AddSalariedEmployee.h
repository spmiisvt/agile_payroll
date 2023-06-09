#pragma once
#include "AddEmployeeTransaction.h"
#include "SalariedClassification.h"
#include "MonthlySchedule.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
public:
	virtual ~AddSalariedEmployee() {};
	AddSalariedEmployee(int empid, string name,
		string address, double salary);

	PaymentClassification* GetClassification() const;
	PaymentSchedule* GetSchedule() const;
private:
	double itsSalary;
};