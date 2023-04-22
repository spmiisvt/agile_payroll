#include "SalesReceiptTransaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"
#include "CommissionedClassification.h"
#include "SalesReceipt.h"

extern PayrollDatabase GpayrollDatabase;

SalesReceiptTransaction::SalesReceiptTransaction(Date date, double amount, int empid)
	: itsDate(date)
	, itsAmount(amount)
	, itsEmpid(empid)
{}

void SalesReceiptTransaction::Execute()
{
	Employee* e = GpayrollDatabase.GetEmployee(itsEmpid);
	if (e) {
		PaymentClassification* pc = e->GetClassification();
		if (CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc))
		{
			cc->AddSalesReceipt(new SalesReceipt(itsDate, itsAmount));
		}
		else {
			throw("Tried to add SalesReceipt to non-commission employee");
		}
	}
	else {
		throw("No such employee.");
	}
}