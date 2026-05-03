#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <limits>
#include <ios>
#include <algorithm>
#include <cstring>
#include <windows.h>

using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Color definitions
#define RESET   7
#define RED     12
#define GREEN   10
#define YELLOW  14
#define BLUE    9
#define CYAN    11
#define WHITE   15
#define MAGENTA 13

void vline(int);
void vline(int, char);
void printHeader(string);
void printDivider(char = '=', int = 50);
void getDataForCustomer(string file, string loggedInUser);
void getDataForAdmin(string file);
int countCustomerBookings(string username, string password);
int login();
bool searchName(string);
bool searchPw(char*);
bool searchNameAndPassword(string, string); 
int main();

void vline(int n) {
    for (int i = 0; i < n; i++)
        cout << "=";
    cout << endl;
}

void vline(int n, char ch) {
    for (int i = 0; i < n; i++)
        cout << ch;
    cout << endl;
}

void printHeader(string title) {
    int boxWidth = 51;  
    int titleLength = title.length();
    int paddingTotal = boxWidth - titleLength - 3;  
    int leftPadding = paddingTotal / 2;
    int rightPadding = paddingTotal - leftPadding;
    
    setColor(CYAN);
    cout << "\n\n\t\t\t\t   +" << string(boxWidth - 2, '-') << "+\n";
    cout << "\t\t\t\t   |";
    setColor(YELLOW);
    cout << string(leftPadding, ' ') << title << string(rightPadding, ' ');
    setColor(CYAN);
    cout << "|\n";
    cout << "\t\t\t\t   +" << string(boxWidth - 2, '-') << "+\n";
    setColor(RESET);
}

void printDivider(char ch, int n) {
    setColor(CYAN);
    for (int i = 0; i < n; i++) cout << ch;
    setColor(RESET);
    cout << endl;
}


struct Room {
	int room;
	char roomtype[50];
	float cost;
	int day;
	int roomNum;

public:
	void showRoom() {
		Room single = { 1, "Single Bedroom", 150.50 }, 
			doubles = { 2, "Double Bedroom", 240.20 }, 
			family = { 3, "Family Bedroom", 300.50 };
		
		setColor(CYAN);
		cout << "\n\n\t\t\t\t      +-------------------------------------------------+\n";
		cout << "\t\t\t\t      |                ROOM INFORMATION                 |\n";
		cout << "\t\t\t\t      +-------------------------------------------------+\n\n";
		
		setColor(WHITE);
		cout << "\t\t\t\t  +-------------------------------------------------+\n";
		cout << "\t\t\t\t  |                                                 |\n";
		cout << "\t\t\t\t  |     No    Room Type              Cost (RM)      |\n";
		cout << "\t\t\t\t  |     ---   ----------             --------       |\n";
		
		setColor(YELLOW);
		cout << "\t\t\t\t  |      1    " << left << setw(25) << single.roomtype 
			<< setprecision(2) << fixed << single.cost << "       |\n";
		
		setColor(GREEN);
		cout << "\t\t\t\t  |      2    " << left << setw(25) << doubles.roomtype 
			<< setprecision(2) << fixed << doubles.cost << "       |\n";
		
		setColor(MAGENTA);
		cout << "\t\t\t\t  |      3    " << left << setw(25) << family.roomtype 
			<< setprecision(2) << fixed << family.cost << "       |\n";
		
		setColor(WHITE);
		cout << "\t\t\t\t  +-------------------------------------------------+\n";
		setColor(RESET);
	}

}single = { 1, "Single Bedroom", 150.50 }, doubles = { 2, "Double Bedroom", 240.20 }, family = { 3, "Family Bedroom", 300.50 };

struct Admin {
	Room r;
	char phone_no[12], pw[20];
	string name;
	string type, file;

	void bookRoom() {
		file = "customer.txt";
		system("cls");
		r.showRoom();
		getDataForAdmin(file);
	};

