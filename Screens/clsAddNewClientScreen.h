#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
    static void ReadClientInfo(clsBankClient &Client)
    {

        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
    }

    static void PrintClientCard(clsBankClient Client)
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
    static void AddNewClient()
    {
        _DrawScreenHeader("Add Client Screen    ");
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        cout << "Please Enter Number's of Account to Add" << endl;
        string AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Is Exist" << endl;
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);
        ReadClientInfo(Client);
        PrintClientCard(Client);
        clsBankClient::enSaveResults SaveResults;
        SaveResults = Client.Save();

        switch (SaveResults)
        {
        case clsBankClient::enSaveResults::enSaveFailed:
            cout << "Save Failed" << endl;
            break;

        case clsBankClient::enSaveResults::enSaveSucceed:
            cout << "New Client Added" << endl;
            break;

        case clsBankClient::enSaveResults::enClientExist:
            cout << "Client Is Exist" << endl;
            break;

        default:
            break;
        }
    }
};