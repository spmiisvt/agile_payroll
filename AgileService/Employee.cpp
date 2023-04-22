#include "Employee.h"
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"


Employee::~Employee()
{
	delete itsClassification;
	delete itsSchedule;
	delete itsPaymentMethod;
}

Employee::Employee(int empId, string name, string address)
	: itsEmpId(empId)
	, itsName(name)
	, itsAddress(address)
	, itsClassification(nullptr)
	, itsSchedule(nullptr)
	, itsPaymentMethod(nullptr)
{}
void Employee::SetName(string name)
{
	itsName = name;
}

void Employee::SetAddress(string address)
{
	itsAddress = address;
}

void Employee::SetClassification(PaymentClassification* pc)
{
	delete itsClassification;
	itsClassification = pc;
}

void Employee::SetSchedule(PaymentSchedule* ps)
{
	delete itsSchedule;
	itsSchedule = ps;
}

void Employee::SetMethod(PaymentMethod* pm)
{
	delete itsPaymentMethod;
	itsPaymentMethod = pm;
}