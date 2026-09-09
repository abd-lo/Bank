#pragma once
#include <iostream>
// #include "../CurrencyExchange/clsCurrency.h"
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"

using namespace std;

class clsShowUpdateCurrenciesScreen : public clsScreen
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

    static string _ReadCurrencyCode()
    {
        string CurrencyCode;
        cout << "enter Currency Code:  " << endl;
        cin >> CurrencyCode;
        return CurrencyCode;
    }

public:
    static void ShowCurrencyUpdateScreen()
    {
        system("clear");
        _DrawScreenHeader("Currencies Find Screen");
        string CurrenCode = _ReadCurrencyCode();

        clsCurrency Currency = clsCurrency::FindByCode(CurrenCode);

        if (Currency.IsEmpty())
        {
            cout << "Currency Has'nt been Found" << endl;
            return;
        }
        else
        {
            _PrintCurrency(Currency);

            cout << "Do u Want to Update the Rate?" << endl;

            char answer;
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                float NewRate;
                cout << "\nEnter New Rate:";
                cin >> NewRate;

                Currency.UpdateRate(NewRate);
                _PrintCurrency(Currency);
            }
        }
    }
};