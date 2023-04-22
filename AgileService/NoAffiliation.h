#pragma once
#include "Affiliation.h"
#include "PayCheck.h"

class NoAffiliation : public Affiliation
{
public:
	virtual ~NoAffiliation() {};
	NoAffiliation() {};
	double CalculateDeductions(PayCheck&) const override;
};