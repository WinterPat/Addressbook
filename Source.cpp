#define _CRTDBG_MAP_ALLOC
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <sstream> 
#include <string>
#include <list>
#include <iomanip>
#include <crtdbg.h>


using namespace std;
class ContactInfo {
private:
	string first;
	string last;
	string email;
	string city;
	string relative;
	string relativeL;
	string number;
	static int count;
	int currentCount;

public:
	ContactInfo(string first0 = "", string last0 = "", string email0 = "", string city0 = "", string relative0 = "", string relativeL0 = "", string number0 = "")
		: first(first0), last(last0), email(email0), city(city0), relative(relative0), relativeL(relativeL0), number(number0) {
		currentCount = count++;
	}
	~ContactInfo() { };
	friend ostream& operator <<(ostream& out, const ContactInfo& c);
	friend ofstream& operator <<(ofstream& out, ContactInfo& c);
	friend istream& operator >>(istream& in, ContactInfo& c);
	friend ifstream& operator >>(ifstream& in, ContactInfo& c);
	string getLast()const;
	string getFirst()const;
	string getEmail() const;
	string getCity()const;
	string getNumber()const;
	string getRelative()const;
	string getRelativeL()const;
	string getName()const;
	string getNameR()const;
	int getCount()const;


};


int ContactInfo::count = 0;
bool sortBy(const ContactInfo& a, const ContactInfo& b);
bool sortByName(const ContactInfo& b, const ContactInfo& a);
void add(ContactInfo& c);
void remove();
void find();
void removeAll();
void readF();
void printF();
void program();
void removeBy();
void stringToUpper(string& s);

int main() {
	program();
	_CrtDumpMemoryLeaks();
	return 0;
}
ifstream& operator >>(ifstream& in, ContactInfo& c) {
	in >> c.first >> c.last >> c.email >> c.city >> c.relative >> c.relativeL >> c.number 
		>> c.count;
	return in;
}
istream& operator >>(istream& in, ContactInfo& c) {
	cout << "Enter first name: ";
	getline(in, c.first);
	cout << "Enter last name: ";
	getline(in, c.last);
	cout << "Enter email address: ";
	getline(in, c.email);
	cout << "Enter your city: ";
	getline(in, c.city);
	cout << "Enter relatives first name: ";
	getline(in, c.relative);
	cout << "Enter relatives last name: ";
	getline(in, c.relativeL);
	cout << "Enter telephone number: ";
	getline(in, c.number);
	return in;
}
ofstream& operator <<(ofstream& out, ContactInfo& c) {
	out << c.first << ":  " << c.last << ":  " << c.email << ": " << c.city << ": " << c.relative 
		<< ": " << c.relativeL << ": " << c.number << ": " << endl;
	return out;
}
ostream& operator <<(ostream& out, const ContactInfo& c) {
	out << c.first << " " << c.last << " " << c.email << " " << c.city 
		<< " " << c.relative << " " << c.relativeL << " " << c.number;
	return out;
}
string ContactInfo::getFirst()const {
	return first;
}
string ContactInfo::getLast()const{
	return last;
}
string ContactInfo::getEmail()const {
	return email;
}
string ContactInfo::getCity()const {
	return city;
}
string ContactInfo::getNumber()const {
	return number;
}
string ContactInfo::getRelative()const {
	return relative;
}
string ContactInfo::getRelativeL()const {
	return relativeL;
}
string ContactInfo::getName()const {
	return first + " " + last;
}
string ContactInfo::getNameR()const {
	return relative + " " + relativeL;
}
int ContactInfo::getCount()const {
	return currentCount;
}

