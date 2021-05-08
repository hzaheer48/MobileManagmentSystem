#include<iostream>
#include<list>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
int c = 0;
int x = 0;
template<typename T>
void display(const list<T>& l)
{
	typename list<T>::const_iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
}
template<typename T>
list<T> search(const list<T>& l, const T& val)
{
	typename list<T>::const_iterator it;
	list<T> l2;
	if (c == 1) //searching with price option check
	{

		double val1;
		cout << "Enter ending range[Rs]: ";
		cin >> val1;
		for (it = l.begin(); it != l.end(); it++)
		{
			if (*it >= val && *it <= val1)
			{
				l2.push_back(*it);
			}
		}
		c = 0;
		return l2;
	}
	else // all other searching check
	{
		for (it = l.begin(); it != l.end(); it++)
		{
			if (*it == val)
			{
				l2.push_back(*it);
			}
		}
		return l2;
	}
}

template<typename T>
void update(list<T>& l, const T& val)
{
	typename list<T>::const_iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		T v;
		if (*it == val) //when data matched with val
		{
			cin >> v;
			//inserting updated at the place of data to be updated
			//insert function will push old data one place forward
			//iterator will point to old data i.e. data after updated data
			//which is old data in this case
			l.insert(it, v);
			l.erase(it);	//deleting old data
			cout << setw(43) << "Record UPDATED SUCCESSFULLY!" << endl;
			x = 1;
			break;
		}
	}
}
template<typename T>
void delt(list<T>& l, const T& val)
{
	typename list<T>::const_iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		if (*it == val)	//when data matched with val
		{
			l.erase(it);	//deleting data
			cout << setw(43) << "Record DELETED SUCCESSFULLY!" << endl;
			x = 1;
			break;
		}

	}
}
template<typename T>
void writing_to_the_file(list<T>& l, ostream& f1)
{
	//writing whole list to the file
	typename list<T>::const_iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		f1.write((const char*)&*it, sizeof(T));
	}
}
struct MobilePhone {
	string name;
	string company;
	string android_ios;
	double display_size = 0;
	double ram_size = 0;
	double storage_capacity = 0;
	double price = 0;
	friend ostream& operator<<(ostream& out, const MobilePhone& m)
	{
		out << endl;
		out << endl;
		out << setw(21) << "Name: " << m.name << endl;
		out << setw(24) << "Company: " << m.company << endl;
		out << setw(24) << "Version: " << m.android_ios << endl;
		out << setw(29) << "Display size: " << m.display_size << " inches" << endl;
		out << setw(20) << "Ram: " << m.ram_size << " GB" << endl;
		out << setw(33) << "Storage Capacity: " << m.storage_capacity << " GB" << endl;
		out << setw(22) << "Price: " << m.price << " Rs" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, MobilePhone& m)
	{
		cout << "Adding mobile phone: " << endl;
		cout << "Enter name of the mobile phone: ";
		in.ignore();
		//used this to work in correspondence with getline function.maybe it doesn't display first letter 
		getline(in, m.name); //used getline funtion to read charchters after spaces also
		cout << "Enter company of the mobile phone: ";
		getline(in, m.company); //used getline funtion to read charchters after spaces also
		cout << "Enter version of the mobile phone[android/ios]: ";
		getline(in, m.android_ios); //used getline funtion to read charchters after spaces also
		cout << "Enter display size of the mobile phone[inches]: ";
		in >> m.display_size;
		cout << "Enter ram size of the mobile phone[GB]: ";
		in >> m.ram_size;
		cout << "Enter storage capacity of the mobile phone[GB]: ";
		in >> m.storage_capacity;
		cout << "Enter price of the mobile phone[Rs]: ";
		in >> m.price;
		return in;
	}
	void operator=(const MobilePhone& m)
	{
		name = m.name;
		company = m.company;
		android_ios = m.android_ios;
		display_size = m.display_size;
		ram_size = m.ram_size;
		storage_capacity = m.storage_capacity;
		price = m.price;
	}
	bool operator ==(const MobilePhone& m) const
	{
		//making every attribute key for searching with different attributes
		if ((name == m.name) || (company == m.company) || (android_ios == m.android_ios) || (display_size == m.display_size) || (ram_size == m.ram_size) || (storage_capacity == m.storage_capacity) || (price == m.price))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>=(const MobilePhone& m) const
	{
		if (price >= m.price)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>=(double s) const
	{
		if (price >= s)
		{
			return true;
		}
		else
		{
			return false;

		}

	}
	bool operator<=(const MobilePhone& m) const
	{
		if (price <= m.price)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<=(double s) const
	{
		if (price <= s)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{

	list<MobilePhone> l1;
	int opt;
	int ch;
	ifstream file("data.bin", ios::binary | ios::ate);
	//if file already exists
	if (file.fail())
	{
		cout << endl;
	}
	else
	{
		//readring records from file if it exist
		//making array of those records
		//pushing them in list
		MobilePhone m;
		int nbytes = file.tellg(); //reading total number of bytes
		int n = nbytes / sizeof(MobilePhone);	//total records
		MobilePhone* m_array = new MobilePhone[n]; //creating dynamic array of no of records
		file.seekg(0);
		file.read((char*)m_array, nbytes); //reading all records 
		for (int i = 0; i < n; i++)
		{
			l1.push_back(m_array[i]); //pushing them in list
		}
	}
	file.close();
	do
	{
		system("cls");
		cout << endl << setw(24) << "GSM ARENA" << endl;
		cout << setw(34) << "Press 1: ADD Record" << endl;
		cout << setw(37) << "Press 2: SEARCH Record" << endl;
		cout << setw(37) << "Press 3: UPDATE Record" << endl;
		cout << setw(37) << "Press 4: DELETE Record" << endl;
		cout << setw(39) << "Press 5: DISPLAY Records" << endl;
		cout << setw(28) << "Press 6: Exit" << endl;
		cout << setw(29) << "Enter option: ";
		cin >> opt;
		if (opt == 1)
		{
			ofstream file_1("data.bin", ios::binary | ios::app);
			system("cls");
			cout << endl << setw(37) << "ADDING Mobile to Arena" << endl;
			MobilePhone m;
			cin >> m;
			file_1.write((const char*)&m, sizeof(MobilePhone));
			flush(file_1);
			l1.push_back(m);
			file_1.close();
		}
		if (opt == 2)
		{
			int search_criteria;
			MobilePhone m;
			system("cls");
			cout << endl << setw(40) << "SEARCHING Mobile in Arena" << endl;
			cout << setw(39) << "Press 1: SEEARCH by name" << endl;
			cout << setw(41) << "Press 2: SEARCH by company" << endl;
			cout << setw(41) << "Press 3: SEARCH by version" << endl;
			cout << setw(46) << "Press 4: SEARCH by display size" << endl;
			cout << setw(37) << "Press 5: SEARCH by ram" << endl;
			cout << setw(50) << "Press 6: SEARCH by storage capacity" << endl;
			cout << setw(45) << "Press 7: SEARCH by price range" << endl;
			cout << setw(28) << "Press 8: EXIT" << endl;
			cout << setw(29) << "Enter option: ";
			cin >> search_criteria;
			if (search_criteria == 1)
			{

				system("cls");
				cout << endl << setw(39) << "SEARCHIMG Mobile by name" << endl;
				int options;
				cin.ignore();
				cout << "Enter name of the Mobile Phone:";
				getline(cin, m.name);
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				system("pause");
			}
			if (search_criteria == 2)
			{
				system("cls");
				cin.ignore();
				cout << endl << setw(42) << "SEARCHIMG Mobile by company" << endl;
				cout << "Enter name of the company:";
				getline(cin, m.company);
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by version" << endl;
						cout << setw(46) << "Press 2: FILTER by display size" << endl;
						cout << setw(37) << "Press 3: FILTER by ram" << endl;
						cout << setw(50) << "Press 4: FILTER by storage capacity" << endl;
						cout << setw(45) << "Press 5: FILTER by price range" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> (option);
						if (option == 1)
						{
							cout << endl;
							cout << endl << setw(42) << "FILTERING Mobile by version" << endl;
							cout << "Enter version[android/ios]: ";
							cin >> m2.android_ios;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(47) << "FILTERING Mobile by display size" << endl;
							cout << "Enter display size[inches]: ";
							cin >> m2.display_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(38) << "FILTERING Mobile by ram" << endl;
							cout << "Enter ram size[GB]: ";
							cin >> m2.ram_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(51) << "FILTERING Mobile by storage capacity" << endl;
							cout << "Enter storage capacity[GB]: ";
							cin >> m2.storage_capacity;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(46) << "FILTERING Mobile by price range" << endl;
							cout << "Enter starting range[Rs]: ";
							cin >> m2.price;
							c++;
							l2 = search(l2, m2);
							display(l2);
						}

					} while (option != 0);
				}
				else
				{
					continue;
				}

			}
			if (search_criteria == 3)
			{
				system("cls");
				cin.ignore();
				cout << endl << setw(42) << "SEARCHIMG Mobile by version" << endl;
				cout << "Enter name of the version[android/ios]: ";
				getline(cin, m.android_ios);
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by company" << endl;
						cout << setw(46) << "Press 2: FILTER by display size" << endl;
						cout << setw(37) << "Press 3: FILTER by ram" << endl;
						cout << setw(50) << "Press 4: FILTER by storage capacity" << endl;
						cout << setw(45) << "Press 5: FILTER by price range" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> (option);
						if (option == 1)
						{
							cout << endl << setw(42) << "FILTERING Mobile by company" << endl;
							cout << "Enter company: ";
							cin >> m2.company;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(47) << "FILTERING Mobile by display size" << endl;
							cout << "Enter display size[inches]: ";
							cin >> m2.display_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(38) << "FILTERING Mobile by ram" << endl;
							cout << "Enter ram size[GB]: ";
							cin >> m2.ram_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(51) << "FILTERING Mobile by storage capacity" << endl;
							cout << "Enter storage capacity[GB]: ";
							cin >> m2.storage_capacity;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(46) << "FILTERING Mobile by price range" << endl;
							cout << "Enter starting range[Rs]: ";
							c++;
							l2 = search(l2, m2);
							display(l2);
						}
					} while (option != 0);
				}
				else
				{
					continue;
				}

			}
			if (search_criteria == 4)
			{
				system("cls");
				cin.ignore();
				cout << endl << setw(47) << "SEARCHIMG Mobile by display size" << endl;
				cout << "Enter name of the display siz:";
				cin >> m.display_size;
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by company" << endl;
						cout << setw(41) << "Press 2: FILTER by version" << endl;
						cout << setw(37) << "Press 3: FILTER by ram" << endl;
						cout << setw(50) << "Press 4: FILTER by storage capacity" << endl;
						cout << setw(45) << "Press 5: FILTER by price range" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> (option);
						if (option == 1)
						{
							cout << endl << setw(42) << "FILTERING Mobile by company" << endl;
							cout << "Enter company: ";
							cin >> m2.company;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(42) << "FILTERING Mobile by version" << endl;
							cout << "Enter version[android/ios]: ";
							cin >> m2.android_ios;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(38) << "FILTERING Mobile by ram" << endl;
							cout << "Enter ram size[GB]: ";
							cin >> m2.ram_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(51) << "FILTERING Mobile by storage capacity" << endl;
							cout << "Enter storage capacity[GB]: ";
							cin >> m2.storage_capacity;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(46) << "FILTERING Mobile by price range" << endl;
							cout << "Enter starting range[Rs]: ";
							cin >> m2.price;
							c++;
							l2 = search(l2, m2);
							display(l2);
						}
					} while (option != 0);
				}
				else
				{
					continue;
				}
			}
			if (search_criteria == 5)
			{
				system("cls");
				cin.ignore();
				cout << endl << setw(38) << "SEARCHIMG Mobile by ram" << endl;
				cout << "Enter ram size[GB]:";
				cin >> m.ram_size;
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by company" << endl;
						cout << setw(41) << "Press 2: FILTER by version" << endl;
						cout << setw(46) << "Press 3: FILTER by display size" << endl;
						cout << setw(50) << "Press 4: FILTER by storage capacity" << endl;
						cout << setw(45) << "Press 5: FILTER by price range" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> (option);
						if (option == 1)
						{
							cout << endl << setw(42) << "FILTERING Mobile by company" << endl;
							cout << "Enter company: ";
							cin >> m2.company;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(42) << "FILTERING Mobile by version" << endl;
							cout << "Enter version[android/ios]: ";
							cin >> m2.android_ios;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(47) << "FILTERING Mobile by display size" << endl;
							cout << "Enter display size[inches]: ";
							cin >> m2.display_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(51) << "FILTERING Mobile by storage capacity" << endl;
							cout << "Enter storage capacity[GB]: ";
							cin >> m2.storage_capacity;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(46) << "FILTERING Mobile by price range" << endl;
							cout << "Enter starting range[Rs]: ";
							cin >> m2.price;
							c++;
							l2 = search(l2, m2);
							display(l2);
						}
					} while (option != 0);
				}
				else
				{
					continue;
				}
			}
			if (search_criteria == 6)
			{
				system("cls");
				cin.ignore();
				cout << endl << setw(51) << "SEARCHIMG Mobile by storage capacity" << endl;
				cout << "Enter name of the company:";
				cin >> m.storage_capacity;
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);;
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by company" << endl;
						cout << setw(41) << "Press 2: FILTER by version" << endl;
						cout << setw(46) << "Press 3: FILTER by display size" << endl;
						cout << setw(37) << "Press 4: FILTER by ram" << endl;
						cout << setw(45) << "Press 5: FILTER by price range" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> option;
						if (option == 1)
						{
							cout << endl << setw(42) << "FILTERING Mobile by company" << endl;
							cout << "Enter company: ";
							cin >> m2.company;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(42) << "FILTERING Mobile by version" << endl;
							cout << "Enter version[android/ios]: ";
							cin >> m2.android_ios;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(47) << "FILTERING Mobile by display size" << endl;
							cout << "Enter display size[inches]: ";
							cin >> m2.display_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(38) << "FILTERING Mobile by ram" << endl;
							cout << "Enter ram size[GB]: ";
							cin >> m2.ram_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(46) << "FILTERING Mobile by price range" << endl;
							cout << "Enter starting range[Rs]: ";
							cin >> m2.price;
							c++;
							l2 = search(l2, m2);
							display(l2);
						}
					} while (option != 0);
				}
				else
				{
					continue;
				}
			}
			if (search_criteria == 7)
			{
				c++;
				system("cls");
				cin.ignore();
				cout << endl << setw(46) << "SEARCHIMG Mobile by price range" << endl;
				cout << "Enter starting range[Rs]: ";
				cin >> m.price;
				list<MobilePhone> l2;
				l2 = search(l1, m);
				display(l2);
				cout << endl << endl;
				cout << setw(30) << "Press 1: FILTER" << endl;
				cout << setw(28) << "Press 0: EXIT" << endl;
				cout << setw(29) << "Enter option: ";
				int options;
				cin >> options;
				if (options == 1)
				{
					int option;
					do
					{
						cout << endl << endl;
						cout << setw(24) << "FILTERING" << endl;
						MobilePhone m2;
						cout << setw(41) << "Press 1: FILTER by company" << endl;
						cout << setw(41) << "Press 2: FILTER by version" << endl;
						cout << setw(46) << "Press 3: FILTER by display size" << endl;
						cout << setw(37) << "Press 4: FILTER by ram" << endl;
						cout << setw(50) << "Press 5: FILTER by sotrage capacity" << endl;
						cout << setw(28) << "Press 0: EXIT" << endl;
						cout << setw(29) << "Enter option: ";
						cin >> option;
						if (option == 1)
						{
							cout << endl << setw(42) << "FILTERING Mobile by company" << endl;
							cout << "Enter company: ";
							cin >> m2.company;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 2)
						{
							cout << endl << setw(42) << "FILTERING Mobile by version" << endl;
							cout << "Enter version[android/ios]: ";
							cin >> m2.android_ios;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 3)
						{
							cout << endl << setw(47) << "FILTERING Mobile by display size" << endl;
							cout << "Enter display size[inches]: ";
							cin >> m2.display_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 4)
						{
							cout << endl << setw(38) << "FILTERING Mobile by ram" << endl;
							cout << "Enter ram size[GB]: ";
							cin >> m2.ram_size;
							l2 = search(l2, m2);
							display(l2);
						}
						if (option == 5)
						{
							cout << endl << setw(51) << "FILTERING Mobile by storage capacity" << endl;
							cout << "Enter storage capacity[GB]: ";
							cin >> m2.storage_capacity;
							l2 = search(l2, m2);
							display(l2);
						}
					} while (option != 0);
				}
				else
				{
					continue;
				}
			}
			if (search_criteria == 8)
			{
				continue;
			}

		}
		if (opt == 3)
		{
			system("cls");
			MobilePhone m;
			cin.ignore();
			cout << endl;
			cout << setw(34) << "UPDATING from Arena" << endl;
			cout << "Enter name of the phone you want to update: ";
			getline(cin, m.name);
			update(l1, m);
			if (x == 1)
			{
				ofstream file_2("data.bin", ios::binary);
				writing_to_the_file(l1, file_2);
				file_2.close();
				x = 0;
			}
			else
			{
				cout << setw(32) << "Record not found!" << endl;
			}
			system("pause");
		}
		if (opt == 4)
		{
			system("cls");
			MobilePhone m;
			cin.ignore();
			cout << endl;
			cout << setw(34) << "DELETING from Arena" << endl;
			cout << "Enter name of the phone you want to delete: ";
			getline(cin, m.name);
			delt(l1, m);
			if (x == 1)
			{
				ofstream file_2("data.bin", ios::binary);
				writing_to_the_file(l1, file_2);
				file_2.close();
				x = 0;
			}
			else
			{
				cout << setw(32) << "Record not found!" << endl;
			}
			system("pause");
		}
		if (opt == 5)
		{
			system("cls");
			cout << setw(36) << "DISPLAYING from Arena" << endl;
			display(l1);
			system("pause");
		}
	} while (opt != 6);
}