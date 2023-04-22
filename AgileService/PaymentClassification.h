#pragma once
#include "PayCheck.h"

class PaymentClassification
{
public:
	virtual ~PaymentClassification() {};
	PaymentClassification() {};
	virtual double CalculatePay(PayCheck&) const = 0;
};