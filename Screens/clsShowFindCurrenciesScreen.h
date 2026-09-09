#pragma once
#include <iostream>
// #include "../CurrencyExchange/clsCurrency.h"
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"

using namespace std;

class clsShowFindCurrencyScreen : public clsScreen
{
    enum enSearchType
    {
        eByNume = 1,
        eByCode = 2
    };

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "__________________" << endl;
        cout << "" << endl;

        cout << "Country      :  " << clsUtil::Tabs(1) << Currency.GetCountry() << endl;
        cout << "CurrencyCode :  " << clsUtil::Tabs(1) << Currency.GetCurrencyCode() << endl;
        cout << "CurrencyName :  " << clsUtil::Tabs(1) << Currency.GetCurrencyName() << endl;
        cout << "Rate         :  " << clsUtil::Tabs(1) << Currency.GetRate() << endl;

        cout << "" << endl;
        cout << "__________________" << endl;
    }

    static enSearchType ReadUserChoice(string &NameOrCode)
    {
        short ChoiceOfSearch;
        cout << "Search with [1] Country Name  [2]CountryCode:  ";
        ChoiceOfSearch = clsInputValidate::ReadShortNumberBetween(1, 2);

        if (ChoiceOfSearch == enSearchType::eByNume)
            cout << "Enter CountryName" << endl;

        else
            cout << "Enter Currency Code" << endl;

        NameOrCode = clsInputValidate::ReadString();

        return (enSearchType)ChoiceOfSearch;
    }

public:
    static void ShowCurrencyFindScreen()
    {
        system("clear");
        _DrawScreenHeader("Currencies Find Screen");
        string NameOrCode;

        if (enSearchType::eByNume == ReadUserChoice(NameOrCode))
        {
            clsCurrency Currency = clsCurrency::FindByCountryName(NameOrCode);
            if (Currency.IsEmpty())
            {
                cout << "Currency Has'nt been Found" << endl;
                return;
            }
            _PrintCurrency(Currency);
        }
        else
        {
            clsCurrency Currency = clsCurrency::FindByCode(NameOrCode);
            if (Currency.IsEmpty())
            {
                cout << "Currency Has'nt been Found" << endl;
                return;
            }
            _PrintCurrency(Currency);
        }
    }
};