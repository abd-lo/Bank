#pragma once
#include <iostream>
#include <iomanip>
#include "../Libraries/clsInputValidate.h"
#include "clsShowListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsShowDeleteUserScreen.h"
#include "clsShowUpdateUserScreen.h"
#include "clsShowFindUserScreen.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "../clsUser.h"
using namespace std;

class clsShowManageUsersScreen : protected clsScreen
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

    enum enManageUsersMenu
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << "" << "Choose what do u want to do" << endl;
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }

    static void _ShowListUsersScreen()
    {
        clsShowListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUsertScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "Press Any Key to Go Back To MangeUsers Menue..." << endl;
        getchar();
        getchar();
        ShowManageUsersScreen();
    }

    static void _PerformManageUsersMenueOption(enManageUsersMenu Choice)
    {
        switch (Choice)
        {

        case enManageUsersMenu::eListUsers:
            system("clear");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenu::eAddNewUser:
            system("clear");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenu::eDeleteUser:
            system("clear");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenu::eUpdateUser:
            system("clear");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenu::eFindUser:
            system("clear");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenu::eMainMenue:
        {
            break;
        }
        }
    }

public:
    static void ShowManageUsersScreen()
    {
        system("clear");
        _DrawScreenHeader("Manage User Screen");
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        cout << setw(37) << left << "" << "======================================================" << endl;
        cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
        cout << setw(37) << left << "" << "======================================================" << endl;
        cout << setw(37) << left << "" << "\t [1]List Users" << endl;
        cout << setw(37) << left << "" << "\t [2]Add New User" << endl;
        cout << setw(37) << left << "" << "\t [3]Delete User" << endl;
        cout << setw(37) << left << "" << "\t [4]Update User" << endl;
        cout << setw(37) << left << "" << "\t [5]Find User" << endl;
        cout << setw(37) << left << "" << "\t [6]Main Menue" << endl;

        _PerformManageUsersMenueOption((enManageUsersMenu)_ReadManageUsersMenueOption());
    }
};