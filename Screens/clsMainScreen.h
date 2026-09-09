#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Global.h"
#include "../Libraries/clsInputValidate.h"
#include "clsShowAllClientsList.h"
#include "clsAddNewClientScreen.h"
#include "clsShowDeleteClientScreen.h"
#include "clsShowUpdateScreen.h"
#include "clsShowFindScreen.h"
#include "clsShowTransactionsScreen.h"
#include "clsShowManageUsersScreen.h"
#include "clsShowRegisterLoginScreen.h"
#include "clsShowCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eReisterLogin = 8,
        eCurrencyExchange = 9,
        eExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        getchar();
        // int k;
        // cin >> k;
        getchar();
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsShowAllClientsList::ShowAllClients();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::AddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsShowDeleteClientScreen::DeleteClient();
    }

    static void _ShowUpdateClientScreen()
    {
        clsShowUpdateScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsShowFindScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsShowTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersMenue()
    {
        clsShowManageUsersScreen::ShowManageUsersScreen();
    }

    static void _ShowRegisterLoginsScreen()
    {
        clsShowRegisterLoginScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen()
    {
        clsShowCurrencyExchangeScreen::ShowCurrencyScreen();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("clear");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("clear");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("clear");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("clear");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("clear");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("clear");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("clear");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eReisterLogin:
            system("clear");
            _ShowRegisterLoginsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("clear");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("clear");
            _Logout();
            // Login();

            break;
        }
    }

public:
    static void ShowMainMenue()
    {

        system("clear");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] RegisterLogins.\n";
        cout << setw(37) << left << "" << "\t[9] CurrencyExchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }
};
