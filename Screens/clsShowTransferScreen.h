#pragma once
#include <iostream>
#include <iomanip>
#include "../clsBankClientTest.h"
#include "clsScreen.h"
#include "clsMainScreen.h"

using namespace std;

class clsShowTransferScreen : protected clsScreen
{
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string Phrase)
    {
        string AccountNumber;

        cout << Phrase << endl;
        cin >> AccountNumber;

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccountNumber Is invalid" << endl;

            cout << Phrase << endl;
            cin >> AccountNumber;
        }
        return AccountNumber;
    }

    static double _ReadAmount(clsBankClient SourceClient)
    {
        double Amount;

        cout << "Enter Amount Moneny You Need To Transfer" << endl;
        cin >> Amount;

        while (Amount > SourceClient.GetAccountBalance())
        {

            cout << "Amount Exeeded Your account balance" << endl;
            cout << "Your Balance Is: " << SourceClient.GetAccountBalance() << endl;
            cout << "" << endl;

            cout << "Enter Amount Moneny You Need To Transfer" << endl;
            cin >> Amount;
        }
        return Amount;
    }

public:
    static void ShowTransferScreen()
    {
        system("clear");
        _DrawScreenHeader("Transaction Screen");
        double Amount;

        clsBankClient Source_Client = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number to Transfer From:"));
        _PrintClientCard(Source_Client);

        clsBankClient Destination_Client = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number to Transfer To:"));
        _PrintClientCard(Destination_Client);
        Amount = _ReadAmount(Source_Client);
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Source_Client.Transfer(Amount, Destination_Client))

        {
            cout << "Done Succefully" << endl;
        }
        else
            cout << "Failed" << endl;

        _PrintClientCard(Source_Client);
        cout << "" << endl;

        _PrintClientCard(Destination_Client);

        return;
    }
};