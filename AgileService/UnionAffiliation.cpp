#include "UnionAffiliation.h"
#include "ServiceCharge.h"
#include "Date.h"

UnionAffiliation::~UnionAffiliation() {
    for (auto& el : itsServiceCharges)
    {
        delete el.second;
    }
    itsServiceCharges.clear();
}
UnionAffiliation::UnionAffiliation(int memberId, double dues)
    : itsMemberId(memberId)
    , itsDues(dues)
{
}
ServiceCharge* UnionAffiliation::GetServiceCharge(const Date& date)
{
    return itsServiceCharges[date];
}
void UnionAffiliation::AddServiceCharge(const Date& date, double amount)
{
    ServiceCharge* sc = new ServiceCharge(date, amount);
    itsServiceCharges[date] = sc;
}