#include <iostream>
#include <iomanip>
#include <fstream>
#include "stdafx.h"
#include <string>


using namespace std;

class BloodStock
{
public:
	char Bloodname[10];
	int stock;

	void blood_account();
	void show_account();

};

void BloodStock::blood_account()
{
	cout << "\n=======================|| ENTER BLOOD GROUP INFORMATION ||=======================" << endl;

	cout << "\n\nEnter the name of blood group : ";
	cin >> Bloodname;
	cout << "\n\nEnter the number of stock : ";
	cin >> stock;
	cout << "\n\n\n New Blood Stock Added :";
}

void BloodStock::show_account()
{

	cout << setw(10) << Bloodname << setw(19) << stock << "\n";

}






