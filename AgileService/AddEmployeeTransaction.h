#pragma once

#include "Transaction.h"
#include "HoldMethod.h"
#include "Employee.h"
#include "PayrollDatabase.h"

#include <string>
using namespace std;

class PaymentMethod;
class PaymentSchedule;
class PaymentClassification;

extern PayrollDatabase GpayrollDatabase;

class AddEmployeeTransaction : public Transaction
{
public:
	virtual ~AddEmployeeTransaction() {};
	AddEmployeeTransaction(int empid, string name, string address);
	virtual PaymentClassification* GetClassification() const = 0;
	virtual PaymentSchedule* GetSchedule() const = 0;
	virtual void Execute();
private:
	int itsEmpid;
	string itsName;
	string itsAddress;
};
