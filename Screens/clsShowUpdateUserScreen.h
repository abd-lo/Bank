#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
    static int _ReadUserPermissions()
    {
        int Permissions = 0;
        char Choice;

        cout << "Do u want full access? Y/N: " << endl;
        cin >> Choice;
        if (Choice == 'y' || Choice == 'Y')
        {
            return -1;
        }
        else
        {

            cout << "Do u want access To List Clients ? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pListClients;
            }

            cout << "Do u want access To AddNewClient? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "Do u want access Delete Client ? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "Do u want access Update Clients? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pUpdateClients;
            }

            cout << "Do u want access Find Clients ? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pFindClient;
            }

            cout << "Do u want access Transactions? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pTransactions;
            }

            cout << "Do u want access ManageUsers ? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pManageUsers;
            }
            cout << "Do u want access RegisterLogin ? Y/N: " << endl;
            cin >> Choice;
            if (Choice == 'y' || Choice == 'Y')
            {
                Permissions += clsUser::enPermissions::pRegisterLogin;
            }

            return Permissions;
        }
    }

    static void _ReadUserInfo(clsUser &User)
    {
        cout << "ENTERING NEW INFO" << endl;

        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter New User Permissions: ";
        User.SetPermissions(_ReadUserPermissions());
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nUserName : " << User.GetUserName();
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.GetFullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions     : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

public:
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("Update User Screen");

        cout << "Please Enter UserName to Update its info" << endl;
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "UserName IsNot Exist ReEnter UserName" << endl;
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);
        cout << "Do you want to Update it Y/N ?" << endl;
        char k;
        cin >> k;

        if (k == 'y' || k == 'Y')
        {
            _ReadUserInfo(User);
            clsUser::enSaveResults SaveResult;
            SaveResult = User.Save();

            if (SaveResult == clsUser::enSaveResults::enSaveSucceed)
            {
                cout << "Updated Successfully\n"
                     << endl;
                cout << "Updated User Info:\n"
                     << endl;

                _PrintUser(User);
            }

            else
                cout << "Failed To Update" << endl;
        }
    }
};