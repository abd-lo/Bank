#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "../Global.h"

using namespace std;

class clsLoginScreen : public clsScreen
{

    static bool _Login()
    {
        string Username, Password;
        bool LoginFailed = 1;
        short NumberOfTries = 0;
        while (LoginFailed)
        {
            cout << "_________________________" << endl;

            cout << "Enter your Username" << endl;
            cin >> Username;
            cout << "Enter your Password" << endl;
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            if (CurrentUser.IsEmpty())
            {

                cout << "\nInvalid Username or Password\n\n";
                NumberOfTries += 1;
                cout << 3 - NumberOfTries << "~~Tials left\n\n";

                if (NumberOfTries == 3)
                    return 0;
            }

            LoginFailed = CurrentUser.IsEmpty();
        }

        CurrentUser.RegisterLogin();

        clsMainScreen::ShowMainMenue();
    }

public:
    static bool ShowLoginScreen()
    {
        system("clear");
        _DrawScreenHeader("Login Screen\n");
        return _Login();
    }
};