	void searchBooking(string user) {
		system("cls");
		printHeader("SEARCH BOOKING INFORMATION");

		ifstream admin;
		admin.open("customer.txt", ios::in);
		if (!admin) {
			setColor(RED);
            cout << "\n\t\t\t\t\t   X File cannot be opened!\n";
            setColor(RESET);
			return;
		}
		else {
			string line;
			bool found = false;
			int bookingCount = 0;
			
			while (getline(admin, line)) {
				stringstream ss(line);
				string name, pw, phone, room, day, roomNum, cost;
				getline(ss, name, ',');
				getline(ss, pw, ',');
				getline(ss, phone, ',');
				getline(ss, room, ',');
				getline(ss, day, ',');
				getline(ss, roomNum, ',');
				getline(ss, cost, ',');
				
				if (user == name) {
					if (!found) {
						found = true;
						setColor(CYAN);
                        cout << "\n\t\t\t\t\t   +-------------------------------------------------+\n";
                        cout << "\t\t\t\t\t   |                BOOKING DETAILS                  |\n";
                        cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
                        setColor(RESET);
					}
					
					bookingCount++;
					setColor(YELLOW);
                    cout << "\n\t\t\t\t\t   =========== Booking #" << bookingCount << " ===========\n";
                    setColor(WHITE);
                    cout << "\t\t\t\t\t   | Username    : " << name << endl;
                    cout << "\t\t\t\t\t   | Password    : " << pw << endl;
                    cout << "\t\t\t\t\t   | Phone       : " << phone << endl;
					
					if (room == "1") {
						type = single.roomtype;
						setColor(GREEN);
					}
					else if (room == "2") {
						type = doubles.roomtype;
						setColor(YELLOW);
					}
					else {
						type = family.roomtype;
						setColor(MAGENTA);
					}
					
					cout << "\t\t\t\t\t   | Room Type   : " << room << " - " << type << endl;
                    setColor(WHITE);
                    cout << "\t\t\t\t\t   | Days Stay   : " << day << endl;
                    cout << "\t\t\t\t\t   | Room Number : " << roomNum << endl;
                    setColor(GREEN);
                    cout << "\t\t\t\t\t   | Total Cost  : RM " << cost << endl;
                    setColor(RESET);
                    cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
				}
			}
			
			if (!found) {
				setColor(RED);
				cout << "\n\t\t\t\t\t   X No booking records found for: " << user << endl;
				setColor(RESET);
			} else {
				setColor(CYAN);
				cout << "\n\t\t\t\t\t   +-------------------------------------------------+\n";
                cout << "\t\t\t\t\t   |           Total Bookings Found: " << bookingCount << "                |\n";
                cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
				setColor(RESET);
			}
		}
		admin.close();
		cout << "\t\t\t\t\t   ";
		system("pause");
	};

	void viewAllBooking() {
		system("cls");
		printHeader("ALL BOOKINGS");
		
		ifstream admin;
		admin.open("customer.txt", ios::in);
		if (!admin) {
			setColor(RED);
			cout << "\n\t\t\t\t\t   X File cannot be opened!\n";
			setColor(RESET);
			return;
		}
		
		string line;
		int bookingCount = 0;
		
		setColor(CYAN);
		cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
		cout << "\t\t\t\t   |                 BOOKED ROOMS LIST                 |\n";
		cout << "\t\t\t\t   +---------------------------------------------------+\n\n";
		setColor(RESET);
		
		while (getline(admin, line)) {
			stringstream ss(line);
			string name, pass, phone, room, day, roomNum, cost;
			getline(ss, name, ',');
			getline(ss, pass, ',');
			getline(ss, phone, ',');
			getline(ss, room, ',');
			getline(ss, day, ',');
			getline(ss, roomNum, ',');
			getline(ss, cost, ',');
			
			bookingCount++;
			
			if (room == "1") type = single.roomtype;
			else if (room == "2") type = doubles.roomtype;
			else type = family.roomtype;
			
			setColor(YELLOW);
			cout << "\t\t\t\t   +---------------------------------------------------+\n";
			cout << "\t\t\t\t   | Booking #" << bookingCount << string(41 - to_string(bookingCount).length(), ' ') << "|\n";
			setColor(WHITE);
			cout << "\t\t\t\t   | Username    : " << left << setw(35) << name << "|\n";
			cout << "\t\t\t\t   | Room Type   : " << setw(35) << (room + " - " + type) << "|\n";
			cout << "\t\t\t\t   | Days Stay   : " << setw(35) << day << "|\n";
			cout << "\t\t\t\t   | Room Number : " << setw(35) << roomNum << "|\n";
			setColor(GREEN);
			cout << "\t\t\t\t   | Cost (RM)   : " << setw(35) << cost << "|\n";
			setColor(RESET);
			cout << "\t\t\t\t   +---------------------------------------------------+\n";
			cout << endl;
		}
		
		if (bookingCount == 0) {
			setColor(RED);
			cout << "\t\t\t\t\t   X No bookings found!\n";
			setColor(RESET);
		} else {
			setColor(CYAN);
			cout << "\t\t\t\t   +---------------------------------------------------+\n";
			cout << "\t\t\t\t   |                Total: " << bookingCount << " booking(s)              |\n";
			cout << "\t\t\t\t   +---------------------------------------------------+\n";
			setColor(RESET);
		}
		
		admin.close();
		// cout << "\n\t\t\t\t\t   ";
		// system("pause");
	};

