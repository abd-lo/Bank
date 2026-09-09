#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"
#include "clsScreen.h"

using namespace std;

class clsShowWithdrawScreen : protected clsScreen
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
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("Transactions Menue", "\n Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account is not exist enter anothor account number:" << endl;
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClientCard(Client);
        double amount = 0;

        cout << "Enter Amount of Money u want to WithDraw" << endl;
        amount = clsInputValidate::ReadDblNumber();
        cout << "\nAre you sure you want to Withdraw this amount of money ?" << endl;
        char k;
        cin >> k;

        if (k == 'y' || k == 'Y')
        {
            if (!Client.WithDraw(amount))
            {

                cout << "Error ,The amount you entered is bigger than your Balance" << endl;
            }
            if (Client.WithDraw(amount))
            {
                cout << "Done Succefully" << endl;

                cout << "New balacne is" << Client.GetAccountBalance() << endl
                     << endl;
            }
        }
        else
        {
            cout << "WithDraw is cancelled" << endl;
            return;
        }
    }
};