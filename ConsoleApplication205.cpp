#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;
struct info
{
	string name, phone, pincode, number;
	bool  mk_correct=false;
	double account_balance;
};
vector<string>splite(string s1,string deamter="#||#") {
	short posstion = 0;
	vector<string>vx;
	string world;
	while((posstion = s1.find(deamter)) != std::string::npos) {
		world = s1.substr(0, posstion);
		if (world != "") {
			vx.push_back(world)
				;
		}
		s1.erase(0, posstion + deamter.length());
	}
	if (s1 != "") {
		vx.push_back(s1);
	}
	return vx;
}
info load_vector_to_client(string s1) {
	string s2;
	info client;
	vector<string>vx = splite(s1);
	client.number = vx[0];
	client.pincode = vx[1];
	client.name = vx[2];
	client.phone = vx[3];
	client.account_balance = stod(vx[4]);
	return client;
}
string convert_to_line(info C) {
	string s1;
	s1 += C.number + "#||#";
	s1 += C.pincode + "#||#";
	s1 += C.name + "#||#";
	s1 += C.phone + "#||#";
	s1 += to_string(C.account_balance);
	return s1;
}
vector<info> read_file() {
	fstream myfile;
	vector<info>vx;
	string line;
	info client;
	myfile.open("Client.txt", ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			client = load_vector_to_client(line);
			vx.push_back(client);
		}
		myfile.close();
	}
	return vx;

}
void show_client_list(){
	vector<info>vx = read_file();
	cout << "\t\t\tCLIENT LIST (" << vx.size() << ") Clients.\n\n";
	cout<<"_____________________________________________________________________________________________________\n\n";
	cout << left << setw(10) << "| Account number ";
	cout << left << setw(10) << "| pincod" ;
	cout << left << setw(20) << "| name " ;
	cout <<left << setw(15) << "| phone " ;
	cout<<left << setw(30) << "| Account number " ;
	cout << "\n___________________________________________________________________________________________________\n\n";
	for (info& clien : vx) {
		cout <<left<<"| " <<  setw(15)<<clien.number <<"| "<< setw(8) <<clien.pincode  <<"| "<< setw(18) << clien.name <<"| " << setw(13) <<clien.phone<<"| "<< setw(30) <<clien.account_balance;
		cout << endl;
	}
	
}
bool find_acc(string account_number){
	vector<info>vx;
	fstream myfile;
	myfile.open("Client.txt", ios::in);
	if (myfile.is_open()) {
		string line;
		info c;
		while (getline(myfile, line)) {
			c = load_vector_to_client(line);
			if (c.number == account_number) {
				myfile.close();
				return 1;
			}
			vx.push_back(c);
		}
		myfile.close();
	}
	return 0;
}
info Add() {
	cout << "__________________________________________________\n\n";
	cout << "\t\tadd new client \n ";
	cout << "__________________________________________________\n\n";
	info add;
	cout << "enter the Number:\t";
	getline(cin >> ws, add.number);
	while (find_acc(add.number)) {
		cout << "\nClient with [" << add.number << "]";
			cout<<"already exists, Enter another Account Number ? " ;
	getline(cin >> ws, add.number);
	}
	cout << "enter the Pincode:\t";
	getline(cin, add.pincode);
	cout << "enter the name:\t";
	getline(cin, add.name);
	cout << "enter the phone:\t";
	getline(cin, add.phone);
	cout << "enter the Account balance:\t";
	cin >> add.account_balance;
	return add;
}
void add_new_client() {
	fstream myfile;
	string line;
	vector<info>vx;
	myfile.open("Client.txt", ios::out | ios::app);
	if (myfile.is_open()) {
		info add = Add();
		line = convert_to_line(add);
		myfile << line<<endl;
	}
	myfile.close();

}
bool findd(string number,vector<info>& vx, info& c) {
	for (info& Clinet : vx) {
		if (Clinet.number == number) {
			c = Clinet;
			return 1;
		}
	}
	return 0;

}
bool chang_mk(string number, vector<info>& vx) {
	for (info& Clinet : vx) {
		if (Clinet.number == number) {
			Clinet.mk_correct = true;
			return 1;
		}
	}
	return 0;
}
void print_info(string s1,info clint) {

	
		if (clint.number == s1) {
			cout << "Account number :" << clint.number << endl;
			cout << "Pincode :" << clint.pincode << endl;
			cout << "Name :" << clint.name << endl;
			cout << "Phone :" << clint.phone << endl;
			cout << "Account balanc :" << clint.account_balance<<endl;
		}
	
}
vector<info>save_info( vector<info>& vx) {
	fstream myfile;
	myfile.open("Client.txt", ios::out);
	if (myfile.is_open()) {
		for (info c : vx) {
			if (c.mk_correct==false) {
				myfile << c.number << "#||#" << c.pincode << "#||#" << c.name << "#||#" << c.phone << "#||#" << c.account_balance<<endl;
			}
		}
		myfile.close();
	}
	return vx;

}
void fun_of_delet(string name, vector<info>& vx) {
	string s1;
	info client;
	if (findd(name, vx, client)) {
		print_info(name,client);
		cout << "do you want to delet this client :";
		cin >> s1;
		if (s1 == "y" || s1 == "Y") {
			chang_mk(name, vx);
			vx = save_info(vx);
			cout << "Done :-)";
		}
	}
	else
	{
		cout << "the number of client <<" << s1 << ">> not found ";
		
	}
}
string reserach() {
	string name;
	cout << "please enter the client of number do you want  :\n";
	cin >> name;
	return name;
}
vector<info> UPD(vector<info>& vx) {
	info c;
	string name = reserach();
	for (info &client : vx) {
		if (client.number == name) {
			cout << "enter the Pincode:\t";
			getline(cin >> ws, client.pincode);
			cout << "enter the name:\t";
			getline(cin, client.name);
			cout << "enter the phone:\t";
			getline(cin, client.phone);
			cout << "enter the Account balance:\t";
			cin >> client.account_balance;
		}
		
	}
	return vx;
	
}
void print_upd() {
	vector<info>vx = read_file();
	vector<info>vxx = UPD(vx);
	vector<info>vxxx = save_info(vxx);

}
void print_find(vector<info>& vx) {
	string s1 = reserach();
	for (info c : vx) {
		if (c.number == s1) {

			cout << "Account number :" << c.number << endl;
			cout << "Pincode :" << c.pincode << endl;
			cout << "Name :" << c.name << endl;
			cout << "Phone :" << c.phone << endl;
			cout << "Account balanc :" << c.account_balance;

			break;
		}
	}
}
int main() {
	short s1=0;
	
	do {
		system("cls");
		cout << "----------------------------------------------------------------------------\n";
		cout << "____________________________________________________________________________\n";
		cout << "\t\t\tMain Menue List \n";
		cout << "----------------------------------------------------------------------------\n";
		cout << "____________________________________________________________________________\n";
		cout << "[1] Show Client List. \n";
		cout << "[2] Add New Client. \n";
		cout << "[3]  Delete Client. \n";
		cout << "[4] Update Client Info.\n";
		cout << "[5] Find Client Info.\n";
		cout << "[6] Exit.\n";
		cout << "_____________________________________________________________________________\n";
		cin >> s1;
		switch (s1)
		{

		case 1: {
			system("cls");
			show_client_list();
			cout << "press any key to go back to the main menue..."; system("pause> nul");
			break;
		}

		case 2: {
			system("cls");
			add_new_client();
			cout << "press any key to go back to the main menue..."; system("pause> nul");
			break;
		}

		case 3: {
			system("cls");
			vector < info>vx = read_file();
			string s2;
			cout << "\nlease enter the account number:\t";
			cin >> s2;
			fun_of_delet(s2, vx);
			cout << "\npress any key to go back to the main menue...";
			system("pause>nul");
			break;
		}

		case  4: {
			system("cls");
			print_upd();
			cout << "\npress any key to go back to the main menue...";
			system("pause>nul");
			break;
		}

		case 5: {
			system("cls");
			vector < info>vx = read_file();
			print_find(vx);
			cout << "\npress any key to go back to the main menue...";
			system("pause>nul");
			break;
		}

		case 6: {
			system("cls");
			cout << "\n-------------------------------------\n";
			cout << "_____________________________________\n";
			cout << "\tPrograme Ends.";
			cout << "\n-------------------------------------\n";
			cout << "_____________________________________\n";
			break;
		}
		}
		
	} while (s1 != 6);
	return 0;
}
