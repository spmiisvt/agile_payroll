#include "CommissionedClassification.h"


CommissionedClassification::~CommissionedClassification()
{
	for (auto& element : itsReceipts)
	{
		delete element.second;
	}
	itsReceipts.clear();
}

CommissionedClassification::CommissionedClassification(double salary, double commissionRate)
	: itsSalary(salary)
	, itsCommissionRate(commissionRate)
{
}
double CommissionedClassification::GetSalary() const {
	return itsSalary;
}

double CommissionedClassification::GetRate() const {
	return itsCommissionRate;
}

void CommissionedClassification::AddSalesReceipt(SalesReceipt* sr)
{
	itsReceipts[sr->GetDate()] = sr;
}

SalesReceipt* CommissionedClassification::GetReceipt(const Date& saleDate)
{
	return itsReceipts[saleDate];
}