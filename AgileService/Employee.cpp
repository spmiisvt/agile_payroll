#include "Employee.h"


Employee::~Employee()
{
	delete itsClassification;
	delete itsSchedule;
	delete itsPaymentMethod;
	delete itsAffiliation;
}

Employee::Employee(int empId, string name, string address)
	: itsEmpId(empId)
	, itsName(name)
	, itsAddress(address)
	, itsClassification(nullptr)
	, itsSchedule(nullptr)
	, itsPaymentMethod(nullptr)
	, itsAffiliation(new NoAffiliation())
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
void Employee::SetAffiliation(Affiliation* af)
{
	delete itsAffiliation;
	itsAffiliation = af;
}


bool Employee::IsPayDate(const Date& payDate) const
{
	return itsSchedule->IsPayDate(payDate);
}

Date Employee::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
	return itsSchedule->GetPayPeriodStartDate(payPeriodEndDate);
}

void Employee::Payday(PayCheck& pc) const
{
	const double grossPay = itsClassification->CalculatePay(pc);
	const double deductions = itsAffiliation->CalculateDeductions(pc);
	const double netPay = grossPay - deductions;
	pc.SetGrossPay(grossPay);
	pc.SetDeductions(deductions);
	pc.SetNetPay(netPay);
	itsPaymentMethod->Pay(pc);
}