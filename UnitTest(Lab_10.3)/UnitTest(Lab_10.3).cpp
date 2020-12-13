#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.3/Lab_10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab103
{
	TEST_CLASS(UnitTestLab103)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int kil_towar = 3;
			towar* s = new towar[kil_towar + 100];

			s[0].n_towar = "asdas";
			s[0].vartіst = 300;
			s[0].kilkist = 230;
			s[0].units = (measurement)2;
			s[0].masa = 12;

			s[1].n_towar = "aqqqs";
			s[1].vartіst = 220;
			s[1].kilkist = 180;
			s[1].units = (measurement)3;
			s[1].masa = 12;

			s[2].n_towar = "dwwwas";
			s[2].vartіst = 30;
			s[2].kilkist = 20;
			s[2].units = (measurement)1;
			s[2].masa = 2;

			SortTXT("E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_10.3\\Lab_10.3\\test1.1.txt", "E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_10.3\\Lab_10.3\\test.txt", kil_towar, s);
			Print_towar(s, kil_towar, 0, "E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_10.3\\Lab_10.3\\test.txt");

			Assert::AreEqual(s[0].vartіst, 30);
		}
	};
}
