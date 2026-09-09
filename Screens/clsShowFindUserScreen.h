#pragma once
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "../clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("Find User Screen    ");

        cout << "Please Enter UserName to Find: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "UserName Is Not Exist Enter New UserName" << endl;
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        if (User.IsEmpty())
            cout << "User Is Not found" << endl;
        else
        {
            cout << "\nUser Found" << endl;
            _PrintUser(User);
        }
    }
};