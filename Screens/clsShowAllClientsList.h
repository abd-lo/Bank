#include <iostream>
#include "../clsBankClientTest.h"
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"
#include "../Libraries/clsPerson.h"
#include "../Libraries/clsUtil.h"
// #include <stdlib.h>
using namespace std;
class clsShowAllClientsList : protected clsScreen
{
private:
	static void PrintClientRecordLine(clsBankClient Client)
	{

		cout << "| " << setw(15) << left << Client.GetAccountNumber();
		cout << "| " << setw(20) << left << Client.GetFullName();
		cout << "| " << setw(12) << left << Client.GetPhone();
		cout << "| " << setw(20) << left << Client.GetEmail();
		cout << "| " << setw(10) << left << Client.GetPinCode();
		cout << "| " << setw(12) << left << Client.GetAccountBalance();
	}

public:
	static void ShowAllClients()
	{

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		_DrawScreenHeader("ShowClients List");
		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}
		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n"
				 << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n"
				 << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";

		else

			for (clsBankClient &Client : vClients)
			{

				PrintClientRecordLine(Client);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n"
				 << endl;
	}
};