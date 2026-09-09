#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"
#include "clsScreen.h"

using namespace std;

class clsShowDepositScreen : protected clsScreen
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
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("Transactions Menue", "\tDeposit Screen");

        string AccountNumber = _ReadAccountNumber();

        while (true)
        {

            if (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "Account is not exist enter anothor account number:" << endl;

                string AccountNumber = clsInputValidate::ReadString();
            }
            else
                break;
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "Enter Amount of Money u want to deposit" << endl;
        double Ammount = clsInputValidate::ReadDblNumber();

        cout << "Are you sure you want to deposit this ammount of money ?" << endl;
        char k;
        cin >> k;

        if (k == 'y' || k == 'Y')
        {

            Client.Deposit(Ammount);
            cout << "New balacne is" << Client.GetAccountBalance() << endl;

            cout << "Done Succefully" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "New data" << endl;

            _PrintClientCard(Client);
        }
        else
        {
            cout << "Deposit is not saved" << endl;
            return;
        }
    }
};