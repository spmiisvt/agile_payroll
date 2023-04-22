#pragma once
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"
#include "Affiliation.h"
#include "Date.h"
#include "PaymentMethod.h"
#include "PayCheck.h"
#include "NoAffiliation.h"

#include <string>

using namespace std;


class Employee
{
public:
	virtual ~Employee();
	Employee(int empId, string name, string address);

	void SetName(string name);
	void SetAddress(string address);
	void SetClassification(PaymentClassification*);
	void SetSchedule(PaymentSchedule*);
	void SetMethod(PaymentMethod*);
	void SetAffiliation(Affiliation*);


	int GetEmpId() const { return itsEmpId; }
	string GetName() const { return itsName; }
	string GetAddress() const { return itsAddress; }

	PaymentClassification* GetClassification() const { return itsClassification; }
	PaymentSchedule* GetSchedule() const { return itsSchedule; }
	PaymentMethod* GetMethod() const { return itsPaymentMethod; }
	Affiliation* GetAffiliation() const { return itsAffiliation; }
	
	void Payday(PayCheck&) const;
	bool IsPayDate(const Date& payDate) const;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const;

private:
	int itsEmpId;
	string itsName;
	string itsAddress;
	PaymentClassification* itsClassification;
	PaymentSchedule* itsSchedule;
	PaymentMethod* itsPaymentMethod;
	Affiliation* itsAffiliation;
};