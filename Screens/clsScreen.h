#pragma once
#include <iostream>
#include "../clsUser.h"
#include "../Global.h"
#include "../Libraries/clsDate.h"
#include "../CurrencyExchange/clsCurrency.h"
using namespace std;

class clsScreen
{
protected:
    static void _PrintUserNameAndDate()
    {

        cout << "\t\t\t\t\t  " << "UserName: " << CurrentUser.GetUserName() << endl;
        cout << "\t\t\t\t\t  Date: " << clsDate::DateToString(clsDate()) << endl;
    }

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        _PrintUserNameAndDate();
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
    }

    static bool CheckAccessRights(clsUser::enPermissions ScreenPermissions)
    {
        if (!CurrentUser.CheckAccessPermission(ScreenPermissions))
        {
            cout << "___________________________________________\n"
                 << endl;
            cout << "Access Denied Contact Your Admin\n"
                 << endl;
            cout << "___________________________________________\n"
                 << endl;
            return 0;
        }
        else
            return 1;
    }
};