#include "AddEmployeeTransaction.h"


AddEmployeeTransaction::
AddEmployeeTransaction(int empid, string name, string address)
	: itsEmpid(empid)
	, itsName(name)
	, itsAddress(address)
{
}

void AddEmployeeTransaction::Execute()
{
	PaymentClassification* pc = GetClassification();
	PaymentSchedule* ps = GetSchedule();
	PaymentMethod* pm = new HoldMethod();
	Employee* e = new Employee(itsEmpid, itsName, itsAddress);
	e->SetClassification(pc);
	e->SetSchedule(ps);
	e->SetMethod(pm);
	GpayrollDatabase.AddEmployee(itsEmpid, e);
}