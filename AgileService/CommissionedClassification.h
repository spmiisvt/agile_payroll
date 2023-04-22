#pragma once

#include "PaymentClassification.h"
#include "SalesReceipt.h"
#include "PayCheck.h"
#include "Date.h"

#include <map>
#include <string>

using namespace std;

class CommissionedClassification : public PaymentClassification
{
public:
	virtual ~CommissionedClassification();
	CommissionedClassification(double salary, double commissionRate);

	double GetSalary() const;
	double GetRate() const;

	SalesReceipt* GetReceipt(const Date& saleDate);
	void AddSalesReceipt(SalesReceipt*);

	double CalculatePay(PayCheck&) const override;

private:
	double itsSalary;
	double itsCommissionRate;
	map<Date, SalesReceipt*> itsReceipts;
};