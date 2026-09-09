#pragma once
#include <iostream>
// #include "../CurrencyExchange/clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsShowListCurrenciesScreen : protected clsScreen
{

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
        cout << "| " << setw(8) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(45) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.GetRate();
    }

public:
    static void ShowCurrencyListScreen()
    {
        system("clear");
        _DrawScreenHeader("Currencies List Screen");
        vector<clsCurrency> vCurrency = clsCurrency::GetCurrencyList();

        cout << setw(20) << left << "" << "Number Of Currencies Found" << "[" << vCurrency.size() << "]" << endl;

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n"
             << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n"
             << endl;
        if (vCurrency.size() == 0)
        {
            cout << "No Currencies Found" << endl;
        }
        else
            for (clsCurrency &i : vCurrency)
            {

                _PrintCurrency(i);
                cout << endl;
            }

        return;
    }
};