#include <iostream>
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"
#include "../clsBankClientTest.h"

using namespace std;

class clsShowDeleteClientScreen : protected clsScreen
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

public:
    static void DeleteClient()
    {
        char Answer;
        _DrawScreenHeader("Delete Screen");
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        cout << "Please Enter Number's of Account to Delete" << endl;
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Is Not Exist ,Enter Account Number Agian:\n"
                 << endl;
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _Print(Client);

        cout << "Do u want to delete it y/n?:" << endl;
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.DeleteClient())
            {
                cout << "Client has deleted succesfully\n"
                     << endl;
                _Print(Client);
            }
            else
                cout << "\n Error , Client was not deleted" << endl;
        }
    }
};