	void updateBooking(string user) {
		system("cls");
		printHeader("UPDATE BOOKING");

		ifstream admin;
		ofstream temp;
		file = "temp.txt";
		admin.open("customer.txt", ios::in);
		temp.open("temp.txt", ios::out | ios::app);
		string line;
		bool found = false;

		while (getline(admin, line)) {
			stringstream ss(line);
			string name, pw, phone, room, day, roomNum, cost;
			getline(ss, name, ',');
			getline(ss, pw, ',');
			getline(ss, phone, ',');
			getline(ss, room, ',');
			getline(ss, day, ',');
			getline(ss, roomNum, ',');
			getline(ss, cost, ',');
			if (user == name) {
				found = true;
				setColor(CYAN);
                cout << "\n\t\t\t\t\t   +-------------------------------------------------+\n";
                cout << "\t\t\t\t\t   |              CURRENT BOOKING DETAILS            |\n";
                cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
                setColor(WHITE);
                cout << "\t\t\t\t\t   | Username    : " << name << endl;
                cout << "\t\t\t\t\t   | Password    : " << pw << endl;
                cout << "\t\t\t\t\t   | Phone No.   : " << phone << endl;

				if (room == "1") {
					type = single.roomtype;
				}
				else if (room == "2") {
					type = doubles.roomtype;
				}
				else {
					type = family.roomtype;
				}
				cout << "\t\t\t\t\t   | Room Type   : " << room << " - " << type << endl;
                cout << "\t\t\t\t\t   | Days Stay   : " << day << endl;
                cout << "\t\t\t\t\t   | Room Number : " << roomNum << endl;
                setColor(GREEN);
                cout << "\t\t\t\t\t   | Cost (RM)   : " << cost << endl;
                setColor(RESET);
                cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
                
                cout << "\n\t\t\t\t\t   ";
                vline(43, '-');
                cout << "\n\t\t\t\t\t   Press Enter to continue with update...";
                getDataForAdmin(file);
                setColor(GREEN);
                cout << "\n\t\t\t\t\t   * Booking Contents Modified Successfully!\n";
                setColor(RESET);
			}
			else {
				temp << name << "," << pw << "," << phone << "," << room << "," << day << "," << roomNum << "," << cost << "\n";
			}
		}
		if (!found) {
            setColor(RED);
            cout << "\n\t\t\t\t\t   X No booking found for: " << user << endl;
            setColor(RESET);
        }

		admin.close();
		temp.close();
		remove("customer.txt");
		rename("temp.txt", "customer.txt");
		system("pause");
	};

	void deleteBooking(string user) {
		system("cls");
        printHeader("DELETE BOOKING");

		ifstream admin;
		ofstream temp;
		admin.open("customer.txt", ios::in);
		temp.open("temp.txt", ios::out | ios::app);
		string line;
		bool deleted = false;

		while (getline(admin, line)) {
			stringstream ss(line);
			string name, pw, phone, room, day, roomNum, cost;
			getline(ss, name, ',');
			getline(ss, pw, ',');
			getline(ss, phone, ',');
			getline(ss, room, ',');
			getline(ss, day, ',');
			getline(ss, roomNum, ',');
			getline(ss, cost, ',');
			if (user != name) {
				temp << name << "," << pw << "," << phone << "," << room << "," << day << "," << roomNum << "," << cost << "\n";
			}
			else {
				deleted = true;
                setColor(YELLOW);
                cout << "\n\t\t\t\t\t   +-------------------------------------------------+\n";
                cout << "\t\t\t\t\t   |                 BOOKING DELETED                   |\n";
                cout << "\t\t\t\t\t   +-------------------------------------------------+\n";
                setColor(GREEN);
                cout << "\t\t\t\t\t   * Record for '" << name << "' has been deleted.\n";
                setColor(RESET);
			}
		}
		if (!deleted) {
            setColor(RED);
            cout << "\n\t\t\t\t\t   X No booking found for: " << user << endl;
            setColor(RESET);
        }

		admin.close();
		temp.close();
		remove("customer.txt");
		rename("temp.txt", "customer.txt");
		cout << endl;
		system("pause");
	};
};

