#pragma once
#include <iostream>
// #include "../CurrencyExchange/clsCurrency.h"
#include "clsShowListCurrenciesScreen.h"
#include "clsShowFindCurrenciesScreen.h"
#include "clsShowUpdateCurrenciesScreen.h"
#include "clsShowCurrenciesCalculatorScreen.h"
#include "clsScreen.h"

using namespace std;

class clsShowCurrencyExchangeScreen : protected clsScreen
{
    enum enCurrencyExchangeMenueOption
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();

        cout << "\n_____________________________\n";
    }

    static short _ReadCurrencyMenueOption()
    {
        cout << "Choose what do u want to do" << endl;
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5);
        return Choice;
    }

    static void _ShowListCurrenciesScreen()
    {
        clsShowListCurrenciesScreen::ShowCurrencyListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsShowFindCurrencyScreen::ShowCurrencyFindScreen();
    }

    static void _ShowUpdateCurrencyScreen()
    {
        clsShowUpdateCurrenciesScreen::ShowCurrencyUpdateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsShowCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _ShowMainMenueScreen()
    {
    }

    static void _GoBackToCurrencyExchangeMenue()
    {
        getchar();
        cout << "Press Any Key to Go Back To CurrencyExchange Menue..." << endl;
        getchar();
        ShowCurrencyScreen();
    }

    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOption Choice)
    {
        switch (Choice)
        {

        case enCurrencyExchangeMenueOption::eListCurrencies:
            system("clear");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOption::eFindCurrency:
            system("clear");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOption::eUpdateRate:
            system("clear");
            _ShowUpdateCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        case enCurrencyExchangeMenueOption::eCurrencyCalculator:
            system("clear");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeMenueOption::eMainMenue:
        }
    }

public:
    static void ShowCurrencyScreen()
    {
        system("clear");
        _DrawScreenHeader("CurrencyExchange Screen");

        cout << setw(37) << left << "" << "=================================" << endl;
        cout << setw(37) << left << "" << "\t [1]ListCurrencies" << endl;
        cout << setw(37) << left << "" << "\t [2]Find Currency" << endl;
        cout << setw(37) << left << "" << "\t [3]Update Rate" << endl;
        cout << setw(37) << left << "" << "\t [4]Currency Calculator" << endl;
        cout << setw(37) << left << "" << "\t [5]MainMenue" << endl;
        cout << setw(37) << left << "" << "=================================" << endl;

        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOption)_ReadCurrencyMenueOption());

        return;
    }
};