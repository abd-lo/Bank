#include <iostream>
#include "clsScreen.h"
#include "../clsUser.h"
#include <iomanip>
using namespace std;
class clsShowRegisterLoginScreen : public clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser::stRegisterLogin stLogin)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << stLogin.Date;
		cout << "| " << setw(20) << left << stLogin.UserName;
		cout << "| " << setw(20) << left << stLogin.Password;
		cout << "| " << setw(12) << left << stLogin.Permissions;
	}

public:
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pRegisterLogin))
		{
			return;
		}
		vector<clsUser::stRegisterLogin> vLogin = clsUser::GetRegisterLoginList();

		_DrawScreenHeader("Login Register Screen");

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n"
				 << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n"
				 << endl;

		if (vLogin.size() == 0)
			cout << "\t\t\t\tNo Logins Registered In the System!";

		else

			for (clsUser::stRegisterLogin &C : vLogin)
			{

				_PrintUserRecordLine(C);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n"
				 << endl;
	}
};