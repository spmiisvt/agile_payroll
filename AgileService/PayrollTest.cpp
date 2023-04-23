#include "gtest/gtest.h"

#include "AddSalariedEmployee.h"
#include "PayrollDatabase.h"
#include "Employee.h"
#include "SalariedClassification.h"
#include "AddEmployeeTransaction.h"
#include "PaymentSchedule.h"
#include "MonthlySchedule.h"
#include "PaymentMethod.h"
#include "HoldMethod.h"
#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "TimeCard.h"
#include "SalesReceiptTransaction.h"
#include "SalesReceipt.h"
#include "UnionAffiliation.h"
#include "ServiceChargeTransaction.h"
#include "ServiceCharge.h"
#include "ChangeEmployeeTransaction.h"
#include "ChangeNameTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeClassificationTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeMemberTransaction.h"
#include "PaydayTransaction.h"
#include "PaymentClassification.h"
#include "PayCheck.h"
#include "Date.h"
#include "ChangeMethodTransaction.h"
#include "MailMethod.h"
#include "DirectMethod.h"
#include "ChangeDirectTransaction.h"
#include "ChangeHoldTransaction.h"
#include "ChangeMailTransaction.h"
#include "ChangeUnaffiliatedTransaction.h"


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
TEST(PayrollTest, TestPaySingleSalariedEmployeeOnWrongDate)
{
	GpayrollDatabase.clear();
	const int empId = 15;
	AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
	t.Execute();
	Date payDate(11, 29, 2001);
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc == 0);
}
TEST(PayrollTest, TestPayMultipleSalariedEmployees)
{
	GpayrollDatabase.clear();
	AddSalariedEmployee t1(1, "Bob", "Home", 1000.00);
	AddSalariedEmployee t2(2, "Bill", "Home", 2000.00);
	AddSalariedEmployee t3(3, "Barry", "Home", 3000.00);
	t1.Execute();
	t2.Execute();
	t3.Execute();
	Date payDate(11, 30, 2001);
	PaydayTransaction pt(payDate);
	pt.Execute();
	ASSERT_TRUE(3L == pt.GetPaycheckCount());

	PayCheck* pc = pt.GetPaycheck(1);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(1000.00, pc->GetGrossPay(), .01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .01);
	ASSERT_DOUBLE_EQ(1000.00, pc->GetNetPay(), .01);

	PayCheck* pc2 = pt.GetPaycheck(2);
	ASSERT_TRUE(pc2);
	ASSERT_TRUE(pc2->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(2000.00, pc2->GetGrossPay(), .01);
	ASSERT_TRUE("Hold" == pc2->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc2->GetDeductions(), .01);
	ASSERT_DOUBLE_EQ(2000.00, pc2->GetNetPay(), .01);

	PayCheck* pc3 = pt.GetPaycheck(3);
	ASSERT_TRUE(pc3);
	ASSERT_TRUE(pc3->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(3000.00, pc3->GetGrossPay(), .01);
	ASSERT_TRUE("Hold" == pc3->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc3->GetDeductions(), .01);
	ASSERT_DOUBLE_EQ(3000.00, pc3->GetNetPay(), .01);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeNoTimeCards)
{
	GpayrollDatabase.clear();
	const int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	const Date payDate(11, 9, 2001);
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(2);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(0.0, pc->GetGrossPay(), .01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .01);
	ASSERT_DOUBLE_EQ(0.0, pc->GetNetPay(), .01);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeOneTimeCard)
{
	GpayrollDatabase.clear();
	const int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	const Date payDate(11, 9, 2001);

	TimeCardTransaction tc(payDate, 2.0, empId);
	tc.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(30.5, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(30.5, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeOvertimeOneTimeCard)
{
	GpayrollDatabase.clear();
	const int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	const Date payDate(11, 9, 2001);

	TimeCardTransaction tc(payDate, 9.0, empId);
	tc.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	const double countPay = (8 + 1.5) * 15.25;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeOnWrongDate)
{
	GpayrollDatabase.clear();
	const int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	const Date payDate(11, 8, 2001);

	TimeCardTransaction tc(payDate, 9.0, empId);
	tc.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc == 0);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCards)
{
	GpayrollDatabase.clear();
	const int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	const Date payDate(11, 9, 2001); // Friday

	TimeCardTransaction tc(payDate, 2.0, empId);
	tc.Execute();
	TimeCardTransaction tc2(Date(11, 8, 2001), 5.0, empId);
	tc2.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	const double countPay = 7 * 15.25;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods)
{
	GpayrollDatabase.clear();
	int empId = 2;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
	t.Execute();
	Date payDate(11, 9, 2001);
	Date dateInPreviousPayPeriod(11, 2, 2001);

	TimeCardTransaction tc(payDate, 2.0, empId);
	tc.Execute();
	TimeCardTransaction tc2(dateInPreviousPayPeriod, 5.0, empId);
	tc2.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	const double countPay = 2 * 15.25;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleCommissionedEmployeeNoSalesReceipts)
{
	GpayrollDatabase.clear();
	const int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
	t.Execute();
	const Date payDate(11, 9, 2001); // Friday
	PaydayTransaction pt(payDate);
	pt.Execute();
	const double countPay = 2500.00;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleCommissionedEmployeeOneSalesReceipt)
{
	GpayrollDatabase.clear();
	const int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
	t.Execute();
	const Date payDate(11, 9, 2001);
	SalesReceiptTransaction srt(payDate, 13000.00, empId);
	srt.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	const double countPay = 2500.00 + .032 * 13000;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleCommissionedEmployeeTwoSalesReceipts)
{
	GpayrollDatabase.clear();
	const int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
	t.Execute();
	const Date payDate(11, 9, 2001); // Biweekly Friday
	SalesReceiptTransaction srt(payDate, 13000.00, empId);
	srt.Execute();
	SalesReceiptTransaction srt2(Date(11, 8, 2001), 24000, empId);
	srt2.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	const double countPay = 2500.00 + .032 * 13000 + .032 * 24000;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestPaySingleCommissionedEmployeeWrongDate)
{
	GpayrollDatabase.clear();
	const int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
	t.Execute();
	const Date payDate(11, 16, 2001);
	SalesReceiptTransaction srt(payDate, 13000.00, empId);
	srt.Execute();
	SalesReceiptTransaction srt2(Date(11, 15, 2001), 24000, empId);
	srt2.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc == 0);
}
TEST(PayrollTest, TestPaySingleCommissionedEmployeeSpanMultiplePayPeriods)
{
	GpayrollDatabase.clear();
	int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
	t.Execute();
	Date earlyDate(11, 9, 2001);
	Date payDate(11, 23, 2001);
	Date lateDate(12, 7, 2001);
	SalesReceiptTransaction srt(payDate, 13000.00, empId);
	srt.Execute();
	SalesReceiptTransaction srt2(earlyDate, 24000, empId);
	srt2.Execute();
	SalesReceiptTransaction srt3(lateDate, 15000, empId);
	srt3.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();

	const double countPay = 2500.00 + .032 * 13000;
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(countPay, pc->GetGrossPay(), .001);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(0.0, pc->GetDeductions(), .001);
	ASSERT_DOUBLE_EQ(countPay, pc->GetNetPay(), .001);
}
TEST(PayrollTest, TestSalariedUnionMemberDues)
{
	GpayrollDatabase.clear();
	const int empId = 1;
	AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
	t.Execute();
	const int memberId = 7734;
	ChangeMemberTransaction cmt(empId, memberId, 9.42);
	cmt.Execute();
	const Date payDate(11, 30, 2001);
	const int fridays = 5;
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(1000.00, pc->GetGrossPay(), 0.01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(fridays * 9.42, pc->GetDeductions(), 0.01);
	ASSERT_DOUBLE_EQ(1000.0 - (fridays * 9.42), pc->GetNetPay(), 0.01);
}
TEST(PayrollTest, TestHourlyUnionMemberDues)
{
	GpayrollDatabase.clear();
	const int empId = 1;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
	t.Execute();
	const int memberId = 7734;
	ChangeMemberTransaction cmt(empId, memberId, 9.42);
	cmt.Execute();
	const Date payDate(11, 9, 2001);
	TimeCardTransaction tct(payDate, 8.0, empId);
	tct.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(8 * 15.24, pc->GetGrossPay(), 0.01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(9.42, pc->GetDeductions(), 0.01);
	ASSERT_DOUBLE_EQ((8 * 15.24) - 9.42, pc->GetNetPay(), 0.01);
}
TEST(PayrollTest, TestCommissionedUnionMemberDues)
{
	GpayrollDatabase.clear();
	const int empId = 3;
	AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
	t.Execute();
	const int memberId = 7734;
	ChangeMemberTransaction cmt(empId, memberId, 9.42);
	cmt.Execute();
	const Date payDate(11, 9, 2001);
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(2500.00, pc->GetGrossPay(), 0.01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(2 * 9.42, pc->GetDeductions(), 0.01);
	ASSERT_DOUBLE_EQ(2500.0 - (2 * 9.42), pc->GetNetPay(), 0.01);
}
TEST(PayrollTest, TestHourlyUnionMemberServiceCharge)
{
	GpayrollDatabase.clear();
	const int empId = 1;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
	t.Execute();
	const int memberId = 7734;
	ChangeMemberTransaction cmt(empId, memberId, 9.42);
	cmt.Execute();
	const Date payDate(11, 9, 2001);
	ServiceChargeTransaction sct(memberId, payDate, 19.42);
	sct.Execute();
	TimeCardTransaction tct(payDate, 8.0, empId);
	tct.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(8 * 15.24, pc->GetGrossPay(), 0.01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(9.42 + 19.42, pc->GetDeductions(), 0.01);
	ASSERT_DOUBLE_EQ((8 * 15.24) - (9.42 + 19.42), pc->GetNetPay(), 0.01);
}
TEST(PayrollTest, TestServiceChargesSpanningMultiplePayPeriods)
{
	GpayrollDatabase.clear();
	int empId = 1;
	AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
	t.Execute();
	int memberId = 7734;
	ChangeMemberTransaction cmt(empId, memberId, 9.42);
	cmt.Execute();
	Date earlyDate(11, 2, 2001); // previous Friday
	Date payDate(11, 9, 2001);
	Date lateDate(11, 16, 2001); // next Friday
	ServiceChargeTransaction sct(memberId, payDate, 19.42);
	sct.Execute();
	ServiceChargeTransaction sctEarly(memberId, earlyDate, 100.00);
	sctEarly.Execute();
	ServiceChargeTransaction sctLate(memberId, lateDate, 200.00);
	sctLate.Execute();
	TimeCardTransaction tct(payDate, 8.0, empId);
	tct.Execute();
	PaydayTransaction pt(payDate);
	pt.Execute();
	PayCheck* pc = pt.GetPaycheck(empId);
	ASSERT_TRUE(pc);
	ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
	ASSERT_DOUBLE_EQ(8 * 15.24, pc->GetGrossPay(), 0.01);
	ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
	ASSERT_DOUBLE_EQ(9.42 + 19.42, pc->GetDeductions(), 0.01);
	ASSERT_DOUBLE_EQ((8 * 15.24) - (9.42 + 19.42), pc->GetNetPay(), 0.01);
}
TEST(PayrollTest, TestChangeUnaffiliatedTransaction)
{
	GpayrollDatabase.clear();
	int empId = 5;
	int memberId = 1422;
	AddHourlyEmployee t(empId, "Fill", "Home", 14.64);
	t.Execute();
	ChangeMemberTransaction cmt(empId, memberId, 51.26);
	cmt.Execute();
	ChangeUnaffiliatedTransaction cut(empId);
	cut.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	Affiliation* af = e->GetAffiliation();
	ASSERT_TRUE(af);
	NoAffiliation* nf = dynamic_cast<NoAffiliation*>(af);
	ASSERT_TRUE(nf);
	Employee* member = GpayrollDatabase.GetUnionMember(memberId);
	ASSERT_TRUE(member == 0);
}
TEST(PayrollTest, TestChangeMailTransaction)
{
	GpayrollDatabase.clear();
	int empId = 5;
	AddHourlyEmployee t(empId, "Fill", "Home", 14.64);
	t.Execute();
	ChangeMailTransaction cmt(empId, "21 great street");
	cmt.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentMethod* pm = e->GetMethod();
	ASSERT_TRUE(pm);
	MailMethod* mm = dynamic_cast<MailMethod*>(pm);
	ASSERT_TRUE(mm);
	ASSERT_TRUE("21 great street" == mm->GetAddress());
}
TEST(PayrollTest, TestChangeDirectTransaction)
{
	GpayrollDatabase.clear();
	int empId = 5;
	AddHourlyEmployee t(empId, "Fill", "Home", 14.64);
	t.Execute();
	ChangeDirectTransaction cdt(empId, "BTBANK", "6151848");
	cdt.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentMethod* pm = e->GetMethod();
	ASSERT_TRUE(pm);
	DirectMethod* dm = dynamic_cast<DirectMethod*>(pm);
	ASSERT_TRUE(dm);
	ASSERT_TRUE("BTBANK" == dm->GetBank());
	ASSERT_TRUE("6151848" == dm->GetAccount());
}
TEST(PayrollTest, TestChangeHoldTransaction)
{
	GpayrollDatabase.clear();
	const int empId = 5;
	AddHourlyEmployee t(empId, "Fill", "Home", 14.64);
	t.Execute();
	ChangeDirectTransaction cdt(empId, "BTBANK", "6151848");
	cdt.Execute();
	ChangeHoldTransaction cht(empId);
	cht.Execute();
	Employee* e = GpayrollDatabase.GetEmployee(empId);
	ASSERT_TRUE(e);
	PaymentMethod* pm = e->GetMethod();
	ASSERT_TRUE(pm);
	HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
	ASSERT_TRUE(hm);
}