#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"
#include "../Libraries/clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsShowFindScreen : protected clsScreen
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

public:
    static void ShowFindClientScreen()
    {
        _DrawScreenHeader("Find Client Screen");

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        cout << "Enter Account Number To Find" << endl;
        string AccountNumber = clsInputValidate::ReadString();

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.clsBankClient::IsEmpty())
            cout << "Client Has Not Found " << endl;

        else
            _PrintClientCard(Client);

        return;
    }
};