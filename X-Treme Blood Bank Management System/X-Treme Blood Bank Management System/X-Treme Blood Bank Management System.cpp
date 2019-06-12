// X-Treme Blood Bank Management System.cpp : main project file.

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include<conio.h>
#include "Hospital.h"
#include "BloodStock.h"

#include "Blooddonationcamp.h"
#include "BloodDonar.h"


void intro(); // introduction of the system
void Login_menu(); // first menu of the system
void Update_profile(); // hospital update profile
void Hospital_Menu();  //menu of the hospital
void Admin_Menu();   //menu of the admin
void Donor_Menu();  //menu of the donor



using namespace std;

//=========================================|| Global Object ||====================================
//================================================================================================

Hospital h;  
BloodDonar b;
Blooddonationcamp y;
BloodStock a;


//=========================================|| Global Variable ||====================================
//==================================================================================================

char current_user[10]; // global variable of user that call outside the function
char user[10];
char bloodName[10];


//=====================================|| Request for Blood ||=========================================
//=====================================================================================================

void Blood_request()
{
	cout << "\n\tHospital Name is : " << (current_user, h.hospital_name) << "\n";
	h.blood_request();
	ofstream out("bloodrequest.txt", ios::app); // write the information to the text file
	if (!out) {
		cout << "cannot open the donar.dat file. \n";
	}
	out.write((char*)&h, sizeof(Hospital));//casts the address of the float variable to a pointer of type char.


}


//=====================================|| View Blood Request Result (Hospital) ||==============================
//=============================================================================================================

void View_bloodrequest()
{
	ifstream in("bloodrequest.txt");
	if (!in)
	{
		cout << "File not Found";
	}

	cout << "\n\t\t\t                          *Hospital Blood Request List*  \n\n";
	cout << "\n\t|Hospital Name|" << setw(25) << "|Blood Group|" << setw(16) << "|Unit|\n";
	cout << "\t****************************************************\n";
	while (in.read((char*)&h, sizeof(Hospital)))
	{
		if (strcmp(h.hospital_name, current_user) == 0)
		{
			h.show_bloodrequest();
			
		}
	}
	in.close();

}
//=============================================|| All Blood Donation Request (Donor) ||==========================================
//===============================================================================================================================

