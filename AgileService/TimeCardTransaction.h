#pragma once
#include "Transaction.h"
#include "Date.h"
#include "Employee.h"
#include "PayrollDatabase.h"
#include "HourlyClassification.h"
#include "TimeCard.h"

extern PayrollDatabase GpayrollDatabase;

class TimeCardTransaction : public Transaction
{
public:
	virtual ~TimeCardTransaction() {};
	TimeCardTransaction(Date date, double hours, int empid);

	virtual void Execute();
public:
	int itsEmpid;
	Date itsDate;
	double itsHours;
};