#include <iostream>
#include "clsScreen.h"
#include "../clsUser.h"
#include "../clsBankClientTest.h"
#include <iomanip>
using namespace std;
class clsTransferLog : public clsScreen
{
private:
	static void _PrintTransferLogRecord(clsBankClient::stTransferLog TrasnferRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << TrasnferRecord.Date;
		cout << "| " << setw(30) << left << TrasnferRecord.SourceAccountNumber;
		cout << "| " << setw(30) << left << TrasnferRecord.DestinationAccountNumber;
		cout << "| " << setw(10) << left << TrasnferRecord.Amount;
		cout << "| " << setw(15) << left << TrasnferRecord.SourceBalance;
		cout << "| " << setw(20) << left << TrasnferRecord.DestinationBalance;
		cout << "| " << setw(20) << left << TrasnferRecord.UserName;
	}

public:
	static void ShowTransferLogScreen()
	{

		vector<clsBankClient::stTransferLog> vTransferLogs = clsBankClient::GetTransferLog();

		_DrawScreenHeader("Transfer Log Screen");

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n"
				 << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date";
		cout << "| " << left << setw(30) << "Source Account Number";
		cout << "| " << left << setw(30) << "Destination AccountNumber";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(15) << "SourceBalance";
		cout << "| " << left << setw(20) << "DestinationBalance";
		cout << "| " << left << setw(20) << "Username";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n"
				 << endl;

		if (vTransferLogs.size() == 0)
			cout << "\t\t\t\tNo Transfers Registered In the System!";

		else

			for (clsBankClient::stTransferLog &C : vTransferLogs)
			{

				_PrintTransferLogRecord(C);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n"
				 << endl;
	}
};