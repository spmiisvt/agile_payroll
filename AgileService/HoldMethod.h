#pragma once
#include "PaymentMethod.h"
#include "PayCheck.h"

class HoldMethod : public PaymentMethod
{
public:
	virtual ~HoldMethod() {};
	HoldMethod() {};
	void Pay(PayCheck&) override;
};