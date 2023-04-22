#pragma once
#include <string>
#include <iostream>

using namespace std;

class Date
{
public:
    enum class DayOfWeek
    {
        sunday = 0,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday
    };

    // Canonical Form
    Date();
    Date(int month, int day, int year);
    Date(const Date&);
    virtual ~Date() = default;
    Date& operator=(const Date&);
    Date(Date&& other) noexcept = default;
    Date& operator=(Date&& other) noexcept = default;

    // Accessors
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;
    DayOfWeek GetDayOfWeek() const;
    std::string GetDayOfWeekName() const;

    // Input & Output
    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);

    // Arithmetic and comparison operators
    int operator==(const Date&) const;
    int operator!=(const Date&) const;
    int operator<(const Date&) const;
    int operator>(const Date&) const;
    int operator<=(const Date&) const;
    int operator>=(const Date&) const;
    friend Date operator+(int, const Date&);
    friend Date operator+(const Date&, int);
    Date operator-(int) const;
    int operator-(const Date&) const;
    Date& operator+=(int);
    Date& operator-=(int);
    Date& operator++();
    Date operator++(int); // postfix
    Date& operator--();
    Date operator--(int); // postfix

    static bool IsBetween(const Date& theDate, const Date& startDate, const Date& endDate)
    {
        return (theDate >= startDate) && (theDate <= endDate);
    }

private:
    time_t itsTime = {};
    tm itsTimeStruct = {};

    static long secondsPerDay;
};