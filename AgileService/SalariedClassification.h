#pragma once

#include "PaymentClassification.h"

class SalariedClassification : public PaymentClassification {
public:
	virtual ~SalariedClassification() {};
	SalariedClassification(double salary);

	double GetSalary() const;

private:
	double itsSalary;
};