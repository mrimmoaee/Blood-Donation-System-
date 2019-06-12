#include <iostream>
#include <iomanip>
#include <fstream>
#include "stdafx.h"
#include <string>
#include "User.h"




using namespace std;

class Hospital : public User
{
public:

	char hospital_name[20];
	char password[15];
	char bloodgroup[20];
	int unit;
	string status;
	

	void create_account();
	void show_account();
	void show_bloodrequest();
	void blood_request();


};


void Hospital::create_account()
{
	cout << "\n=======================|| ENTER HOSPITAL INFORMATION ||=======================" << endl;

	cout << "\n\nEnter the hospital name : ";
	cin >> hospital_name;
	cout << "\n\nEnter the password : ";
	cin >> password;
	
}



void Hospital::show_account()
{
	cout << setw(10) << hospital_name << setw(16) << password << "\n";

}

void Hospital::show_bloodrequest()
{
	cout << setw(15) << hospital_name << setw(23) << bloodgroup << setw(23) << unit << "\n";
}

void Hospital::blood_request()
{
	cout << "\n=======================|| Fill Up Blood Request Form ||=======================" << endl;
	cout << "\n\nEnter the Blood Group name : ";
	cin >> bloodgroup;
	cout << "\n\nEnter Unit : ";
	cin >> unit;

	cout << "\n\n\n Your Request Submitted.";
}
