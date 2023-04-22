#include "ChangeCommissionedTransaction.h"


ChangeCommissionedTransaction::
ChangeCommissionedTransaction(int empid, double salary, double commissionRate)
	: ChangeClassificationTransaction(empid)
	, itsCommissionRate(commissionRate)
	, itsSalary(salary)
{}

PaymentSchedule* ChangeCommissionedTransaction::GetSchedule() const
{
	return new BiweeklySchedule();
}


PaymentClassification* ChangeCommissionedTransaction::GetClassification() const
{
	return new CommissionedClassification(itsSalary, itsCommissionRate);
}