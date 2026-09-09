#pragma once
#include <iostream>
#include <iomanip>
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"
#include "../Libraries/clsInputValidate.h"
#include "clsScreen.h"
#include "clsShowDepositScreen.h"
#include "clsShowWithdrawScreen.h"
#include "clsShowTotalBalancesScreen.h"
#include "clsShowTransferScreen.h"
#include "clsShowTransferLogScreen.h"
#include "clsMainScreen.h"

using namespace std;

class clsShowTransactionsScreen : protected clsScreen
{
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

    enum enTransactionsMenueOption
    {
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalances = 3,
        eShowTransfer = 4,
        eShowTransferLog = 5,
        eShowMainMenue = 6
    };

    static short _ReadTrasactionMenueOption()
    {
        cout << "Choose what do u want to do" << endl;
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }

    static void _ShowDepositScreen()
    {
        clsShowDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithDrawScreen()
    {
        clsShowWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowFindCurrencyScreen_ShowWithDrawScreen()
    {
        clsShowWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsShowTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen()
    {
        clsShowTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferLog::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "Press Any Key to Go Back To Transaction Menue..." << endl;
        getchar();
        getchar();
        ShowTransactionsScreen();
    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOption Choice)
    {
        switch (Choice)
        {

        case enTransactionsMenueOption::eDeposit:
            system("clear");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOption::eWithdraw:
            system("clear");
            _ShowWithDrawScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOption::eShowTotalBalances:
            system("clear");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOption::eShowTransfer:
            system("clear");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOption::eShowTransferLog:
            system("clear");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;

        case enTransactionsMenueOption::eShowMainMenue:
            // system("clear");
            // return;
            // // clsMainScreen::ShowMainMenue();
            // break;
        }
    }

public:
    static void ShowTransactionsScreen()
    {
        system("clear");
        _DrawScreenHeader("Transaction Screen");
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }
        cout << setw(37) << left << "" << "\t [1]Deposit" << endl;
        cout << setw(37) << left << "" << "\t [2]Withdraw" << endl;
        cout << setw(37) << left << "" << "\t [3]Balance" << endl;
        cout << setw(37) << left << "" << "\t [4]Transfer" << endl;
        cout << setw(37) << left << "" << "\t [5]TransferLog" << endl;
        cout << setw(37) << left << "" << "\t [6]MainMenue" << endl;

        _PerformTransactionsMenueOption((enTransactionsMenueOption)_ReadTrasactionMenueOption());

        return;
    }
};