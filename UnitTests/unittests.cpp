#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Library/Library.h"

#include <vector>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_XGetOpt_fail)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-a", "-c", "-e", "param E", "--fail" };
			char * opts = "ab:cde:";

			Assert::IsTrue( getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual( argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'a', L"option -a");
			Assert::IsTrue(optarg == nullptr, L"option param -a");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'c', L"option -c");
			Assert::IsTrue(optarg == nullptr, L"option param -c");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[6], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == '?', L"option --fail");
			Assert::IsTrue( optind == 8, L"--fail index");
		}

		TEST_METHOD(Test_XGetOpt_param)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-e", "param E", "param 1", "param 2" };
			char * opts = "ab:cde:";

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual(argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[4], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == EOF, L"last option");
			Assert::IsTrue(optind == 5, L"first param index");
		}

		TEST_METHOD(Test_X)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv1 = { "Application.exe", "-c", "2", "-f", "C:\\Users\\Lenka\\Desktop\\Škola\\4.roèník\\TSS\\zadanie1.txt" };
			std::vector<char *> argv2 = { "Application.exe", "-n", "1", "-f", "C:\\Users\\Lenka\\Desktop\\Škola\\4.roèník\\TSS\\zadanie1.txt" };
			std::vector<char *> argv5 = { "Application.exe", "-n", "2", "toto je nejaky string\nstring cislo2\nposledny string"};
			char * opts = "c:n:f:";
			//kvoli newlinom
			std::string str(argv5[3]);
			size_t pos = 0;
			while ((pos = str.find("\\n", pos)) != std::string::npos)
			{
				str.replace(pos, 2, "\n");
				pos += 2;
			};

			//**************************************************************************************************

			//Kontrola vypisu znakov

			//kontrola pri citani zo suboru
			std::fstream subor;
			subor.open(argv1[4], std::fstream::in);
			Assert::AreEqual(Hlavicka(atoi(argv1[2]), subor, 'c'),std::string("Pr"), L"option -c");
			subor.close();

			//kontrola pri citani stringu
			std::istringstream xxx(str);
			Assert::AreEqual(Hlavicka(atoi(argv5[2]), xxx, 'c'), std::string("to"), L"option -c");

			//********************************************************************************************

			//Kontrola vypisu riadkov

			//kontrola pri citani zo suboru
			subor.open(argv1[4], std::fstream::in);
			Assert::AreEqual(Hlavicka(atoi(argv2[2]), subor), std::string("Prvý riadok!\n"), L"option -n");
			subor.close();

			//kontrola pri citani zo stringu
			std::istringstream xx(str);
			Assert::AreEqual(Hlavicka(atoi(argv5[2]), xx), std::string("toto je nejaky string\nstring cislo2\n"), L"option -n");
		}
	};
}