/**
	@void add();
	Asks users inputs for contact.
	Prints the contact.
	Asks if user wants to save the contact to the file.
	If first and last name is not entered correctly saiving doesn't work.
*/
void add() {
	ContactInfo c;
	string str, test;
	ofstream out("text.txt", ios::app);
	cin >> c;
	
	test = c.getName();
	remove_if(test.begin(), test.end(), isspace);
	
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(19) << "Name|" << setw(30) << "Email|" << setw(15) << "City|"
		<< setw(18) << "Relative|" << setw(14) << "Number|" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(18) << c.getName() << "|" << setw(29) << c.getEmail() << "|"
		<< setw(14) << c.getCity() << "|" << setw(17) << c.getRelative() + " " + c.getRelativeL() 
		<< "|" << setw(13) << c.getNumber() << "|"
		<< endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "Do you want to save the contact to file?(yes/no)" << endl;
	getline(cin, str);
	stringToUpper(str);
	if(str == "YES" && c.getFirst() != "" && c.getLast() != "" && c.getEmail() != ""){
		out << c;
		cout << "The contact is saved to the file." << endl;
	}
	else if (c.getFirst() == "" || c.getLast() == "" || c.getEmail() == "") {
		cout << "At least First name,Last name and email must be entered!" << endl;
	}
	else {
		cout << "The contact not saved." << endl;
	}
	out.close();
}
/**
	@void removeBy();
	Asks user to choose removing method.
	Removes contact/contacts from file according to the choosen method.
*/
void removeBy() {
	string line, check, removed, method, str, str1, str2, str3, str4, str5, str6;
	int i = 0;
	cout << "Choose removing method: 'name', 'email' or 'all' " << endl;
	getline(cin, method);
	stringToUpper(method);

	if(method == "NAME"){
		cout << "Enter name of contact that you want to remove:" << endl;
		getline(cin, removed);
	}
	else if (method == "EMAIL") {
		cout << "Enter email of contact that you want to remove:" << endl;
		getline(cin, removed);
	}
	else if (method == "ALL") {
		cout << "Are you sure that you want to remove all contacts from contactbook?(yes/no)" << endl;
		getline(cin, check);
		stringToUpper(check);
		if (check == "YES") {
			cout << "Removing all contacts from contactbook..." << endl;
		}
	}
	else {
		cout << "No valid method entered" << endl;
	}
	ifstream in("text.txt", ios::app);
	ofstream out("temp.txt", ios::app);
	while (getline(in, line)) {
		istringstream is(line);
		is >> str >> str1 >> str2 >> str3 >> str4 >> str5 >> str6;
		str.erase(str.end() - 1);
		str1.erase(str1.end() - 1);
		str2.erase(str2.end() - 1);

		if (method == "NAME") {
			if (removed == str + " " + str1) {
				cout << "removing... " << endl;
				cout << str + " " + str1 << " from contactbook." << endl;
				i++;
			}
			if (removed != str + " " + str1) {
				out << line << endl;
			}
		}
		else if (method == "EMAIL") {
			if (removed == str2) {
				cout << "removing... " << endl;
				cout << str + " " + str1 << "from addresbook." << endl;
				i++;
			}
			if (removed != str2) {
				out << line << endl;
			}
		}
		else if (method == "ALL" && check == "YES") { i++;}
		else {
			out << line << endl;
		}
	}
	if (i == 0) {
		cout << "Person not found." << endl;
	}
	in.close();
	out.close();
	remove("text.txt");
	rename("temp.txt", "text.txt");
}
/**
	@void find();
	Asks user to choosen searching method(name, email, city, relative, number).
	Then asks user to enter the search parameter.
	Prints all found contacts according to choosen method and parameter.
	ex.
	If method is 'city' and search parameter is 'Helsinki'.
	Prints all contacts listed in Helsinki.	
*/
void find() {
	string search, method, line, str, str1, str2, str3, str4, str5, str6;
	vector<ContactInfo> vlist;
	int i = 0;
	cout << "Choose search method: 'name', 'email', 'city', 'relative' or 'number' " << endl;
	getline(cin, method);
	stringToUpper(method);

	if (method == "NAME") {
		cout << "Enter name of contact that you want to search:" << endl;
		getline(cin, search);
	}
	else if (method == "NUMBER") {
		cout << "Enter number of contact that you want to search:" << endl;
		getline(cin, search);
	}
	else if (method == "RELATIVE") {
		cout << "Enter relative of contact that you want to search:" << endl;
		getline(cin, search);
	}
	else if (method == "CITY") {
		cout << "Enter city of contact that you want to search:" << endl;
		getline(cin, search);
	}
	else if (method == "EMAIL") {
		cout << "Enter email of contact that you want to search:" << endl;
		getline(cin, search);
	}
	else {
		cout << "No valid method entered" << endl;
	}
	ifstream in("text.txt", ios::app);
	while (getline(in, line)) {
		istringstream is(line);
		is >> str >> str1 >> str2 >> str3 >> str4 >> str5 >> str6;
		str.erase(str.end() - 1);
		str1.erase(str1.end() - 1);
		str2.erase(str2.end() - 1);
		str3.erase(str3.end() - 1);
		str4.erase(str4.end() - 1);
		str5.erase(str5.end() - 1);
		str6.erase(str6.end() - 1);

		if (method == "NAME") {
			if (search == str + " " + str1) {
				vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
				i++;
			}
		}
		else if (method == "EMAIL") {
			if (search == str2) {
				vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
				i++;
			}
		}
		else if (method == "CITY") {
			if (search == str3) {
				vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
				i++;
			}
		}
		else if (method == "RELATIVE") {
			if (search == str4 + " " + str5) {
				vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
				i++;
			}
		}
		else if (method == "NUMBER") {
			if (search == str6) {
				vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
				i++;
			}
		}
	}
	in.close();
	if (i == 0) {
		cout << "Person not found." << endl;
	}
	else {
		sort(vlist.begin(), vlist.end(), sortBy);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "|" << setw(19) << "Name|" << setw(30) << "Email|" << setw(15) << "City|"
			<< setw(18) << "Relative|" << setw(14) << "Number|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		for (const auto& p : vlist) {
			cout << "|" << setw(18) << p.getName() << "|" << setw(29) << p.getEmail() << "|"
				<< setw(14) << p.getCity() << "|" << setw(17) << p.getRelative() + " " + p.getRelativeL() << "|" << setw(13) << p.getNumber() << "|"
				<< endl;
		}
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
}
/**
	@void stringToUpper(string& s);
	@param string
	Converts string to uppercase.
*/
void stringToUpper(string& s)
{
	for (unsigned int i = 0; i < s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}
}
/**
	@bool sortBy(const ContactInfo& a, const ContactInfo& b);
	@param two ContactInfo objects.
	Sorts the objects so the relatives are printed first.	
*/

