#include <iostream>
#include <fstream>
#include <string>
#include "../Libraries/clsString.h"
#include <vector>
using namespace std;

class clsCurrency
{
	enum enMode
	{
		enEmpty = 1,
		enUpdate = 2
	};

	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _CurrencyRate;
	// ReadFromFile

	static clsCurrency _ConvertLineCurrencyToObject(string Line)
	{

		vector<string> vCurrencyData = clsString::Split(Line, "#//#");
		return clsCurrency(enMode::enUpdate, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static vector<clsCurrency> _LoadCurrecnyListFromFile()
	{

		fstream MyFile;
		string Line;
		vector<clsCurrency> vCurrenciesData;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineCurrencyToObject(Line);
				vCurrenciesData.push_back(Currency);
			}

			MyFile.close();
		}
		return vCurrenciesData;
	}

	// WriteToFile
	string _PrepareRecordLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string Line = Currency._Country + Seperator;
		Line += Currency._CurrencyCode + Seperator;
		Line += Currency._CurrencyName + Seperator;
		Line += to_string(Currency._CurrencyRate);
		return Line;
	}

	void _SaveDataToFile(vector<clsCurrency> _vCurrency)
	{
		fstream MyFile;
		string Line;

		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency &i : _vCurrency)
			{
				MyFile << _PrepareRecordLine(i, "#//#") << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{

		vector<clsCurrency> _vCurrency = _LoadCurrecnyListFromFile();
		cout << "BeforerSave" << endl;

		for (clsCurrency &i : _vCurrency)
		{
			if (i._CurrencyCode == _CurrencyCode)
			{
				i = *this;
				break;
			}
		}

		_SaveDataToFile(_vCurrency);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float CurrencyRate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_CurrencyRate = CurrencyRate;
	}

	static clsCurrency GetEmpty()
	{
		return clsCurrency(enMode::enEmpty, "", "", "", 0);
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::enEmpty);
	}

	string GetCountry()
	{
		return _Country;
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	float GetRate()
	{
		return _CurrencyRate;
	}

	void SetRate(float Rate)
	{
		_CurrencyRate = Rate;
	}

	static vector<clsCurrency> GetCurrencyList()
	{
		return _LoadCurrecnyListFromFile();
	}

	void UpdateRate(float NewRate)
	{
		_CurrencyRate = NewRate;
		cout << "After" << endl;
		_Update();
	}

	static clsCurrency FindByCode(string CountryCode)
	{
		CountryCode = clsString::UpperAllString(CountryCode);

		fstream MyFile;
		string Line;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCurrency C = _ConvertLineCurrencyToObject(Line);
				if (clsString::UpperAllString(C._CurrencyCode) == CountryCode)
				{
					MyFile.close();
					return C;
				}
			}
		}

		else
			return GetEmpty();
	}

	static clsCurrency FindByCountryName(string CountryName)
	{
		CountryName = clsString::UpperAllString(CountryName);

		fstream MyFile;
		string Line;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsCurrency C = _ConvertLineCurrencyToObject(Line);
				if (clsString::UpperAllString(C._Country) == CountryName)
				{
					MyFile.close();
					return C;
				}
			}
		}

		else
			return GetEmpty();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	float ConvertToDollar(float Amount)
	{
		return Amount / GetRate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency SecondCurrency)
	{
		float AmountInDollar = Amount;
		if (GetCurrencyCode() != "USD")
		{
			AmountInDollar = ConvertToDollar(Amount);
		}

		if (SecondCurrency.GetCurrencyCode() == "USD")
		{
			return AmountInDollar;
		}

		else
		{
			return AmountInDollar * SecondCurrency.GetRate();
		}
	}
};