struct Customer {
    Room r;
    char pw[20];
    char phone_no[12];
    string name;
    string file, type = " ";
    
    void bookRoom(string user) {  
        file = "customer.txt";
        system("cls");
        r.showRoom();
        getDataForCustomer(file, user); 
    };

    void viewBookedRoom(string user, string userPw) {
        system("cls");
        printHeader("YOUR BOOKING INFORMATION");
        
        ifstream cust;
        cust.open("customer.txt", ios::in);
        if (!cust) {
            setColor(RED);
            cout << "\n\t\t\t\t\t   X File cannot be opened!\n";
            setColor(RESET);
            return;
        }
        
        string line;
        int bookingCount = 0;
        bool hasBookings = false;
        
        while (getline(cust, line)) {
            stringstream ss(line);
            string name, pw, phone, room, day, roomNum, cost;
            getline(ss, name, ',');
            getline(ss, pw, ',');
            getline(ss, phone, ',');
            getline(ss, room, ',');
            getline(ss, day, ',');
            getline(ss, roomNum, ',');
            getline(ss, cost, ',');
            
            if (user == name && userPw == pw) {
                if (!hasBookings) {
                    hasBookings = true;
                    setColor(CYAN);
                    cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
                    cout << "\t\t\t\t   |                    BOOKINGS                       |\n";
                    cout << "\t\t\t\t   +---------------------------------------------------+\n";
                    setColor(RESET);
                }
                
                bookingCount++;
                
                setColor(YELLOW);
                cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
                cout << "\t\t\t\t   | Booking #" << bookingCount << string(40 - to_string(bookingCount).length(), ' ') << "|\n";
                setColor(WHITE);
                
                if (room == "1") {
                    type = single.roomtype;
                    setColor(GREEN);
                }
                else if (room == "2") {
                    type = doubles.roomtype;
                    setColor(YELLOW);
                }
                else {
                    type = family.roomtype;
                    setColor(MAGENTA);
                }
                
                cout << "\t\t\t\t   | Room Type   : " << room << " - " << type << string(35 - (room + " - " + type).length(), ' ') << "|\n";
                setColor(WHITE);
                cout << "\t\t\t\t   | Days Stay   : " << day << string(35 - to_string(stoi(day)).length(), ' ') << "|\n";
                cout << "\t\t\t\t   | Room Number : " << roomNum << string(35 - roomNum.length(), ' ') << "|\n";
                setColor(GREEN);
                cout << "\t\t\t\t   | Cost (RM)   : " << cost << string(35 - cost.length(), ' ') << "|\n";
                setColor(RESET);
                cout << "\t\t\t\t   +---------------------------------------------------+\n";
            }
        }
        
        if (hasBookings) {
            setColor(CYAN);
            cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
            cout << "\t\t\t\t   |               Total Bookings: " << bookingCount << string(20 - to_string(bookingCount).length(), ' ') << "|\n";
            cout << "\t\t\t\t   +---------------------------------------------------+\n";
            setColor(RESET);
        } else {
            setColor(RED);
            cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
            cout << "\t\t\t\t   |                  NO BOOKINGS FOUND                |\n";
            cout << "\t\t\t\t   +---------------------------------------------------+\n";
            setColor(RESET);
        }
        
        cust.close();
        cout << "\n\t\t\t\t\t   ";
        system("pause");
    }
    
    void viewInfo(string user, string userPw) {
        system("cls");
        printHeader("YOUR PERSONAL INFORMATION");
        
        ifstream cust;
        cust.open("customer.txt", ios::in);
        if (!cust) {
            setColor(RED);
            cout << "\n\t\t\t\t\t   X File cannot be opened!\n";
            setColor(RESET);
            return;
        }
        
        string line;
        bool found = false;
        
        setColor(CYAN);
        cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
        cout << "\t\t\t\t   |                 ACCOUNT DETAILS                   |\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n";
        setColor(RESET);
        
        while (getline(cust, line)) {
            stringstream ss(line);
            string name, pw, phone;
            getline(ss, name, ',');
            getline(ss, pw, ',');
            getline(ss, phone, ',');
            
            if (user == name && userPw == pw) {
                found = true;
                setColor(WHITE);
                cout << "\t\t\t\t   | Username     : " << left << setw(35) << name << "|\n";
                cout << "\t\t\t\t   | Password     : " << setw(35) << pw << "|\n";
                setColor(GREEN);
                cout << "\t\t\t\t   | Phone Number : " << setw(35) << phone << "|\n";
                setColor(RESET);
                break;
            }
        }
        
        if (!found) {
            setColor(RED);
            cout << "\t\t\t\t   |                                                       |\n";
            cout << "\t\t\t\t   |            NO PERSONAL INFORMATION FOUND             |\n";
            setColor(RESET);
        }
        
        setColor(CYAN);
        cout << "\t\t\t\t   +---------------------------------------------------+\n";
        setColor(RESET);
        
        cust.close();
        cout << "\n\t\t\t\t\t   ";
        system("pause");
    };
};

