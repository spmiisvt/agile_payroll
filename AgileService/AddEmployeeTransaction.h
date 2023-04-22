#pragma once

#include "Transaction.h"
#include <string>

using namespace std;

class PaymentClassification;
class PaymentSchedule;

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
