#pragma once
#include <iostream>
#include <string>
#include "Libraries/clsPerson.h"
#include "Libraries/clsString.h"
#include "Libraries/clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson

{
public:
	struct stTransferLog
	{
		string Date;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double SourceBalance;
		double DestinationBalance;
		string UserName;
	};

private:
	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1,
		NewClient = 2
	};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = 0;

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{

		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read Mode

		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static clsBankClient _ConvertLineToClientObject(string Line)
	{
		vector<string> vClients;
		vClients = clsString::Split(Line, "#//#");
		return clsBankClient(enMode::UpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4], vClients[5], stod(vClients[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string sClient;
		sClient += Client.GetFirstName() + Seperator;
		sClient += Client.GetLastName() + Seperator;
		sClient += Client.GetEmail() + Seperator;
		sClient += Client.GetPhone() + Seperator;
		sClient += Client.GetAccountNumber() + Seperator;
		sClient += Client.GetPinCode() + Seperator;
		sClient += to_string(Client.GetAccountBalance()) + Seperator;
		return sClient;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		string ClientRecord = "";

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{

			for (clsBankClient &C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					ClientRecord = _ConvertClientObjectToLine(C);
					MyFile << ClientRecord << endl;
				}
			}

			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update()
	{

		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient &i : _vClients)
		{

			if (i._AccountNumber == GetAccountNumber())

				i = *this;

			break;
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
		}

		MyFile.close();
	}
	// Transfer
	string _PrepareTransferLogRecord(double Amount, clsBankClient ClientDestination)
	{
		string Line = "", Seperator = "#//#";
		Line = clsDate::GetCurrentTimeWithM_S() + Seperator;
		Line += _AccountNumber + Seperator;
		Line += ClientDestination._AccountNumber + Seperator;
		Line += to_string(Amount) + Seperator;
		Line += to_string(_AccountBalance) + Seperator;
		Line += to_string(ClientDestination._AccountBalance) + Seperator;
		Line += CurrentUser.GetUserName();
		return Line;
	}

	void _RegitserTransferLog(double Amount, clsBankClient ClientDestination)
	{
		fstream MyFile;
		string RecordLine = _PrepareTransferLogRecord(Amount, ClientDestination);

		MyFile.open("TransfersLog.txt", ios::out || ios::app);
		if (MyFile.is_open())
		{
			MyFile << RecordLine << endl;
			MyFile.close();
		}
	}

	static stTransferLog _GetTransferLogRecord(string Line)
	{
		stTransferLog TransferLogRecord;
		vector<string> vRecord;
		vRecord = clsString::Split(Line, "#//#");

		TransferLogRecord.Date = vRecord[0];
		TransferLogRecord.SourceAccountNumber = vRecord[1];
		TransferLogRecord.DestinationAccountNumber = vRecord[2];
		TransferLogRecord.Amount = stod(vRecord[3]);
		TransferLogRecord.SourceBalance = stod(vRecord[4]);
		TransferLogRecord.DestinationBalance = stod(vRecord[5]);
		TransferLogRecord.UserName = vRecord[6];

		return TransferLogRecord;
	}

	static vector<stTransferLog> _LoadTransferLogList()
	{
		stTransferLog TransferLog;
		string Line;
		vector<stTransferLog> vTransferLog;
		fstream MyFile;

		MyFile.open("TransfersLog.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				TransferLog = _GetTransferLogRecord(Line);
				vTransferLog.push_back(TransferLog);
			}
			MyFile.close();
		}
		return vTransferLog;
	}

	void Encrypt(string Test)
	{
		for (int i = 0; i == Test.size(); i++)
		{
			Test[i] = char(Test[i] + 1);
		}
	}

	//-----public-------

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
								string PinCode, float AccountBalance)
			: clsPerson(FirstName, LastName, Email, Phone)
	{
		{
			_Mode = Mode;
			_AccountNumber = AccountNumber;
			_PinCode = PinCode;
			_AccountBalance = AccountBalance;
		}
	}
	// Get
	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	// Set
	void SetAccountNumber(string AccountNumber)
	{
		_AccountNumber = AccountNumber;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	// find
	static clsBankClient Find(string AccountNumber)
	{
		string ClientLine;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, ClientLine))
			{
				clsBankClient Client = _ConvertLineToClientObject(ClientLine);

				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
			return _GetEmptyClientObject();
		}
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		string ClientLine;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, ClientLine))
			{
				clsBankClient Client = _ConvertLineToClientObject(ClientLine);

				if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}

				MyFile.close();
				return _GetEmptyClientObject();
			}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResults
	{
		enSaveFailed = 0,
		enSaveSucceed = 1,
		enClientExist = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
			{

				return enSaveResults::enSaveFailed;
			}
			break;

		case enMode::UpdateMode:

			_Update();
			return enSaveResults::enSaveSucceed;
			break;

		case enMode::NewClient:

			if (IsClientExist(_AccountNumber))

				return enSaveResults::enClientExist;

			_AddDataLineToFile(_ConvertClientObjectToLine(*this));

			return enSaveResults::enSaveSucceed;

			break;

		default:
			break;
		}
	}

	// NewClient

	clsBankClient static GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::NewClient, "", "", "", "", AccountNumber, "", 0);
	}

	bool DeleteClient()
	{

		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient &C : vClients)
		{
			if (C._AccountNumber == _AccountNumber)
				C._MarkForDelete = 1;

			break;
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return 1;
	}

	// list client
	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();
		double TotalBalances = 0;

		for (auto &&C : vClients)
		{
			TotalBalances += C.GetAccountBalance();
		}
		return TotalBalances;
	}

	void Deposit(double amount)
	{

		_AccountBalance += amount;
		Save();
	}

	bool WithDraw(double amount)
	{
		if (amount > _AccountBalance)
			return 0;
		else
		{
			_AccountBalance -= amount;
			Save();
			return 1;
		}
	}

	bool Transfer(double Amount, clsBankClient &ClientDestination)
	{
		ClientDestination.Deposit(Amount);
		bool Result = WithDraw(Amount);

		if (Result == 1)
			_RegitserTransferLog(Amount, ClientDestination);

		return Result;
	}

	static vector<stTransferLog> GetTransferLog()
	{
		return _LoadTransferLogList();
	}
};