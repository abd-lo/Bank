#pragma once
#include <iostream>
#include <string.h>
#include "Libraries/clsPerson.h"
#include "Libraries/clsString.h"
#include "Libraries/clsUtil.h"
#include "Libraries/clsDate.h"
#include <vector>
#include <fstream>
using namespace std;

class clsUser : public clsPerson
{
public:
	struct stRegisterLogin
	{
		string Date;
		string UserName;
		string Password;
		int Permissions;
	};

private:
	enum enMode
	{
		eEmpty = 1,
		eUpdate = 2,
		eAddNew = 3
	};

	enMode _Mode;
	string _Password;
	string _UserName;
	int _Permissions;
	bool _MarkToDelete = 0;

	// Register Login
	string _PrepareLoginRecord(string Seperator = "#//#")
	{
		string Line = "";

		Line = clsDate::GetCurrentTimeWithM_S() + Seperator;
		Line += GetUserName() + Seperator;
		Line += clsUtil::Encrypt(GetPassword()) + Seperator;
		Line += to_string(GetPermissions());

		return Line;
	}

	static stRegisterLogin _ConvertLoginRegisterLineToRecord(string Line)
	{
		stRegisterLogin sData;
		vector<string> vLogin;

		vLogin = clsString::Split(Line, "#//#");

		sData.Date = vLogin[0];
		sData.UserName = vLogin[1];
		sData.Password = clsUtil::Decrypt(vLogin[2]);
		sData.Permissions = stoi(vLogin[3]);
		return sData;
	}

	void _LoadRegisterdLoginsFromFile(string Seperator = "#//#")
	{
		vector<stRegisterLogin> vLogins;
		stRegisterLogin RegisterData;
		string Line = "";
		fstream MyFile;

		MyFile.open("Login.txt", ios ::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				RegisterData = _ConvertLoginRegisterLineToRecord(Line);
				vLogins.push_back(RegisterData);
			}
		}
		MyFile.close();
	}

	static string _ConvertUserRecordToLine(clsUser User, string Seperator = "#//#")
	{

		string Line = "";
		Line = User.GetFirstName() + Seperator;
		Line += User.GetLastName() + Seperator;
		Line += User.GetEmail() + Seperator;
		Line += User.GetPhone() + Seperator;
		Line += User.GetUserName() + Seperator;
		Line += clsUtil::Encrypt(User.GetPassword()) + Seperator;
		Line += to_string(User.GetPermissions());
		return Line;
	}

	static clsUser _ConvertLineToUserObejct(string Line)
	{

		vector<string> vUsers;
		vUsers = clsString::Split(Line, "#//#");
		return clsUser(enMode::eUpdate, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4], clsUtil::Decrypt(vUsers[5]), stoi(vUsers[6]));
	}

	static vector<clsUser> _LoadUsersListFormFile()
	{
		vector<clsUser> vUsers;
		fstream MyFile;
		string Line;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObejct(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}
		return vUsers;
	}

	void _SaveDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		string Line;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser &i : vUsers)
			{
				if (!i._MarkToDelete)
				{
					Line = _ConvertUserRecordToLine(i);
					MyFile << Line;
					if (i._UserName != vUsers.back()._UserName)
						MyFile << endl;
				}
			}
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::eEmpty, "", "", "", "", "", "", 0);
	}

	void _Update()
	{

		vector<clsUser> _vUsers = _LoadUsersListFormFile();

		for (auto &&i : _vUsers)
		{
			if (i._UserName == _UserName)
			{
				i = *this;
				break;
			}
		}
		_SaveDataToFile(_vUsers);
	}

	void _AddNewUser()
	{
		_AddNewLineToFile(_ConvertUserRecordToLine(*this));
	}

	void _AddNewLineToFile(string NewLineData)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << NewLineData << endl;

			MyFile.close();
		}
	}
	//--------------------public-------------------------------
public:
	enum enSaveResults
	{
		enSaveFailedEmptyObject = 0,
		enSaveSucceed = 1,
		enSaveFailedUserExist = 2
	};
	enum enPermissions
	{
		pAll = -1,
		pListClients = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClients = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pRegisterLogin = 128,
	};
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string UserName, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	// Get And Set
	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetPassword()
	{
		return _Password;
	}
	void SetPassword(string Password)
	{
		_Password = Password;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	/////
	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;
		string Line;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObejct(Line);

				if (User._UserName == Username && User._Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username)
	{
		fstream MyFile;
		string Line;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObejct(Line);

				if (User._UserName == Username)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::eEmpty);
	}
	// get empty object with new user mode
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::eAddNew, "", "", "", "", UserName, "", 0);
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);
		return (!User.IsEmpty());
	}

	bool MarkedForDelete()
	{
		return _MarkToDelete;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersListFormFile();
	}

	bool Delete()
	{
		vector<clsUser> _vUsers;
		_vUsers = _LoadUsersListFormFile();

		for (clsUser &i : _vUsers)
		{
			if (i._UserName == _UserName)
			{
				i._MarkToDelete = 1;
				break;
			}
		}
		_SaveDataToFile(_vUsers);
		*this = _GetEmptyUserObject();
		return 1;
	}

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::eEmpty:
		{

			return enSaveResults::enSaveFailedEmptyObject;
		}

		case enMode::eUpdate:
		{

			_Update();
			return enSaveResults::enSaveSucceed;
		}

		case enMode::eAddNew:

			if (clsUser::IsUserExist(_UserName))
			{

				return enSaveResults::enSaveFailedUserExist;
			}

			else
			{

				_AddNewUser();

				_Mode = enMode::eUpdate;
				return enSaveResults::enSaveSucceed;
			}
		}
	}

	bool CheckAccessPermission(enPermissions ScreenPermissions)
	{
		if (this->_Permissions == enPermissions::pAll)
		{
			return 1;
		}

		if ((this->_Permissions & ScreenPermissions) == ScreenPermissions)
		{
			return 1;
		}
		else
			return 0;
	}

	void RegisterLogin()
	{
		fstream MyFile;

		MyFile.open("Login.txt", ios ::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << _PrepareLoginRecord();
			MyFile << endl;
		}
		MyFile.close();
	}

	static vector<stRegisterLogin> GetRegisterLoginList()
	{
		vector<stRegisterLogin> vLogin;
		fstream MyFile;
		stRegisterLogin sLogin;
		string Line;
		MyFile.open("Login.txt", ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				sLogin = _ConvertLoginRegisterLineToRecord(Line);
				vLogin.push_back(sLogin);
			}
		}
		MyFile.close();
		return vLogin;
	}
};