void adminMenu() {
	Admin a;
	char ch;
	string user;
	do {
		system("cls");
		setColor(CYAN);
        cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
        cout << "\t\t\t\t   |                   ADMIN VIEW                      |\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n";
        cout << "\t\t\t\t   |       [NO.]  |  [Function]                       |\n";
        cout << "\t\t\t\t   |        [1]   |   Book Room                       |\n";
        cout << "\t\t\t\t   |        [2]   |   Search Booking Information      |\n";
        cout << "\t\t\t\t   |        [3]   |   View All Bookings               |\n";
        cout << "\t\t\t\t   |        [4]   |   Update Bookings                 |\n";
        cout << "\t\t\t\t   |        [5]   |   Delete Booking                  |\n";
        cout << "\t\t\t\t   |        [6]   |   Exit                            |\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n\n";
        setColor(RESET);
        
        cout << "\t\t\t\t   Option> ";
		cin >> ch;
		switch (ch) {
			case '1':
				a.bookRoom();
				system("pause");
				break;
			case '2': {
				cin.ignore();
				setColor(YELLOW);
				cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
				cout << "\t\t\t\t   |                SEARCH CUSTOMER                    |\n";
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(WHITE);
				cout << "\t\t\t\t   | Enter Name to Search: ";
				getline(cin, user);
				transform(user.begin(), user.end(), user.begin(), ::toupper);
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(RESET);
				
				if (searchName(user)) {
					a.searchBooking(user);
				} else {
					setColor(RED);
					cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
					cout << "\t\t\t\t   |              BOOKING DOES NOT EXIST!              |\n";
					cout << "\t\t\t\t   +---------------------------------------------------+\n";
					setColor(RESET);
					system("pause");
				}
				break;
			}
			case '3':
				a.viewAllBooking();
				cout << "\t\t\t\t\t  ";
				system("pause");
				break;
			case '4': {
				cin.ignore();
				setColor(YELLOW);
				cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
				cout << "\t\t\t\t   |                UPDATE BOOKING                     |\n";
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(WHITE);
				cout << "\t\t\t\t   | Enter Name to Search: ";
				getline(cin, user);
				transform(user.begin(), user.end(), user.begin(), ::toupper);
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(RESET);
				
				if (searchName(user)) {
					a.updateBooking(user);
				} else {
					setColor(RED);
					cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
					cout << "\t\t\t\t   |              BOOKING DOES NOT EXIST!              |\n";
					cout << "\t\t\t\t   +---------------------------------------------------+\n";
					setColor(RESET);
					system("pause");
				}
				break;
			}
			case '5': {
				cin.ignore();
				setColor(YELLOW);
				cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
				cout << "\t\t\t\t   |                DELETE BOOKING                     |\n";
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(WHITE);
				cout << "\t\t\t\t   | Enter Name to Search: ";
				getline(cin, user);
				transform(user.begin(), user.end(), user.begin(), ::toupper);
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(RESET);
				
				if (searchName(user)) {
					a.deleteBooking(user);
				} else {
					setColor(RED);
					cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
					cout << "\t\t\t\t   |              BOOKING DOES NOT EXIST!              |\n";
					cout << "\t\t\t\t   +---------------------------------------------------+\n";
					setColor(RESET);
					system("pause");
				}
				break;
			}
			case '6':
				setColor(GREEN);
				cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
				cout << "\t\t\t\t   |              EXITING ADMIN MENU...                |\n";
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(RESET);
				break;
			default:
				setColor(RED);
				cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
				cout << "\t\t\t\t   |                 INVALID CHOICE!                   |\n";
				cout << "\t\t\t\t   +---------------------------------------------------+\n";
				setColor(RESET);
				system("pause");
				break;
			}
		} while (ch != '6');
}

