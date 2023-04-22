#pragma once

#include "Transaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

class ChangeEmployeeTransaction : public Transaction
{
public:
	virtual ~ChangeEmployeeTransaction() {};
	ChangeEmployeeTransaction(int empid);
	
	virtual void Execute();
	virtual void Change(Employee&) = 0;

protected:
	int GetEmpId() const { return itsEmpId; }

private:
	int itsEmpId;
};