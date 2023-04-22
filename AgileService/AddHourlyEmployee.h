#pragma once

#include "AddEmployeeTransaction.h"
#include "WeeklySchedule.h"
#include "HourlyClassification.h"

#include <string>

using namespace std;

class AddHourlyEmployee : public AddEmployeeTransaction
{
public:
	virtual ~AddHourlyEmployee() {};
	AddHourlyEmployee(int empid, string name, string address, double hourlyRate);
	PaymentClassification* GetClassification() const;
	PaymentSchedule* GetSchedule() const;

private:
	double itsHourlyRate;
};