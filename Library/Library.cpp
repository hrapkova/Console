// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "..\Library\Library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <tchar.h>


//// This is an example of an exported variable
//LIBRARY_API int nLibrary=0;
//
//// This is an example of an exported function.
//LIBRARY_API int fnLibrary(void)
//{
//    return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see Library.h for the class definition
//CLibrary::CLibrary()
//{
//    return;
//}

LIBRARY_API std::string Hlavicka(int pocet, std::istream& input)
{
	std::string vystup, tmp;
	int count = 0;

	while (getline(input, tmp))
	{
		if (count != pocet)
		{
			vystup = vystup + tmp + "\n";
			++count;
		}
	}
	if (pocet > count)
	{
		std::cout << "Vstup nema potrebny pocet riadkov." << std::endl;
		return "error";
	}

	return vystup;
}

LIBRARY_API std::string Hlavicka(int pocet, std::istream& input, char option)
{
	int count = 0;
	char znak;
	std::string vystup;

	while (input.get(znak))
	{
		if (count != pocet)
		{
			vystup = vystup + znak;
			++count;
		}
	}
	if (pocet > count)
	{
		std::cout << "Vstup nema potrebny pocet znakov." << std::endl;
		return "error";
	}

	return vystup;
}