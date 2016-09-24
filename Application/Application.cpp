// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "..\Library\Library.h"
#include <iostream>
#include <fstream>
#include <string>

void DisplayUsage( char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help" << std::endl;
	std::cout << "\t-c - vypis daneho poct znakov" << std::endl;
	std::cout << "\t-n - vypis daneho poct riadkov" << std::endl;
	std::cout << "\t-f \"cesta ku suboru\" - cesta ku vstupnemu textovemu suboru" << std::endl;
}

void Hlavicka(char **argv, int pocet, char *file)
{
	
	int tmp = 0;
	std::string line;
	std::fstream subor(file, std::fstream::in);

	//Kontrola suboru
	if (!subor.is_open())
	{
		std::cout << "Chyba textoveho suboru." << std::endl;
		return;
	}

	//Zistenie poctu vsetkych riadkov v subore a navrat na zaciatok suboru
	while (!subor.eof())
	{
		getline(subor,line);
		++tmp;
	}
	subor.clear();
	subor.seekg(0, std::fstream::beg);

	//Vypis pozadovanych riadkov
	if (pocet < 0 && -pocet <= tmp)
		for (int i = 0; i < tmp + pocet; ++i)
		{
			getline(subor, line);
			std::cout << line << std::endl;
		}
	if (pocet > 0 && pocet <= tmp)
		for (int i = 0; i < pocet; ++i)
		{
			getline(subor, line);
			std::cout << line << std::endl;
		}
	if ((pocet < 0 && -pocet > tmp) || (pocet > 0 && pocet > tmp))
		std::cout << "Subor nema potrebny pocet riadkov." << std::endl;
	subor.close();

	return;
}

void Hlavicka(char **argv, int pocet, char *file, char option)
{
	int tmp = 0;
	char znak;

	std::fstream subor(file, std::fstream::in);
	//Kontrola otvorenia suboru
	if (!subor.is_open())
	{
		std::cout << "Chyba textoveho suboru." << std::endl;
		return;
	}

	//Zistenie poctu vsetkych znakov v subore a navrat na zaciatok suboru
	while (!subor.eof())
	{
		subor.get(znak);
		++tmp;
	}
	subor.clear();
	subor.seekg(0, std::fstream::beg);

	//Vypis pozadovanych znakov
	if (pocet < 0 && -pocet <= tmp)
		for (int i = 0; i < tmp + pocet; ++i)
		{
			subor.get(znak);
			putchar(znak);
		}
	if (pocet > 0 && pocet <= tmp)
		for (int i = 0; i < pocet; ++i)
		{
			subor.get(znak);
			putchar(znak);
		}
	if ((pocet < 0 && -pocet > tmp) || (pocet > 0 && pocet > tmp))
		std::cout << "Subor nema potrebny pocet znakov." << std::endl;
	subor.close();

	return;
}

int main(int argc, char **argv)
{
	int x=0, index = 0;

	if (argc == 1)
	{
		DisplayUsage(argv[0]);
	}
	if (argc < 5)
	{
		std::cout << "Nespravny vstup." << std::endl;
		DisplayUsage(argv[0]);
	}
	if(argc>=5)
	{
		while ((x = getopt(argc, argv, "hc:n:f:")) != EOF)
		{
			switch (x)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 'f':
				index = optind;
				//Aby sa dalo vypisovat aj z viacerych vstupnych suborov
				while (index != 2)
				{
					if (std::string(argv[index - 2]) == "-c")
					{
						Hlavicka(argv, atoi(argv[index - 1]), argv[index + 1], 'c');
						std::cout << std::endl;
						break;
					}
					if (std::string(argv[index - 2]) == "-n")
					{
						Hlavicka(argv, atoi(argv[index - 1]), argv[index + 1]);
						std::cout << std::endl;
						break;
					}
					else
						--index;
				}
				if (index == 2)
				{
					std::cout << "Nebol zadany prepinac -n/-c." << std::endl;
				}
				break;
			case 'c':
				//Kontrola ci je argument + alebo - cislo
				if (optarg[0] == '-' && !isdigit(optarg[1]))
				{
					std::cout << "Chybny argument." << std::endl;
					return -1;
				}
				if (optarg[0] != '-' && !isdigit(optarg[0]))
				{
					std::cout << "Chybny argument." << std::endl;
					return -1;
				}
				//Kontrola ci bol zadany vstupny subor k prepinacu
				if ("-f" != std::string(argv[optind]))
				{
					std::cout << "Nezadany vstupny subor!" << std::endl;
					return -1;
				}
				//Funkcia na vypis znakov
				Hlavicka(argv, atoi(optarg), argv[optind + 1], 'c');
				std::cout << std::endl;
				optind = optind + 2;
				break;
			case 'n':
				//Kontrola ci je argument + alebo - cislo
				if (optarg[0]=='-' && !isdigit(optarg[1]))
				{
					std::cout << "Chybny argument." << std::endl;
					return -1;
				}
				if (optarg[0] != '-' && !isdigit(optarg[0]))
				{
					std::cout << "Chybny argument." << std::endl;
					return -1;
				}
				//Kontrola ci bol zadany vstupny subor k prepinacu
				if ("-f" != std::string(argv[optind]))
				{
					std::cout << "Nezadany vstupny subor!" << std::endl;
					return -1;
				}
				//Funkcia na vypis riadkov
				Hlavicka(argv, atoi(optarg), argv[optind + 1]);
				std::cout << std::endl;
				optind = optind + 2;
				break;
			case '?':
				std::wcout << "Chybny parameter '" << argv[optind - 1] << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			default:
				std::wcout << "Neznamy parameter '" << (char)x << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			}
		}
	}

     return 0;
}