void BloodDonation_request()
{
	char n[3];
	char k[10];
	char c;
	int flag = 0;
	fstream f1;
	fstream f2;
	int m;
	fstream fp, f;
	int found = 0;
	ifstream in("bloodcamp.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t                          *Blood Donation Camp Information List*  \n\n";
	cout << "|---Camp Name---|" << setw(10) << "|---Location---|\n";
	cout << "----------------------------------------------------------\n";
	while (in.read((char*)&y, sizeof(Blooddonationcamp)))
	{
		y.show_account();

	}

	in.close();

	cout << "\n\n\tDo You Want To Donate Blood (y/n?)";

	cin >> c;
	if (c == 'y' || c == 'Y')
	{
		cout << "\n\n\tEnter the name of Blood Camp: ";
		cin >> k;

		cout << "\n\n\tEnter the name of blood group:";
		cin >> n;
		fp.open("bloodStock.txt", ios::in | ios::out);
		while (fp.read((char*)&a, sizeof(BloodStock)) && found == 0)
		{
			if (strcmp(a.Bloodname, n) == 0)
			{

				cout << "\n\n\tEnter the unit of blood Donation : ";
				cin >> m;
				a.stock = a.stock + m;
				int pos = -1 * sizeof(a);
				fp.seekp(pos, ios::cur);
				fp.write((char*)&a, sizeof(BloodStock));
				found = 1;
				fp.close();
				cout << "\n\n\tRequest Accepted\n";
			}
				
		}

	}
	else {
		Donor_Menu();

	}



	fp.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";
}


//=============================================|| All Blood Request (admin) ||===================================================
//===============================================================================================================================

void All_bloodRequest()
{
	char n[3];
	char k[10];
	char c;
	int flag = 0;
	fstream f1;
	fstream f2;
	int m;
	fstream fp,f;
	int found = 0;
	ifstream in("bloodrequest.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t                          *Hospital Blood Request List*  \n\n";
	cout << "\n\t|Hospital Name|" << setw(25) << "|Blood Group|" << setw(16) << "|Unit|" << "\n";
	cout << "\t**********************************************************\n";
	while (in.read((char*)&h, sizeof(Hospital)))
	{
		h.show_bloodrequest();

	}

	in.close();

		cout << "\n\n\tDo You Want To Accept Blood Request(y/n?)"; 

		cin >> c;
		if (c == 'y' || c == 'Y')
		{
			cout << "\n\n\tEnter the name of hospital:";
			cin >> k;

			cout << "\n\n\tEnter the name of blood group:";
			cin >> n;
			fp.open("bloodStock.txt", ios::in | ios::out);
			while (fp.read((char*)&a, sizeof(BloodStock)) && found == 0)
			{

				if (strcmp(a.Bloodname, n) == 0)
				{
					cout << "\n\t\t\t*Blood Stock Information List*  \n\n";
					cout << "|---Blood Group---|" << setw(10) << "|---Stock Available---| \n";
					cout << "------------------------------------------\n";
					a.show_account();

					if (a.stock == 0)
					{
						cout << "\n\n\t   ********This Blood Group Is Not Available.********\n";
						break;
					}
					else
					{
						cout << "\n\n\tEnter the unit of blood needed : ";
						cin >> m;
						a.stock = a.stock - m;
						int pos = -1 * sizeof(a);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&a, sizeof(BloodStock));
						found = 1;
						fp.close();
						cout << "\n\n\tRequest Accepted\n";

						//deleting the accepting request
						f1.open("bloodrequest.txt", ios::in | ios::out);
						f2.open("temp.txt", ios::out);
						f1.seekg(0, ios::beg);
						while (f1.read((char*)&h, sizeof(Hospital)))
						{
							if (strcmp(h.hospital_name, k)!= 0 )
								f2.write((char*)&h, sizeof(Hospital));
							else
								flag = 1;
						}
						f2.close();
						f1.close();
						remove("bloodrequest.txt");
						rename("temp.txt", "bloodrequest.txt");

					}

				}

			}

		}
		else {
			Admin_Menu();

		}

		
	
	fp.close();
	if (found == 0)
    cout << "\n\n Record Not Found ";

}


//=============================================|| Blood Stock Account ||================================================================
//======================================================================================================================================


void Bloodstock_Account()
{
	a.blood_account();
	ofstream out("bloodstock.txt", ios::app);
	if (!out) {
		cout << "cannot open the bloodstock.dat file. \n";
	}
	out.write((char*)&a, sizeof(BloodStock));

}

//=============================================|| Blood Donar Account ||=================================================
//=======================================================================================================================

void BloodDonar_Account()
{
	b.create_account();
	ofstream out("donar.txt", ios::app);
	if (!out) {
		cout << "cannot open the donar.dat file. \n";
	}
	out.write((char*)&b, sizeof(BloodDonar));
	cout << "\tYour Account Has Been Created";
}

//=============================================|| All Blood stock Record ||======================================================
//===============================================================================================================================

void AllBloodstock()
{
	ifstream in("bloodstock.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t*Blood Stock Information List*  \n\n";
	cout << "|---Blood Group---|" << setw(10) << "|---Stock Available---| \n";
	cout << "------------------------------------------\n";
	while (in.read((char*)&a, sizeof(BloodStock)))
	{
		a.show_account();

	}

	in.close();
}

//=============================================|| All Blood Donar Record ||==============================================================
//=======================================================================================================================================

void Allblooddonarinfo()
{
	ifstream in("donar.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t                                  *Blood Donar Information List*  \n\n";
	cout << "|---Username---|" << setw(10) << "|---Password---|\n";
	cout << "----------------------------------------------------------\n";
	while (in.read((char*)&b, sizeof(BloodDonar)))
	{
		b.show_account();

	}

	in.close();
}

//=============================================|| All Blood Donation Camp Record ||======================================================
//=======================================================================================================================================

void Allbloodinfo()
{
	ifstream in("bloodcamp.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t                          *Blood Donation Camp Information List*  \n\n";
	cout << "|---Camp Name---|" << setw(10) << "|---Location---|\n";
	cout << "----------------------------------------------------------\n";
	while (in.read((char*)&y, sizeof(Blooddonationcamp)))
	{
		y.show_account();

	}

	in.close();
}
//=====================================|| View or Update Donor Profile ||==============================
//=====================================================================================================

void Update_donorprofile()
{
	char ch;
	fstream fp;
	system("cls"); //clear screen
	fp.open("donar.txt", ios::in | ios::out); // open file
	while (fp.read((char*)&b, sizeof(BloodDonar)))
	{
		if (strcmp(b.name,user) == 0)
		{
			do {
				system("cls");
				cout << "\n\t\t\t  *Donor Information List*  \n\n";
				cout << "|---Donor Name---|" << setw(10) << "|---Password---|\n";
				cout << "-----------------------------------------------------\n";
				b.show_account();

				cout << "\n\n\t******************************";
				cout << "\n\tDonor Information Update Menu";
				cout << "\n\t********************************";
				cout << "\n\t1.Update Donor Name";
				cout << "\n\t2.Update Password";
				cout << "\n\t3.Go To Menu\n";
				cout << "\n\tEnter Your Choice: ";
				ch = getchar();

				switch (ch)
				{
				case '1':
				{
					cout << "\n\tUpdate Username : ";
					cin >> b.name;
					int pos = -1 * sizeof(b);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&b, sizeof(BloodDonar));
					cout << "\n\n\t Record Updated";
					fp.close();
					break;
				}

				case '2':
				{
					cout << "\n\tUpdate Password : ";
					cin >> b.password;
					int pos = -1 * sizeof(b);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&b, sizeof(BloodDonar));
					cout << "\n\n\t Record Updated";
					fp.close();
					break;
				}

				case '3':
				{
					system("cls");
					Donor_Menu();
					break;
				}
				}
			} while (ch != '3');

		}
	}

	fp.close();
	Hospital_Menu();
}



//=====================================|| View or Update Hospital Profile ||===========================
//=====================================================================================================

void Update_profile()
{
	char ch;
	fstream fp;
	system("cls"); //clear screen
	fp.open("hospital.txt", ios::in | ios::out); // open file
	while (fp.read((char*)&h, sizeof(Hospital)))
	{
		if (strcmp(h.hospital_name, current_user) == 0)
		{
			do {
				system("cls");
				cout << "\n\t\t\t  *Hospital Information List*  \n\n";
				cout << "|---Hospital Name---|" << setw(10) << "|---Password---|\n";
				cout << "-----------------------------------------------------\n";
				h.show_account();

				cout << "\n\n\t******************************";
				cout << "\n\tHospital Information Update Menu";
				cout << "\n\t********************************";
				cout << "\n\t1.Update Hospital Name";
				cout << "\n\t2.Update Password";
				cout << "\n\t3.Go To Hospital Menu\n";
				cout << "\n\tEnter Your Choice: ";
				ch = getchar();

				switch (ch)
				{
				case '1':
				{
					cout << "\n\tUpdate Username : ";
					cin >> h.hospital_name;
					int pos = -1 * sizeof(h);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&h, sizeof(Hospital));
					cout << "\n\n\t Record Updated";
					fp.close();
					break;
				}

				case '2':
				{
					cout << "\n\tUpdate Password : ";
					cin >> h.password;
					int pos = -1 * sizeof(h);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&h, sizeof(Hospital));
					cout << "\n\n\t Record Updated";
					fp.close();
					break;
				}
				
				case '3':
				{
					system("cls");
					Hospital_Menu();
					break;
				}
				}
			} while (ch != '3');

		}
	}

	fp.close();
	Hospital_Menu();

}
//=============================================|| Update Blood Donation Camp Record ||===================================================
//=======================================================================================================================================
void Update_bloodcamp()
{
	char n[6], ch;
	fstream fp;
	int found = 0;
	system("cls");
	cout << "\n\n\tUpdate Blood Donation Camp Information.... ";
	cout << "\n\n\tEnter the name of the blood donation camp :";
	cin >> n;
	fp.open("bloodcamp.txt", ios::in | ios::out);
	while (fp.read((char*)&y, sizeof(Blooddonationcamp)) && found == 0)
	{
		if (strcmp(y.camp_name, n) == 0)
		{
			do {
				system("cls");
				cout << "\n\t\t\t                          *Blood Donation Camp Information List*  \n\n";
				cout << "|---Camp Name---|" << setw(10) << "|---Location---|\n";
				cout << "----------------------------------------------------------\n";
				y.show_account();

				cout << "\n\n\t******************************";
				cout << "\n\tBlood Donation Camp Information Update Menu";
				cout << "\n\t********************************";
				cout << "\n\t1.Update Camp Name";
				cout << "\n\t2.Update Location";
				cout << "\n\t3.Go To Admin Menu\n";
				cout << "\n\tEnter Your Choice: ";
				ch = getchar();

				switch (ch)
				{
				case '1':
				{
					cout << "\n\tUpdate Camp Name : ";
					cin >> y.camp_name;
					int pos = (-1) * sizeof(y);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&y, sizeof(Blooddonationcamp));
					cout << "\n\n\t Record Updated";
					found = 1;
					fp.close();
					break;
				}

				case '2':
				{
					cout << "\n\tUpdate Location : ";
					cin >> y.location;
					int pos = (-1) * sizeof(y);
					fp.seekp(pos, ios::cur);
					fp.write((char*)&y, sizeof(Blooddonationcamp));
					cout << "\n\n\t Record Updated";
					found = 1;
					fp.close();
					break;
				}

				case '3':
				{
					system("cls");
					Admin_Menu();
					break;
				}
				}
			} while (ch != '3');

		}
	}

	fp.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";
	Admin_Menu();
}

