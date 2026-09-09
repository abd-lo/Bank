#include <iostream>
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"

using namespace std;

class clsShowUpdateScreen : protected clsScreen
{
private:
    void static _Print(clsBankClient Client)
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

    static void _ReadClientInfo(clsBankClient &Client)
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

public:
    static void UpdateClient()
    {
        _DrawScreenHeader("Update Client Screen");
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;
        }
        cout << "Please Enter Number's of Account to update it's info" << endl;
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account isn't found Enter Valid Account Number" << endl;
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        cout << "Client Card :\n"
             << endl;

        _Print(Client1);
        _ReadClientInfo(Client1);

        clsBankClient::enSaveResults Save1;
        Save1 = Client1.Save();

        switch (Save1)
        {
        case clsBankClient::enSaveResults::enSaveSucceed:
            cout << "Client Data Has Updated" << endl;

            cout << "" << endl;
            cout << "" << endl;
            cout << "Client Card After Updating :\n"
                 << endl;
            _Print(Client1);

            break;

        case clsBankClient::enSaveResults::enSaveFailed:
            cout << "Client Update Failed , Because it's empty" << endl;

            break;

        default:
            break;
        }
    }
};