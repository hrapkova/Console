// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Library.h"
#include <iostream>
#include <string>
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

LIBRARY_API void Hlavicka(char **argv, int pocet, std::istream& subor)
{

	int tmp = 0;
	std::string line;

	//Vypis pozadovanych riadkov
	if (pocet > 0 && pocet <= tmp)
		for (int i = 0; i < pocet; ++i)
		{
			getline(subor, line);
			std::cout << line << std::endl;
		}
	if (pocet > 0 && pocet > tmp)
		std::cout << "Vstup nema potrebny pocet riadkov." << std::endl;

	return;
}

LIBRARY_API void Hlavicka(char **argv, int pocet, std::istream& subor, char option)
{
	int tmp = 0;
	char znak;

	//Vypis pozadovanych znakov
	if (pocet > 0 && pocet <= tmp)
		for (int i = 0; i < pocet; ++i)
		{
			subor.get(znak);
			putchar(znak);
		}
	if (pocet > 0 && pocet > tmp)
		std::cout << "Vstup nema potrebny pocet znakov." << std::endl;

	return;
}