//=============================================|| Hospital Account ||==================================================================
//=====================================================================================================================================

void Hospital_Account()
{
	h.create_account();
	ofstream out("hospital.txt", ios::app);
	if (!out) {
		cout << "cannot open the hospital.dat file. \n";
	}
	out.write((char*)&h, sizeof(Hospital));
	cout << "\tNew Hospital Account Has Been Created";

}
//=============================================|| Blood Donation Camp ||========================================================
//==============================================================================================================================

void Bloodcamp_Account()
{
	y.create_account();
	ofstream out("bloodcamp.txt", ios::app);
	if (!out) {
		cout << "cannot open the bloodcamp.dat file. \n";
	}
	out.write((char*)&y, sizeof(Blooddonationcamp));


}


//=============================================|| Hospital Information ||==============================================================
//=====================================================================================================================================
void Allhospitalinfo()
{
	ifstream in("hospital.txt");
	if (!in)
	{
		cout << "File not Found";
	}
	cout << "\n\t\t\t                          *Hospital Information List*  \n\n";
	cout << "|---Hospital Name---|" << setw(10) << "|---Password---|\n";
	cout << "-----------------------------------------------------\n";
	while (in.read((char*)&h, sizeof(Hospital)))
	{
		h.show_account();

	}

	in.close();
}

