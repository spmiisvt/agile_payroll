#include "gtest/gtest.h"

#include "AddSalariedEmployee.h"
#include "PayrollDatabase.h"
#include "Employee.h"
#include "SalariedClassification.h"
#include "HoldMethod.h"
#include "MonthlySchedule.h"
#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "TimeCard.h"
#include "SalesReceipt.h"
#include "SalesReceiptTransaction.h"
#include "UnionAffiliation.h"
#include "Affiliation.h"
#include "ServiceCharge.h"
#include "ServiceChargeTransaction.h"
#include "ChangeEmployeeTransaction.h"
#include "ChangeNameTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeClassificationTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeAffiliationTransaction.h"
#include "ChangeMemberTransaction.h"

extern PayrollDatabase GpayrollDatabase;

TEST(PayrollTest, TestAddSalariedEmployee)
{
	GpayrollDatabase.clear();
	const int empId = 1;
	AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Bob" == e->GetName());
	PaymentClassification* pc = e->GetClassification();
	SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
	ASSERT_TRUE(sc);

	ASSERT_DOUBLE_EQ(1000.00, sc->GetSalary(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
	ASSERT_TRUE(ms);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
TEST(PayrollTest, TestAddHourlyEmployee)
{
	GpayrollDatabase.clear();
	int empId = 2;
	AddHourlyEmployee t(empId, "Sam", "Home", 15.25);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Sam" == e->GetName());

	PaymentClassification* pc = e->GetClassification();
	HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
	ASSERT_TRUE(hc);
	ASSERT_DOUBLE_EQ(15.25, hc->GetRate(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
	ASSERT_TRUE(ws);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
TEST(PayrollTest, TestAddCommissionedEmployee)
{
	GpayrollDatabase.clear();
	int empId = 3;
	AddCommissionedEmployee t(empId, "Miller", "Home", 2400, 1.7);
	t.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE("Miller" == e->GetName());

	PaymentClassification* pc = e->GetClassification();
	CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
	ASSERT_TRUE(cc);
	ASSERT_DOUBLE_EQ(2400, cc->GetSalary(), 0.01);
	ASSERT_DOUBLE_EQ(1.7, cc->GetRate(), 0.01);

	PaymentSchedule* ps = e->GetSchedule();
	BiweeklySchedule* bws = dynamic_cast<BiweeklySchedule*>(ps);
	ASSERT_TRUE(bws);

	PaymentMethod* pm = e->GetMethod();
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}
TEST(PayrollTest, TestDeleteEmployee)
{
	GpayrollDatabase.clear();
	int empId = 4;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
	t.Execute();
	{
		Employee* e = GpayrollDatabase.GetEmployee(empId);
		ASSERT_TRUE(e);
	}
	DeleteEmployeeTransaction dt(empId);
	dt.Execute();
	{
		Employee* e = GpayrollDatabase.GetEmployee(empId);
		ASSERT_TRUE(e == 0);
	}
}
TEST(PayrollTest, TestTimeCardTransaction)
{
	GpayrollDatabase.clear();
	int empId = 5;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();

	TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
	tct.Execute();

	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);

	PaymentClassification* pc = e->GetClassification();
	HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
	ASSERT_TRUE(hc);
	TimeCard* tc = hc->GetTimeCard(Date(10, 31, 2001));
	ASSERT_TRUE(tc);
	ASSERT_EQ(8.0, tc->GetHours());
}
TEST(PayrollTest, TestSalesReceiptTransaction)
{
	GpayrollDatabase.clear();
	int empId = 6;
	AddCommissionedEmployee t(empId, "Miller", "Home", 2400, 1.7);
	t.Execute();
	const Date saleDate(11, 12, 2001);
	SalesReceiptTransaction srt(saleDate, 20000, empId);
	srt.Execute();

	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);

	PaymentClassification* pc = e->GetClassification();
	CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
	ASSERT_TRUE(cc);
	SalesReceipt* sr = cc->GetReceipt(saleDate);
	ASSERT_TRUE(sr);
	ASSERT_DOUBLE_EQ(20000, sr->GetAmount(), 0.01);
}
TEST(PayrollTest, TestAddServiceCharge)
{
	GpayrollDatabase.clear();
	int empId = 7;
	const int memberId = 86;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();

	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);

	UnionAffiliation* af = new UnionAffiliation(memberId, 12.5);
	e->SetAffiliation(af);

	const Date serviceChargeDate(11, 01, 2001);

	GpayrollDatabase.AddUnionMember(memberId, e);
	ServiceChargeTransaction sct(memberId, serviceChargeDate, 12.95);
	sct.Execute();

	ServiceCharge* sc = af->GetServiceCharge(serviceChargeDate);
	ASSERT_TRUE(sc);
	ASSERT_EQ(12.95, sc->GetAmount(), 0.01);
}
TEST(PayrollTest, TestChangeNameTransaction)
{
	GpayrollDatabase.clear();
	int empId = 8;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	ChangeNameTransaction cnt(empId, "Bob");
	cnt.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	ASSERT_TRUE("Bob" == e->GetName());
}
TEST(PayrollTest, TestChangeAddressTransaction)
{
	GpayrollDatabase.clear();
	int empId = 9;
	AddHourlyEmployee t(empId, "Thomas", "Home", 15.25);
	t.Execute();
	ChangeAddressTransaction cnt(empId, "21 street 165");
	cnt.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	ASSERT_TRUE("21 street 165" == e->GetAddress());
}
TEST(PayrollTest, TestChangeHourlyTransaction)
{
	GpayrollDatabase.clear();
	int empId = 10;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
	t.Execute();
	ChangeHourlyTransaction cht(empId, 27.52);
	cht.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentClassification* pc = e->GetClassification();
	ASSERT_TRUE(pc);
	HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
	ASSERT_TRUE(hc);
	ASSERT_DOUBLE_EQ(27.52, hc->GetRate(), 0.01);
	PaymentSchedule* ps = e->GetSchedule();
	WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
	ASSERT_TRUE(ws);
}
TEST(PayrollTest, TestChangeSalariedTransaction)
{
	GpayrollDatabase.clear();
	const int empId = 11;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
	t.Execute();
	ChangeSalariedTransaction cht(empId, 25000);
	cht.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentClassification* pc = e->GetClassification();
	ASSERT_TRUE(pc);
	const auto sc = dynamic_cast<SalariedClassification*>(pc);
	ASSERT_TRUE(sc);
	ASSERT_DOUBLE_EQ(25000, sc->GetSalary(), 0.01);
	PaymentSchedule* ps = e->GetSchedule();
	const auto ms = dynamic_cast<MonthlySchedule*>(ps);
	ASSERT_TRUE(ms);
}
TEST(PayrollTest, TestChangeCommissionedTransaction)
{
	GpayrollDatabase.clear();
	const int empId = 12;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	ChangeCommissionedTransaction cht(empId, 25000, 4.5);
	cht.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentClassification* pc = e->GetClassification();
	ASSERT_TRUE(pc);
	const auto cc = dynamic_cast<CommissionedClassification*>(pc);
	ASSERT_TRUE(cc);
	ASSERT_DOUBLE_EQ(25000, cc->GetSalary(), 0.01);
	ASSERT_DOUBLE_EQ(4.5, cc->GetRate(), 0.01);
	PaymentSchedule* ps = e->GetSchedule();
	const auto bws = dynamic_cast<BiweeklySchedule*>(ps);
	ASSERT_TRUE(bws);
}
TEST(PayrollTest, TestChangeMemberTransaction)
{
	GpayrollDatabase.clear();
	const int empId = 13;
	int memberId = 352;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	ChangeMemberTransaction cmt(empId, memberId, 99.42);
	cmt.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	Affiliation* af = e->GetAffiliation();
	ASSERT_TRUE(af);
	UnionAffiliation* uf = dynamic_cast<UnionAffiliation*>(af);
	ASSERT_TRUE(uf);
	ASSERT_DOUBLE_EQ(99.42, uf->GetDues(), .001);
	Employee* member = GpayrollDatabase.GetUnionMember(memberId);
	ASSERT_TRUE(member);
	ASSERT_TRUE(e == member);
}