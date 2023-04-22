#pragma once

#include "PayCheck.h"

class Affiliation
{
public:
	virtual ~Affiliation() {};
	Affiliation() {};

	virtual double CalculateDeductions(PayCheck&) const = 0;
};