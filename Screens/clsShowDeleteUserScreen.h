#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{

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
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Delete User Screen    ");

        cout << "Please Enter UserName to Delete" << endl;
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "UserName IsNot Exist ReEnter UserName" << endl;
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);
        cout << "Do you want to delete it Y/N ?" << endl;
        char k;
        cin >> k;
        if (k == 'y' || k == 'Y')
        {
            if (User.Delete())
                cout << "Deleted Successfully" << endl;

            else
                cout << "Failed To Delete" << endl;
        }
    }
};