void custMenu(string name, string password) {
    Customer c;
    char ch;
	int boxWidth = 51;
    do {
        system("cls");
        setColor(CYAN);
        cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
        cout << "\t\t\t\t   |                  HOTEL DEL LUNA                   |\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n";
        string welcomeMsg = "WELCOME, \"" + name + "\" !";
        int msgLength = welcomeMsg.length();
        int paddingTotal = boxWidth - msgLength - 2; 
        int leftPadding = paddingTotal / 2;
        int rightPadding = paddingTotal - leftPadding;
        
        setColor(CYAN);
        cout << "\n\n\t\t\t\t   +" << string(boxWidth - 2, '-') << "+\n";
        cout << "\t\t\t\t   |" << string(boxWidth - 2, ' ') << "|\n";
        cout << "\t\t\t\t   |";
        setColor(YELLOW);
        cout << string(leftPadding, ' ') << welcomeMsg << string(rightPadding, ' ');
        setColor(CYAN);
		cout << "|\n";
        cout << "\t\t\t\t   |" << string(boxWidth - 2, ' ') << "|\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n";
        cout << "\t\t\t\t   |       [NO.]  |  [Function]                       |\n";
        cout << "\t\t\t\t   |        [1]   |   Book Room                       |\n";
        cout << "\t\t\t\t   |        [2]   |   View Booking Information        |\n";
        cout << "\t\t\t\t   |        [3]   |   View Personal Info              |\n";
        cout << "\t\t\t\t   |        [4]   |   Exit                            |\n";
        cout << "\t\t\t\t   +---------------------------------------------------+\n\n";
        setColor(RESET);
        
        cout << "\t\t\t\t   Option> ";
        cin >> ch;
        switch (ch) {
        case '1':
            c.bookRoom(name);  
            system("pause");
            custMenu(name, password);
            break;
        case '2':
            c.viewBookedRoom(name, password);
            custMenu(name, password);
            break;
        case '3':
            c.viewInfo(name, password);
            custMenu(name, password);
            break;
        case '4':
            main();
            break;
        default:
			setColor(RED);
			cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
			cout << "\t\t\t\t   |                 INVALID CHOICE!                   |\n";
			cout << "\t\t\t\t   +---------------------------------------------------+\n";
			setColor(RESET);
            system("pause");
            break;
        }
    } while (ch != '4');
}

int main() {
    system("Color 03");
    srand(time(0));
    char ch;
    string user;
    char pw[40];
    
    do {
        system("cls");
        setColor(CYAN);
        cout << "\n\n\t\t\t   +-------------------------------------------------------+\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   |                 HOTEL DEL LUNA                        |\n";
        cout << "\t\t\t   |            ROOM RESERVATION SYSTEM                    |\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   +-------------------------------------------------------+\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   |      Welcome to our Room Reservation Service!         |\n";
        cout << "\t\t\t   |    Please choose the view to proceed next.            |\n";
        cout << "\t\t\t   |            Have a nice day to you :)                  |\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   +-------------------------------------------------------+\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   |                   [1]  Admin View                     |\n";
        cout << "\t\t\t   |                   [2]  Customer View                  |\n";
        cout << "\t\t\t   |                   [3]  Exit                           |\n";
        cout << "\t\t\t   |                                                       |\n";
        cout << "\t\t\t   +-------------------------------------------------------+\n";
        setColor(RESET);
        
        cout << "\n\t\t\t   Option> ";
        cin >> ch;
        
        switch (ch) {
        case '1':
            login();
            adminMenu();
            break;
        case '2': {
            system("cls");
            setColor(CYAN);
            cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
            cout << "\t\t\t\t   |                 CUSTOMER LOGIN                    |\n";
            cout << "\t\t\t\t   +---------------------------------------------------+\n";
            setColor(RESET);
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            setColor(WHITE);
            cout << "\t\t\t\t   | Enter Username: ";
            getline(cin, user);
            transform(user.begin(), user.end(), user.begin(), ::toupper);
            
            cout << "\t\t\t\t   | Enter Password: ";
            cin.getline(pw, 40);
            cout << "\t\t\t\t   +---------------------------------------------------+\n";
            setColor(RESET);
            
            string userPassword = string(pw);
            
            if (searchNameAndPassword(user, userPassword)) {  
                custMenu(user, userPassword);  
            } else {
                setColor(RED);
                cout << "\n\t\t\t\t   +---------------------------------------------------+\n";
                cout << "\t\t\t\t   |           INVALID USERNAME OR PASSWORD!           |\n";
                cout << "\t\t\t\t   +---------------------------------------------------+\n";
                setColor(RESET);
                system("pause");
            }
            break;
        }
        case '3':
            setColor(GREEN);
            cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
            cout << "\t\t\t\t   |      Thank You for using our Room Reservation     |\n";
            cout << "\t\t\t\t   |                   Service!                        |\n";
            cout << "\t\t\t\t   |                                                   |\n";
            cout << "\t\t\t\t   |               Have a great day!                   |\n";
            cout << "\t\t\t\t   +---------------------------------------------------+\n\n";
            setColor(RESET);
            exit(0);
        default:
            setColor(RED);
            cout << "\n\n\t\t\t\t   +---------------------------------------------------+\n";
            cout << "\t\t\t\t   |                 INVALID CHOICE!                   |\n";
            cout << "\t\t\t\t   +---------------------------------------------------+\n";
            setColor(RESET);
            system("pause");
            break;
        }
    } while (ch != '3');
    
    system("pause");
    return 0;
}

