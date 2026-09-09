#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsDate
{
private:
	short _Year = 1900, _Month = 1, _Day = 1;

public:
	// Set And Get
	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}
	// Split
	void Split(vector<string> &vDate, string stDate, string Delimiter = "/")
	{
		short Pos = 0;

		while ((Pos = stDate.find(Delimiter)) != std::string::npos)
		{
			vDate.push_back(stDate.substr(0, Pos));
			stDate = stDate.erase(0, Pos + 1);
		}
		if (stDate != "")
			vDate.push_back(stDate);
	}

	static bool IsLeapYear(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	void GetDateAfterAddingDays(short DaysToAdd, short Year)
	{
		_Day = DaysToAdd;
		_Month = 1;
		_Year = Year;

		while (_Day > NumberOfDaysInMonth(_Year, _Month))
		{
			_Day -= NumberOfDaysInMonth(_Year, _Month);
			_Month++;

			if (_Month > 12)
			{
				_Year++;
				_Month = 1;
			}
		}
	}

	// Constructor

	clsDate()
	{
		time_t now = time(0);			 // Get the current time
		tm *ltm = localtime(&now); // Convert to local time format
		_Year = 1900 + ltm->tm_year;
		_Month = 1 + ltm->tm_mon;
		_Day = ltm->tm_mday;
	}

	clsDate(string stDate1)
	{
		vector<string> vDate1;
		Split(vDate1, stDate1);
		_Day = stoi(vDate1[0]);
		_Month = stoi(vDate1[1]);
		_Year = stoi(vDate1[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short Days, short Year)
	{
		GetDateAfterAddingDays(Days, Year);
	}

	clsDate static GetCurrentTime()
	{
		// system date
		time_t t = time(0);
		tm *now = localtime(&t);
		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		return clsDate(Day, Month, Year);
	}
	static string GetCurrentTimeWithM_S()
	{
		time_t t = time(0);
		tm *now = localtime(&t);
		short Seconds, Mintues, Hours, Day, Month, Year;
		string time;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		Hours = now->tm_hour;
		Mintues = now->tm_min;
		Seconds = now->tm_sec;
		time = to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + "  -  " + to_string(Hours) + ":" + to_string(Mintues) + ":" + to_string(Seconds);
		return time;
	}

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	// Calculate Age

	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}

		short NumberOfDaysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDaysInMonth[Month];
	}

	static bool IsItLastMonth(short MonthOrder)
	{

		return (MonthOrder == 12);
	}

	static bool IsLastDay(clsDate Date)
	{
		return (NumberOfDaysInMonth(Date._Year, Date._Month) == Date._Day);
	}

	static clsDate AddOneDay(clsDate &Date)
	{
		if (IsLastDay(Date))
		{
			if (IsItLastMonth(Date._Month))
			{
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
		{
			Date._Day++;
		}
		return Date;
	}

	void AddOneDay()

	{
		*this = AddOneDay(*this);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
	}
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		if (Date1._Year < Date2._Year)
			return true;

		else if (Date1._Year == Date2._Year && Date1._Month < Date2._Month)
			return true;

		else if (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day < Date2._Day)
			return true;

		else
			return false;
	}

	static void SwapDates(clsDate &Date1, clsDate &Date2)
	{

		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool SwapFlagValue = 1)
	{
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			// Swap Dates
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			AddOneDay(Date1); // Now modifies Date1 directly
		}
		return Days;
		// return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	short GetDifferenceInDays(clsDate Date1)
	{
		return GetDifferenceInDays(Date1, *this);
	}

	static int AgeCalculator(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetCurrentTime());
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date._Day > 31 || Date._Day < 1 || Date._Month > 12 || Date._Month < 1)
		{
			return 0;
		}

		if (Date._Day > NumberOfDaysInMonth(Date._Year, Date._Month))
		{
			return 0;
		}

		if (Date._Month == 2 && IsLeapYear(Date._Year) && Date._Day > 29)
		{
			return 0;
		}

		if (Date._Month == 2 && !(IsLeapYear(Date._Year)) && Date._Day > 28)
		{
			return 0;
		}

		return 1;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}
	static short NumberOfDaysInAYear(short Year)
	{
		return IsLeapYear(Year) ? 365 : 364;
	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear();
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{

		if (Month < 1 || Month > 12)
			return 0;

		int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return NumberOfHoursInAMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		// 0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

		return arrDayNames[DayOfWeekOrder];
	}

	static string DayShortName(short Day, short Month, short Year)
	{

		string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
	}

	string DayShortName()
	{

		string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = {"Jan", "Feb", "Mar",
												 "Apr", "May", "Jun",
												 "Jul", "Aug", "Sep",
												 "Oct", "Nov", "Dec"};

		return (Months[MonthNumber - 1]);
	}

	string MonthShortName()
	{

		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;

		// Index of the day from 0 to 6
		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		// Print the current month name
		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(int Year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar()
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", _Year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, _Year);
		}

		return;
	}

	static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{

		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	short DaysFromTheBeginingOfTheYear()
	{

		return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{

		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}

			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static clsDate IncreaseDateByOneWeek(clsDate &Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	clsDate IncreaseDateByXWeeks(short Weeks, clsDate &Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	clsDate IncreaseDateByOneMonth(clsDate &Date)
	{

		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}

		// last check day in date should not exceed max days in the current month
		//  example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
		//  be 28/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{

		IncreaseDateByOneMonth(*this);
	}

	clsDate IncreaseDateByXDays(short Days, clsDate &Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{

		IncreaseDateByXDays(Days, *this);
	}

	clsDate IncreaseDateByXMonths(short Months, clsDate &Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate &Date)
	{
		Date._Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	clsDate IncreaseDateByXYears(short Years, clsDate &Date)
	{
		Date._Year += Years;
		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years);
	}

	clsDate IncreaseDateByOneDecade(clsDate &Date)
	{
		// Period of 10 years
		Date._Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	clsDate IncreaseDateByXDecades(short Decade, clsDate &Date)
	{
		Date._Year += Decade * 10;
		return Date;
	}

	void IncreaseDateByXDecades(short Decade)
	{
		IncreaseDateByXDecades(Decade, *this);
	}

	clsDate IncreaseDateByOneCentury(clsDate &Date)
	{
		// Period of 100 years
		Date._Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	clsDate IncreaseDateByOneMillennium(clsDate &Date)
	{
		// Period of 1000 years
		Date._Year += 1000;
		return Date;
	}

	clsDate IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else
			{

				Date._Month--;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}
		}
		else
		{
			Date._Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate &Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate &Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate &Date)
	{

		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;

		// last check day in date should not exceed max days in the current month
		//  example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
		//  be 28/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate &Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate &Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate &Date)
	{

		Date._Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate &Date)
	{

		Date._Year -= Years;
		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate &Date)
	{
		// Period of 10 years
		Date._Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate &Date)
	{

		Date._Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate &Date)
	{
		// Period of 100 years
		Date._Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate &Date)
	{
		// Period of 1000 years
		Date._Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static short IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
	}

	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		// Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		// Weekends are Sun,Mon,Tue,Wed and Thur

		/*
short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
return  (DayIndex >= 5 && DayIndex <= 4);
		*/

		// shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{

		clsDate EndOfMontDate;
		EndOfMontDate._Day = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
		EndOfMontDate._Month = Date1._Month;
		EndOfMontDate._Year = Date1._Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date1)
	{

		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date1._Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	// i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(DateFrom, DateTo);
	}
	// above method is eough , no need to have method for the object

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		// to add weekends
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare
	{
		Before = -1,
		Equal = 0,
		After = 1
	};

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
				return enDateCompare::After;*/

		// this is faster
		return enDateCompare::After;
	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}
};