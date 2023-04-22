#pragma once
#include <string>

using namespace std;

class PaymentClassification;
class PaymentSchedule;
class PaymentMethod;
class Affiliation;
class Date;

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
	

private:
	int itsEmpId;
	string itsName;
	string itsAddress;
	PaymentClassification* itsClassification;
	PaymentSchedule* itsSchedule;
	PaymentMethod* itsPaymentMethod;
	Affiliation* itsAffiliation;
};