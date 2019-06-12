#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "stdafx.h"
#include <string>

using namespace std;

class Blooddonationcamp
{
public:
	char camp_name[20];
	char location[10];

	void create_account();
	void show_account();
};


void Blooddonationcamp::create_account()
{
	cout << "\n=======================|| ENTER BLOOD DONATION CAMP INFORMATION ||=======================" << endl;

	cout << "\n\nEnter the Camp Name : ";
	cin >> camp_name;
	cout << "\n\nEnter the name of the location : ";
	cin >> location;
	cout << "\n\nNew Blood Donation Added : ";

	
}

void Blooddonationcamp::show_account()
{
	cout << setw(10) << camp_name << setw(16) << location << setw(18) << "\n";
}