//=============================================|| Admin Menu ||=================================================
//==============================================================================================================

void Admin_Menu()
{
	char ch;
	do
	{
		system("cls");
		cout << "\n\n\n\t              ||ADMIN MAIN MENU||";
		cout << "\n\n\n\t----------------Register------------------------";
		cout << "\n\n\tA. REGISTER BLOOD DONOR"; 
		cout << "\n\n\tB. REGISTER HOSPITAL";//f
		cout << "\n\n\tC. REGISTER BLOOD DONATION CAMP";  //f
		cout << "\n\n\tD. ADD BLOOD STOCK"; //f
		cout << "\n\n\n\t----------------View All Record---------------- ";
		cout << "\n\n\tE. VIEW ALL BLOOD DONOR RECORD";//f
		cout << "\n\n\tF. VIEW ALL HOSPITAL RECORD";//f
		cout << "\n\n\tG. VIEW ALL BLOOD DONATION CAMP RECORD";//f
		cout << "\n\n\tH. VIEW ALL BLOOD STOCK RECORD";//f
		cout << "\n\n\n\t----------------Request-------------------------";
		cout << "\n\n\tI. MANAGE HOSPITAL REQUEST";//f
		cout << "\n\n\n\t----------------Update--------------------------";
		cout << "\n\n\tJ. UPDATE BLOOD DONATION CAMP RECORD"; //f
		cout << "\n\n\tK. EXIT";
		cout << "\n\n\tSelect Your Option (A-K) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case 'A':
			BloodDonar_Account();
			break;
		case 'B':
			Hospital_Account();
			break;
		case 'C':
			Bloodcamp_Account();
			break;
		case 'D':
			Bloodstock_Account();
			break;
		case 'E':
			Allblooddonarinfo();
			break;
		case 'F':
			Allhospitalinfo();
			break;
		case 'G':
			Allbloodinfo();
			break;
		case 'H':
			AllBloodstock();
			break;
		case 'I':
	    	All_bloodRequest();
			break;
		case 'J':
			Update_bloodcamp();
			break;
		case 'K':
			cout << "\n\n\tThanks For Using X-Treme Blood Bank Management System";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != 'K');

	Login_menu();
}
//=============================================|| Blood Donor Menu ||=============================================
//=================================================================================================================

void Donor_Menu()
{
	char ch;
	do {
		system("cls");
		cout << "\n\n             ---------------Login Menu Of Blood Donor-------------- \n";
		cout << "\n\n\t           1.View or Update Profile" << endl;
		cout << "\n\n\t           2.Request For Blood Donation"<< endl;
		cout << "\n\n\t           3.Exit" << endl;
		cout << "\n\n\t           Select Your Option (1-3)" << endl;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			Update_donorprofile();
			break;
		case '2':
			BloodDonation_request();
			break;
		case '3':
			cout << "\n\n\tThanks For Using X-Treme Blood Bank Management System";
			break;
		default:cout << "\a";

		}

		cin.ignore();
		cin.get();
	} while (ch != '3');
	Login_menu();
}

