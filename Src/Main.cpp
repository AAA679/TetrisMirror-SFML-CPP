#include <Application.h>
#include <stdexcept>
#include <iostream>
#include <Windows.h>

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