bool sortBy(const ContactInfo& a, const ContactInfo& b) {	
	if (a.getRelativeL() != b.getRelativeL()) {
		if ((a.getRelativeL().length() == 0)) {
			cout << a.getRelative().length() << endl;
			return false;
		}
		return(a.getRelativeL() < b.getRelativeL());
	}
	/*else if(a.getCity() != b.getCity()) {
		return(a.getCity() < b.getCity());
	}*/
	return false;
}
bool sortByName(const ContactInfo& a, const ContactInfo& b) {
	return a.getEmail() < b.getEmail();
}

/**
	@void printF()
	Read and prints all contacts from contactbook file.
*/
void printF() {
	string search, search2, line, str, str1, str2, str3, str4, str5, str6;
	vector<ContactInfo> vlist;
	int i = 0;
	ifstream in("text.txt", ios::app);
	while (getline(in, line)) {
		if (line.find(search) != std::string::npos) {
			istringstream is(line);
			is >> str >> str1 >> str2 >> str3 >> str4 >> str5 >> str6;
			str.erase(str.end() - 1);
			str1.erase(str1.end() - 1);
			str2.erase(str2.end() - 1);
			str3.erase(str3.end() - 1);
			str4.erase(str4.end() - 1);
			str5.erase(str5.end() - 1);
			str6.erase(str6.end() - 1);
			vlist.push_back(ContactInfo(str, str1, str2, str3, str4, str5, str6));
		}
		i++;
	}
	in.close();
	sort(vlist.begin(), vlist.end(), sortBy);
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(19) <<  "Name|" << setw(30) << "Email|" << setw(15) << "City|"
		<< setw(18) << "Relative|" << setw(14) << "Number|"  << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	for (const auto& p : vlist) {
		cout << "|" << setw(18) << p.getName() << "|" << setw(29) << p.getEmail() << "|"
			<< setw(14) << p.getCity() << "|" << setw(17) << p.getRelative() + " " + p.getRelativeL() << "|" << setw(13) << p.getNumber() << "|"
			<< endl;
	}
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	vlist.clear();
}
/**
	@void program();
	Program logic and instructions for user how to use the program.
*/
void program() {
	string str;

	cout << "Starting program..." << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "|" << setw(32) << "CONTACTBOOK" << setw(25) << "|" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "|Commands are: 'add', 'remove', 'read', 'find' and 'exit'" << setw(0) << "|" << endl;
	cout << "|add: to add new contact to contactbook." << setw(18) << "|" << endl;
	cout << "|remove: to remove contact from contactbook." << setw(14) << "|" << endl;
	cout << "|read: to read contactbook data from file." << setw(16) << "|" << endl;
	cout << "|find: to search specific person." << setw(25) << "|" << endl;
	cout << "|exit: to exit the program." << setw(31) << "|" << endl;
	cout << "|help: to see all available commands" << setw(22) << "|" << endl;
	cout << "----------------------------------------------------------" << endl;
	do {
		cout << "Enter command:" << endl;
		getline(cin, str);
		stringToUpper(str);

		if (str == "ADD") {
			add();
		}
		if (str == "REMOVE") {
			removeBy();
		}
		if (str == "READ") {
			printF();
		}
		if (str == "FIND") {
			find();
		}
		if (str == "HELP") {
			cout << "Commands are: 'add', 'remove', 'read', 'find' and 'exit'" << endl;
		}
	} while (str != "EXIT");
	cout << "Closing program..." << endl;
}
