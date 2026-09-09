#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewUsertScreen : protected clsScreen
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

            cout << "Do u want access To ListClients ? Y/N: " << endl;
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

        cout << "\nPermissions Settings: ";
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
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("Add New User Screen    ");

        cout << "Please Enter UserName to Add" << endl;
        string UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "UserName Is Exist Enter New UserName" << endl;
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(User);
        _PrintUser(User);

        clsUser::enSaveResults SaveResults;
        cout << "Test" << endl;

        SaveResults = User.Save();
        cout << "Test2" << endl;

        switch (SaveResults)
        {
        case clsUser::enSaveResults::enSaveFailedEmptyObject:
            cout << "Save Failed,Empty Object" << endl;
            break;

        case clsUser::enSaveResults::enSaveSucceed:
            cout << "New User Added" << endl;
            break;

        case clsUser::enSaveResults::enSaveFailedUserExist:
            cout << "Failed To Save ,User Is Exist" << endl;
            break;

        default:
            break;
        }
    }
};