#pragma once

#include "PaymentClassification.h"
#include "PayCheck.h"

class SalariedClassification : public PaymentClassification {
public:
	virtual ~SalariedClassification() {};
	SalariedClassification(double salary);

	double GetSalary() const;
	double CalculatePay(PayCheck&) const;

private:
	double itsSalary;
};