bool searchNameAndPassword(string user, string password) {
    ifstream cust;
    cust.open("customer.txt", ios::in);
    if (!cust) {
        return false;
    }
    
    string line;
    while (getline(cust, line)) {
        stringstream ss(line);
        string name, pw;
        getline(ss, name, ',');
        getline(ss, pw, ',');
        
        if (user == name && password == pw) {
            cust.close();
            return true;
        }
    }
    cust.close();
    return false;
}

void getDataForCustomer(string file, string loggedInUser) {
    Customer c;
    Room r;
    ofstream cust;
    cust.open(file, ios::out | ios::app);
    float total;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\t\t\t\t       ";
    vline(43);

    c.name = loggedInUser;
    cout << "\n\t\t\t\t\t     Username: " << c.name << endl;
    
    bool validPassword = false;
    int attempts = 3;
	string userPassword;
    
    while (attempts > 0 && !validPassword) {
        cout << "\t\t\t\t\t     Enter Password (Attempts left: " << attempts << "): ";
        cin.getline(c.pw, 20);
		userPassword = string(c.pw);
        
        ifstream verify;
        verify.open("customer.txt", ios::in);
        string line;
        while (getline(verify, line)) {
            stringstream ss(line);
            string name, pass, phone;
            getline(ss, name, ',');
            getline(ss, pass, ',');
            getline(ss, phone, ',');
            
            if (c.name == name && userPassword == pass) {
                validPassword = true;
                strcpy(c.phone_no, phone.c_str());
                break;
            }
        }
        verify.close();
        
        if (!validPassword) {
            attempts--;
            if (attempts > 0) {
                cout << "\t\t\t\t\t     Invalid password! Please try again." << endl;
            } else {
                cout << "\t\t\t\t\t     Too many failed attempts! Returning to menu." << endl;
                cout << "\t\t\t\t       ";
                vline(43);
                cust.close();
                return;
            }
        }
    }

	int bookingCount = countCustomerBookings(loggedInUser, userPassword);
    cout << "\n\t\t\t\t\t  You currently have " << bookingCount << " booking(s)" << endl;
    
    if (bookingCount > 0) {
        char choice;
        cout << "\n\t\t\t\t\t     You already have " << bookingCount << " booking(s)." << endl;
        cout << "\t\t\t\t\t     Add another booking? (Y/N): ";
        cin >> choice;
        cin.ignore(); 
        
        if (toupper(choice) != 'Y') {
            cout << "\t\t\t\t\t     Booking cancelled." << endl;
            cout << "\t\t\t\t       ";
            vline(43);
            cust.close();
            return;
        }
    }
    
    cout << "\t\t\t\t\t     Enter Days to Stay: ";
    cin >> c.r.day;
    
    do {
        cout << "\t\t\t\t\t     Enter Room Type: ";
        cin >> c.r.room;
        switch (c.r.room) {
        case 1:
            total = single.cost * c.r.day;
            break;
        case 2:
            total = doubles.cost * c.r.day;
            break;
        case 3:
            total = family.cost * c.r.day;
            break;
        default:
            cout << "\t\t\t\t\t     !!!Invalid Room Choice!!!" << endl;
            break;
        }
    } while (c.r.room > 3);
    
    c.r.roomNum = rand() % 100 + 1;
    cout << "\t\t\t\t\t     Room Number: " << c.r.roomNum << endl;
    cout << "\t\t\t\t\t     Total Cost(RM): " << setprecision(2) << fixed << total << endl;
    
    cout << "\t\t\t\t";
    cust << c.name << "," << c.pw << "," << c.phone_no << "," << c.r.room << "," << c.r.day << "," << c.r.roomNum << "," << setprecision(2) << fixed << total << "\n";
    
    bookingCount = countCustomerBookings(loggedInUser, userPassword);
    cout << "\n\t\t\t\t\t     You now have " << bookingCount << " booking(s) in total." << endl;

    cout << "\n\t\t\t\t       ";
    vline(43);
    cust.close();
}

