#pragma once

#include "PayCheck.h"

class PaymentMethod
{
public:
	virtual ~PaymentMethod() {};
	PaymentMethod() {};

	virtual void Pay(PayCheck&) = 0;
};