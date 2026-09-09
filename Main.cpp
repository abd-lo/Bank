#include <iostream>
#include "Screens/clsMainScreen.h"
#include "Screens/clsLoginScreen.h"

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}
}
