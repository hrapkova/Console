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

std::string Hlavicka(char **argv, int pocet, std::istream& input)
{
	std::string vystup, tmp;
	int count = 0;

	while (getline(input, tmp))
	{
		if(count!=pocet)
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

std::string Hlavicka(char **argv, int pocet, std::istream& input, char option)
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

int main(int argc, char **argv)
{
	int x=0, index = 0;

	if (argc == 1)
	{
		DisplayUsage(argv[0]);
	}
	if(argc>=2)
	{
		while ((x = getopt(argc, argv, "hc:n:f:")) != EOF)
		{
			switch (x)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 'f':
				{
					std::fstream subor(optarg, std::fstream::in);
					if (!subor.is_open())
					{
						std::cout << "Chyba textoveho suboru." << std::endl;
						return -1;
					}
					//Aby sa dalo vypisovat aj z viacerych vstupnych suborov
					index = optind;
					while (index != 2)
					{
						if (std::string(argv[index - 2]) == "-c")
						{
							std::cout << Hlavicka(argv, atoi(argv[index - 1]), subor, 'c');
							break;
						}
						if (std::string(argv[index - 2]) == "-n")
						{
							std::cout << Hlavicka(argv, atoi(argv[index - 1]), subor);
							break;
						}
						else
							--index;
					}
					subor.close();
					if (index == 2)
					{
						std::cout << "Nebol zadany prepinac -n/-c." << std::endl;
					}
					break;
				}
			case 'c':
				{
					//Kontrola ci je argument + cislo
					if (optarg[0] != '-' && !isdigit(optarg[0]))
					{
						std::cout << "Chybny argument." << std::endl;
						return -1;
					}

					//Kontrola ci bol zadany vstupny subor k prepinacu -> cita z konzoly
					if (argc == 3)
					{
						std::cout << Hlavicka(argv, atoi(optarg), std::cin,'c');
						break;
					}

					//Funkcia na vypis znakov
					std::fstream subor(argv[optind + 1], std::fstream::in);
					//Kontrola suboru
					if (!subor.is_open())
					{
						std::cout << "Chyba textoveho suboru." << std::endl;
						return -1;
					}
					std::cout << Hlavicka(argv, atoi(optarg), subor, 'c');
					subor.close();
					std::cout << std::endl;
					optind = optind + 2;
					break;
				}
			case 'n':
				{
					//Kontrola ci je argument + cislo
					if (optarg[0] != '-' && !isdigit(optarg[0]))
					{
						std::cout << "Chybny argument." << std::endl;
						return -1;
					}

					//Kontrola ci bol zadany vstupny subor k prepinacu
					if (argc==3)
					{
						std::cout << Hlavicka(argv, atoi(optarg), std::cin);
						break;
					}

					//Funkcia na vypis riadkov
					std::fstream subor(argv[optind + 1], std::fstream::in);
					//Kontrola suboru
					if (!subor.is_open())
					{
						std::cout << "Chyba textoveho suboru." << std::endl;
						return -1;
					}
					std::cout << Hlavicka(argv, atoi(optarg), subor);
					subor.close();
					std::cout << std::endl;
					optind = optind + 2;
					break;
				}
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