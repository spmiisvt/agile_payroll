#pragma once

#include "AddEmployeeTransaction.h"

#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

#include <string>
using namespace std;


class AddCommissionedEmployee : public AddEmployeeTransaction
{
public:
	virtual ~AddCommissionedEmployee() {};
	AddCommissionedEmployee(int empid, string name, string address, double salary, double commissionRate);
	PaymentClassification* GetClassification() const;
	PaymentSchedule* GetSchedule() const;

private:
	double itsSalary;
	double itsCommissionRate;
};