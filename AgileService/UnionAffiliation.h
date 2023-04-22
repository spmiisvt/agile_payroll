#pragma once
#include "Affiliation.h"
#include "ServiceCharge.h"
#include "PayCheck.h"
#include "Date.h"
#include <map>


using namespace std;


class UnionAffiliation : public Affiliation
{
public:
	virtual ~UnionAffiliation();
	UnionAffiliation(int memberId, double dues);

	ServiceCharge* GetServiceCharge(const Date& date);
	void AddServiceCharge(const Date& date, double amount);

	double GetDues() const { return itsDues; }
	int GetMemberId() const { return itsMemberId; }

	double CalculateDeductions(PayCheck&) const override;

private:
	int itsMemberId;
	double itsDues;
	map<Date, ServiceCharge*> itsServiceCharges;
};