//=============================================|| Hospital Menu ||=================================================
//=================================================================================================================

void Hospital_Menu()
{
	char ch;
	do {
		system("cls");
		cout << "\n\n             ---------------Login Menu Of Hospital User------------" << endl;
		cout << "\n\n\t           1.View or Update Profile" << endl;
		cout << "\n\n\t           2.Request For Blood" << endl;
		cout << "\n\n\t           3.View Waiting Request Record" << endl;
		cout << "\n\n\t           4.Exit" << endl;
		cout << "\n\n\t           Select Your Option (1-4)" << endl;   
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
         	Update_profile();
			break;
		case '2':
			Blood_request();
			break;
		case '3':
			View_bloodrequest();
			break;
		case '4':
			cout << "\n\n\tThanks For Using X-Treme Blood Bank Management System";
			break;
		default:cout << "\a";

		}

		cin.ignore();
		cin.get();
	} while (ch != '4');
	Login_menu();
}
//=============================================|| Admin Login ||================================================
//==============================================================================================================

void Admin_login()
{
	string username = "";
	string password = "";
	bool loginSuccess = false;

	do {
		cout << "\n\n Enter Username: ";
		cin >> username;
		cout << "\n\n Enter Password: ";
		cin >> password;
		system("cls");
		if ((username == "admin") && (password == "123"))
		{
			cout << "Login Successfull" << endl;

			Admin_Menu();
			loginSuccess = true;

		}
		else
		{
			cout << "Incorrect username or password \n";
			cout << "Please try to login again";
		}
	} while (!loginSuccess);

}

//=============================================|| Blood Donar Login ||================================================
//====================================================================================================================

void BloodDonar_login()
{
	char n[25], p[5];
	int flag = 0;
	ifstream in("Donar.txt", ios::in | ios::out);

	cin.get();
	cout << "\n\n Enter the Name: ";
	cin.getline(n, 25);
	cout << "\n\n Enter the Password: ";
	cin >> p;

	if (!in)
	{
		cout << "File Not Found";
	}

	while (in.read((char *)&b, sizeof(BloodDonar)))
	{
		if (strcmp(b.name, n) == 0 && strcmp(b.password, p) == 0)
		{
			strcpy_s(user, b.name);
			flag = 1;
			cout << "\n\tWELCOME  " << b.name << "\n";
			Donor_Menu();

		}
	}
	if (flag == 0)
	{
		cout << "\tWrong User Name or Password";
		BloodDonar_login();
	}
	in.close();

}


//=============================================|| Hospital Login ||================================================
//=================================================================================================================

void hospital_login()
{
	char n[25], p[5];
	int flag = 0;
	ifstream in("hospital.txt", ios::in | ios::out);

	cin.get();
	cout << "\n\n Enter the Hospital Name: ";
	cin.getline(n, 25);
	cout << "\n\n Enter the Password: ";
	cin >> p;

	if (!in)
	{
		cout << "File Not Found";
	}

	while (in.read((char *)&h, sizeof(Hospital)))
	{
		if (strcmp(h.hospital_name, n) == 0 && strcmp(h.password, p) == 0) // compare the two char character
		{
			strcpy_s(current_user, h.hospital_name);
			flag = 1;
			cout << "\n\tWELCOME  " << h.hospital_name << "\n";
			Hospital_Menu();


		}
	}
	if (flag == 0)
	{
		cout << "\tWrong User Name or Password";
		hospital_login();
	}
	in.close();

}

//=====================================|| Introduction Page ||=========================================
//=====================================================================================================


void intro()
{
	system("cls");
	cout << "\n\n\t ===========================================================";
	cout << "\n\n\t               X-Treme Blood Bank MANAGEMENT";
	cout << "\n\n\t ===========================================================";
	
}

void Login_menu()
{
	intro();
	char ch;
	cout << "\n\n             ---------------Login Menu Of User------------" << endl;
	cout << "\n\n\t           1.Admin" << endl;
	cout << "\n\n\t           2.Hospital" << endl;
	cout << "\n\n\t           3.Blood Donar" << endl;
	cout << "\n\n\t           4.Exit" << endl;
	cout << "\n\n\t           Select Your Option (1-4) " << endl;
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		Admin_login();
		break;
	case '2':
		hospital_login();
		break;
	case '3':
		BloodDonar_login();
		break;
	case '4':
		exit(0);

	}
}

//=====================================|| Main Function ||====================================
//============================================================================================

int main()
{
	Login_menu();
	system("Pause");
	return 0;
}