int countCustomerBookings(string username, string password) {
    ifstream cust;
    cust.open("customer.txt", ios::in);
    
    if (!cust) {
        return 0;
    }
    
    int count = 0;
    string line;
    
    while (getline(cust, line)) {
        stringstream ss(line);
        string name, pw;
        getline(ss, name, ',');
		getline(ss, pw, ',');
        
        if (username == name && password == pw) {
            count++;
        }
    }
    
    cust.close();
    return count;
}

void getDataForAdmin(string file) {
    Customer c;
    Room r;
    ofstream cust;
    cust.open(file, ios::out | ios::app);
    float total;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\t\t\t\t       ";
    vline(43);
    
    // Admin can enter any username
    cout << "\n\t\t\t\t\t     Enter Username: ";
    getline(cin, c.name);
    transform(c.name.begin(), c.name.end(), c.name.begin(), ::toupper);
    
    cout << "\t\t\t\t\t     Enter Password: ";
    cin.getline(c.pw, 20);
    
    cout << "\t\t\t\t\t     Enter Phone Number: ";
    cin.getline(c.phone_no, 12);
    
    cout << "\t\t\t\t\t     Enter Days to Stay: ";
    cin >> c.r.day;
    
    do {
        cout << "\t\t\t\t\t     Enter Room Type: ";
        cin >> c.r.room;
        switch (c.r.room) {
        case 1:
            total = single.cost * c.r.day;
            break;
        case 2:
            total = doubles.cost * c.r.day;
            break;
        case 3:
            total = family.cost * c.r.day;
            break;
        default:
            cout << "\t\t\t\t\t     !!!Invalid Room Choice!!!" << endl;
            break;
        }
    } while (c.r.room > 3);
    
    c.r.roomNum = rand() % 100 + 1;
    cout << "\t\t\t\t\t     Room Number: " << c.r.roomNum << endl;
    cout << "\t\t\t\t\t     Total Cost(RM): " << setprecision(2) << fixed << total << endl;
    
    cout << "\t\t\t\t";
    cust << c.name << "," << c.pw << "," << c.phone_no << "," << c.r.room << "," << c.r.day << "," << c.r.roomNum << "," << setprecision(2) << fixed << total << "\n";
    
    cout << "\n\t\t\t\t       ";
    vline(43);
    cust.close();
}

bool searchName(string user) {
	Customer c;
	ifstream cust;
	string line;
	cust.open("customer.txt", ios::in);
	while (getline(cust, line)) {
		stringstream ss(line);
		string name;
		getline(ss, name, ',');
		if (user == name) {
			return true;
		}
	}
	return false;
};

bool searchPw(char* pw) {
	Customer c;
	ifstream cust;
	string line;
	cust.open("customer.txt", ios::in);
	while (getline(cust, line)) {
		stringstream ss(line);
		string name, pass;
		getline(ss, name, ',');
		getline(ss, pass, ',');
		if (pw == pass) {
			return true;
		}
	}
	return false;
};

int login() {
	system("cls");
	int i = 3;
	bool isCorrect = false;
	cout << "\n\n\t\t\t\t      * HOTEL DEL LUNA * \n";
	cout << "\t\t\t\t------------------------------\n";
	cout << "\t\t\t\t\t  ADMIN LOGIN \n";
	cout << "\t\t\t\t------------------------------\n\n";
	while ((!isCorrect) && (i > 0)) {
		string pass = "";
		cout << "\t\t\t\tEnter Password: ";
		cin >> pass;


		if (pass == "123") {
			cout << "\n\n\t\t\t\tAccess Granted!\n";
			isCorrect = true;
			cout << "\n\n\t\t\t\t";
			system("pause");
		}

		else if (pass != "123" && i > 0) {
			cout << "\n\n\t\t\t\tAccess Aborted...\n";
			cout << "\n\n\t\t\t\t### " << (--i) << " ATTEMPTS LEFT ###\n";
		}
	}
	if (!isCorrect) {
		cout << "\t\t\t\t### REACHED MAX ATTEMPTS ###\n";
		system("pause");
		main();
	}
	return 0;
}


