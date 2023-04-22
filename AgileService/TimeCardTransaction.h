#pragma once
#include "Transaction.h"
#include "Date.h"


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