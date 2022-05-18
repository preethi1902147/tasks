#include<iostream>
#include <pqxx/pqxx> 
#include <string>
#include "VariadicTable.h"

using namespace std;
using namespace pqxx;

class hotel {
public:
	string sql, cat, input,room,floor,type,date,price ;
	
	void display()
	{
		connection C("dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
		sql = "SELECT * from ROOMS ";
		/* Create a non-transactional object. */
		nontransaction N(C);

		/* Execute SQL query */
		result R(N.exec(sql));

		VariadicTable<string, string, string, string, string> vt({ "r_no", "floor", "price", "date", "type"});
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>());
		}

		vt.print(cout);
	}

	void search()
	{
		connection C("dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
		cout << "category to search";
		cin >> cat;
		cout << " your choice";
		cin >> input;
		cout << "     ";
		cout << "    ";

		
		sql = "SELECT * from  ROOMS where "+cat+" = '"+input+"' ";
		/* Create a non-transactional object. */
		nontransaction N(C);

		/* Execute SQL query */
		result R(N.exec(sql));

		VariadicTable<string, string, string, string, string> vt({ "r_no", "floor", "price", "date", "type" });
		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>());
		}

		vt.print(cout);

	}

	void bookroom()
	{
		connection C("dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
		cout << "enter the room number to book";
		cin >>room;
		cout << "    ";
		cout << "    ";

		work W(C);

		sql = "DELETE from ROOMS where r_no = ' " + room + " ' ";
		cout << "YOUR ROOM HAS BEEN BOOKED SUCCESSFULLY";
		cout << "    ";
		/* Execute SQL query */
		W.exec(sql);
		W.commit();

	}
	void update()
	{
		connection C("dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
		cout << "enter the room number to update";
		cin >> room;
		cout << "    ";

		/* Create a transactional object. */
		work W(C);
		sql = "UPDATE ROOMS set ' " + cat + " ' ='" + input + "' where ID = " + room+ " ";
		/* Execute SQL query */
		W.exec(sql);
		W.commit();

	}

	void add()
	{
		connection C("dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
		cout << "enter the room number to add";
		cin >> room;
		cout << "    ";
		cout << "enter the floor";
		cin >> floor;
		cout << "    ";
		cout << "enter the price";
		cin >> price;
		cout << "    ";
		cout << "enter the date";
		cin >> date;
		cout << "    ";
		cout << "enter the type";
		cin >> type;
		cout << "    ";
		sql = "INSERT INTO ROOMS (r_no, floor, price, date, type) "
			"VALUES (" + room + ", ' " + floor + " ', " + price + ", ' " + date + " ', ' " + type + " '); ";

		/* Create a transactional object. */
		work W(C);

		/* Execute SQL query */
		W.exec(sql);
		W.commit();

	}

};


     int main()
{
		 hotel p;
	string  user_name, ps_word,choice ;
	cout << "enter the user name  :" << endl;
	cin >> user_name;
	cout << "enter the password  :" << endl;
		cin>> ps_word;
		cout << "    ";

	if (((user_name == "Mark") && (ps_word == "MARK.2")) || ((user_name == "David") && (ps_word == "DAVID.2")) || ((user_name == "John") && (ps_word == "JOHN.2")))
	{

		try {
			connection C("dbname = student user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432");
			if (C.is_open()) {
				cout << "Opened database successfully: " << C.dbname() << endl;
				cout << "   " << endl;
			}

			else {
				cout << "Can't open database" << endl;
				return 1;

			}

			p.display();
			p.search();

			do {
				cout << "--------------------------------------------------------" << endl;
				cout << "OPERATIONS :- " << endl;
				cout << "--------------------------------------------------------" << endl;
				cout << "a).book a room :\nb).search a room\nc).update\nd).add a room\ne).display list " << endl;
				cout << " ";
				cin >> choice;
				if ((choice == "a")|| (choice == "A"))
				{
					p.bookroom();

					p.display();

					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}

				else if ((choice == "b")|| (choice == "B"))
				{
					p.search();
					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}

				else if ((choice == "c")|| (choice == "C"))
				{
					p.update();
					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}

				else if ((choice == "d")|| (choice == "D"))
				{
					p.add();
					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}
				else if ((choice == "e")|| (choice == "E"))
				{
					p.display();
					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}
				else {

					cout << "wrong choice" << endl;

					cout << "do you want to continue the function:- (yes/no)" << endl;
					cin >> choice;
					cout << "   " << endl;
					cout << "   " << endl;
					cout << "   " << endl;
				}
		
			} while ((choice.compare("yes") == 0) || (choice.compare("YES") == 0));
		}
		catch (const std::exception& e) {
			cerr << e.what() << std::endl;
			return 1;
		}

	}

	else {
	cout << "wrong entry" << endl;
	cout << "Can't open database" << endl;
}

	return 0;
	}
