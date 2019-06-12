#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "stdafx.h"
#include <string>

using namespace std;

class BloodDonar
{
public:
	char name[50];
	char password[15];




	void create_account(); //function to get data from user
	void show_account();   //function to show data on screen


};

void BloodDonar::create_account()
{
	cout << "\n=======================|| ENTER BLOOD DONAR INFORMATION ||=======================" << endl;

	cout << "\n\nEnter the username : ";
	cin >> name;
	cout << "\n\nEnter the password : ";
	cin >> password;

}

void BloodDonar::show_account()
{
	cout << setw(10) << name << setw(16) << password << "\n";

}


