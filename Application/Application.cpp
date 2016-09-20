// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "..\Library\Library.h"
#include <iostream>

void DisplayUsage( char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help" << std::endl;
	std::cout << "\t-t \"text na vypis\" - vypis textu definovaneho parametrom" << std::endl;
}

void Hlavicka(char *pole)
{
	char option;

	switch (option)
	{
		case 'n':
			// -n vypisuje riadky
			break;
		case 'c':
			// -c vypisuje znaky
			break;
	}

	return;
}

int main(int argc, char **argv)
{
	int c=0;

	if (argc == 1)
	{
		DisplayUsage(argv[0]);
	}
	else
	{
		while ((c = getopt(argc, argv, "ht:" )) != EOF)
		{
			switch (c)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 't':
				std::cout << "Text: " << optarg << std::endl;
				Hlavicka(argv[0]);
				break;
			case '?':
				std::wcout << "Chybny parameter '" << argv[optind - 1] << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			}
		}
	}

	std::cout << "Hello world!";

    return 0;
}

