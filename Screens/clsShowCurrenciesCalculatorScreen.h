#pragma once
#include <iostream>
// #include "../CurrencyExchange/clsCurrency.h"
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"

using namespace std;

class clsShowCurrencyCalculatorScreen : public clsScreen
{

    static void _PrintCurrency(clsCurrency Currency, string Title)
    {
        cout << "__________________" << endl;
        cout << "" << endl;
        cout << Title << endl;

        cout << "Country      :  " << clsUtil::Tabs(1) << Currency.GetCountry() << endl;
        cout << "CurrencyCode :  " << clsUtil::Tabs(1) << Currency.GetCurrencyCode() << endl;
        cout << "CurrencyName :  " << clsUtil::Tabs(1) << Currency.GetCurrencyName() << endl;
        cout << "Rate         :  " << clsUtil::Tabs(1) << Currency.GetRate() << endl;

        cout << "" << endl;
        cout << "__________________" << endl;
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;
        cout << "\n"
             << Message << endl;
        cin >> CurrencyCode;

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "Currency Is Not Exist " << endl;
            cout << "\n"

                 << Message << endl;
            cin >> CurrencyCode;
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
    }

    static void _PrintCalculationResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrintCurrency(CurrencyFrom, "From: ");
        float AmountInDollar = CurrencyFrom.ConvertToDollar(Amount);

        cout << Amount << " " << CurrencyFrom.GetCurrencyCode()

             << " = " << AmountInDollar << " USD\n";
        if (CurrencyTo.GetCurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";
        _PrintCurrency(CurrencyTo, "To");
        float AmountInSecondCurerncy = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

        cout << Amount << " " << CurrencyFrom.GetCurrencyCode()
             << " = " << AmountInSecondCurerncy << " " << CurrencyTo.GetCurrencyCode();
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'Y';
        while (Continue == 'y' || Continue == 'Y')
        {

            system("clear");
            string FirstCurrencyCode, SecondCurrencyCode;
            float Amount, AmountExchanged;

            _DrawScreenHeader("Currencies Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("Enter First Currency");
            clsCurrency CurrencyTo = _GetCurrency("Enter Second Currency");

            cout << "Enter Amount to Calculate" << endl;
            cin >> Amount;

            _PrintCalculationResults(Amount, CurrencyFrom, CurrencyTo);
            char Answer;
            cout << "Do Want To Make Other Calculation?" << endl;
            cin >> Answer;
            if (Answer != 'Y' || Answer != 'y')
                break;
        }
    }
};