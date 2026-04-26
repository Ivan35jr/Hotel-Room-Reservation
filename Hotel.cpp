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

using namespace std;

void vline(int);
void getDataForCustomer(string file, string loggedInUser);
void getDataForAdmin(string file);
int countCustomerBookings(string username, string password);
int login();
bool searchName(string);
bool searchPw(char*);
bool searchNameAndPassword(string, string); 
int main();


struct Room {
	int room;
	char roomtype[50];
	float cost;
	int day;
	int roomNum;

public:
	void showRoom() {
		Room single = { 1, "Single Bedroom", 150.50 }, doubles = { 2, "Double Bedroom", 240.20 }, family = { 3, "Family Bedroom", 300.50 };
		cout << "\n\n\t\t\t\t      ------------- ROOM INFORMATION -------------\n\n";
		cout << "\t\t\t\t  _____________________________________________________\n";
		cout << "\t\t\t\t |                                                     |\n";
		cout << "\t\t\t\t |\tNo\t" << "Room Type" << "\t\tCost           |" << endl;
		cout << "\t\t\t\t |\t---\t" << "----------" << "\t\t-----          |" << endl;
		cout << "\t\t\t\t |\t1\t" << single.roomtype << "\t\t" << setprecision(2) << fixed << "RM" << single.cost << "       |\n";
		cout << "\t\t\t\t |\t2\t" << doubles.roomtype << "\t\t" << setprecision(2) << fixed << "RM" << doubles.cost << "       |\n";
		cout << "\t\t\t\t |\t3\t" << family.roomtype << "\t\t" << setprecision(2) << fixed << "RM" << family.cost << "       |\n";
		cout << "\t\t\t\t |_____________________________________________________|\n";
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
		ifstream admin;
		admin.open("customer.txt", ios::in);
		if (!admin) {
			cout << "File cannot be open" << endl;
		}
		else {
			string line;
			bool found = false;
			int bookingCount = 0;
			
			cout << "\n\n\t\t\t\t        ------ USER(S) ROOM INFORMATION ------\n\n";
			
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
					}
					
					bookingCount++;
					cout << "\t\t\t\t\t   ----- Booking #" << bookingCount << " -----" << endl;
					cout << "\t\t\t\t\t";
					vline(36);
					cout << "\t\t\t\t\t   Username: " << name << endl;
					cout << "\t\t\t\t\t   Password: " << pw << endl;
					cout << "\t\t\t\t\t   Phone Number: " << phone << endl;
					
					if (room == "1") {
						type = single.roomtype;
					}
					else if (room == "2") {
						type = doubles.roomtype;
					}
					else {
						type = family.roomtype;
					}
					
					cout << "\t\t\t\t\t   Room Type: " << room << " - " << type << endl;
					cout << "\t\t\t\t\t   Days of Stay: " << day << endl;
					cout << "\t\t\t\t\t   Room Number: " << roomNum << endl;
					cout << "\t\t\t\t\t   Cost of Stay(RM): " << cost << endl;
					cout << "\n\t\t\t\t\t";
					vline(36);
					cout << endl;
					// Don't break - continue searching for more records with same name
				}
			}
			
			if (!found) {
				cout << "\t\t\t\t\t   No booking records found for: " << user << endl;
				cout << "\t\t\t\t\t";
				vline(36);
			} else {
				cout << "\t\t\t\t\t   Total Bookings Found: " << bookingCount << endl;
				cout << "\t\t\t\t\t";
				vline(36);
			}
		}
		admin.close();
		cout << "\t\t\t\t\t   ";
		system("pause");
	};
	void viewAllBooking() {
		system("cls");
		ifstream admin;
		admin.open("customer.txt", ios::in);
		string line;
		int n = 7, m = 10;
		string** arr = new string * [m];
		for (int i = 0; i < m; i++) {
			// Declare a memory block
			// of size n
			arr[i] = new string[n];
		}
		if (!admin) {
			cout << "File cannot be open" << endl;
		}
		cout << "\n\n\t\t\t\t       ------ BOOKED ROOM INFORMATION ------";
		cout << "\n\n\t\t\t\t\t";
		vline(35);
		int i = 0;
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
			if (room == "1") {
				type = single.roomtype;
			}
			else if (room == "2") {
				type = doubles.roomtype;
			}
			else {
				type = family.roomtype;
			}

			arr[i][0] = name;
			arr[i][1] = room;
			arr[i][2] = type;
			arr[i][3] = day;
			arr[i][4] = roomNum;
			arr[i][5] = cost;
			i++;
		}
		for (int j = 0; j < i; j++) {
			cout << "\t\t\t\t\t   Username: " << arr[j][0] << endl;
			cout << "\t\t\t\t\t   Room Type: " << arr[j][1] << " - " << arr[j][2] << endl;
			cout << "\t\t\t\t\t   Days of Stay: " << arr[j][3] << endl;
			cout << "\t\t\t\t\t   Room Number: " << arr[j][4] << endl;
			cout << "\t\t\t\t\t   Cost of Stay(RM): " << arr[j][5] << endl;
			cout << "\n\t\t\t\t\t";
			vline(35);
		}
		for (int j = 0; j < i; j++)    //To delete the inner arrays
			delete[] arr[j];
		delete[] arr;
		admin.close();
	};
	void updateBooking(string user) {
		system("cls");
		ifstream admin;
		ofstream temp;
		file = "temp.txt";
		admin.open("customer.txt", ios::in);
		temp.open("temp.txt", ios::out | ios::app);
		string line;
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
				cout << "\n\n\t\t\t\t\t------ USER BOOKING INFORMATION ------\n\n";
				cout << "\t\t\t\t\t   Username: " << name << endl;
				cout << "\t\t\t\t\t   Password: " << pw << endl;
				cout << "\t\t\t\t\t   Phone Number: " << phone << endl;
				if (room == "1") {
					type = single.roomtype;
				}
				else if (room == "2") {
					type = doubles.roomtype;
				}
				else {
					type = family.roomtype;
				}
				cout << "\t\t\t\t\t   Room Type: " << room << " - " << type << endl;
				cout << "\t\t\t\t\t   Days of Stay: " << day << endl;
				cout << "\t\t\t\t\t   Room Number: " << roomNum << endl;
				cout << "\t\t\t\t\t   Cost of Stay(RM): " << cost << endl;
				cout << "\n\t\t\t\t\t--------------------------------------";
				cout << "\n\t\t\t\t\t      Press enter to continue....";
				getDataForAdmin(file); 
				cout << "\n\t\t\t\t\t     Booking Contents Modified....\n\n";
			}
			else {
				temp << name << "," << pw << "," << phone << "," << room << "," << day << "," << roomNum << "," << cost << "\n";
			}
		}
		admin.close();
		temp.close();
		remove("customer.txt");
		rename("temp.txt", "customer.txt");
		system("pause");
	};
	void deleteBooking(string user) {
		ifstream admin;
		ofstream temp;
		admin.open("customer.txt", ios::in);
		temp.open("temp.txt", ios::out | ios::app);
		string line;
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
				cout << "\n\t\tRecord deleted" << endl;
			}
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
        ifstream cust;
        cust.open("customer.txt", ios::in);
        if (!cust) {
            cout << "File cannot be open" << endl;
        }
        
        string line;
        int bookingCount = 0;
        bool hasBookings = false;
        
        cout << "\n\n\t\t\t\t       ------ YOUR BOOKING INFORMATION ------\n\n";
        
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
                    cout << "\t\t\t\t     ";
                    vline(42);
                }
                
                bookingCount++;
                cout << "\n\t\t\t\t\t   ----- Booking #" << bookingCount << " -----" << endl;
                
                if (room == "1") {
                    type = single.roomtype;
                }
                else if (room == "2") {
                    type = doubles.roomtype;
                }
                else {
                    type = family.roomtype;
                }
                
                cout << "\t\t\t\t\t   Room Type: " << room << " - " << type << endl;
                cout << "\t\t\t\t\t   Days of Stay: " << day << endl;
                cout << "\t\t\t\t\t   Room Number: " << roomNum << endl;
                cout << "\t\t\t\t\t   Cost of Stay(RM): " << cost << endl;
            }
        }
        
        if (hasBookings) {
            cout << "\n\t\t\t\t\t   -------------------------" << endl;
            cout << "\t\t\t\t\t   Total Bookings: " << bookingCount << endl;
            cout << "\n\t\t\t\t     ";
            vline(42);
        } else {
            cout << "\t\t\t\t\t   No bookings found." << endl;
            cout << "\t\t\t\t     ";
            vline(42);
        }
        
        cust.close();
    }
	void viewInfo(string user, string userPw) {
		system("cls");
		ifstream cust;
		cust.open("customer.txt", ios::in);
		if (!cust) {
			cout << "File cannot be open" << endl;
		}
		string line;
		bool found = false;
		while (getline(cust, line)) {
			stringstream ss(line);
			string name, pw, phone;
			getline(ss, name, ',');
			getline(ss, pw, ',');
			getline(ss, phone, ',');
			if (user == name && userPw == pw) {
				cout << "\n\n\t\t\t\t       ------ USER PERSONAL INFORMATION ------\n\n";
				cout << "\t\t\t\t      ";
				vline(41);
				cout << "\n\t\t\t\t\t     Username: " << name << endl;
				cout << "\t\t\t\t\t     Password: " << pw << endl;
				cout << "\t\t\t\t\t     Phone Number: " << phone << "\n\n";
				cout << "\t\t\t\t      ";
				vline(41);
				break;
			}
		}

		if (!found) {
			cout << "\n\t\t\t\t      No personal information found." << endl;
		}
		cust.close();
	};
};



void adminMenu() {
	Admin a;
	char ch;
	string user;
	do {
		system("cls");
		cout << "\n\n\t\t\t\t ___________________ ADMIN VIEW ___________________\n";
		cout << "\t\t\t\t|                                                  |\n";
		cout << "\t\t\t\t|       [NO.]  |  [Function]                       |\n";
		cout << "\t\t\t\t|        [1]   |   Book Room                       |\n";
		cout << "\t\t\t\t|        [2]   |   Search Booking Information      |\n";
		cout << "\t\t\t\t|        [3]   |   View All Bookings               |\n";
		cout << "\t\t\t\t|        [4]   |   Update Bookings                 |\n";
		cout << "\t\t\t\t|        [5]   |   Delete Booking                  |\n";
		cout << "\t\t\t\t|        [6]   |   Exit                            |\n";
		cout << "\t\t\t\t|__________________________________________________|\n\n";
		cout << "\t\t\t\t\t\tOption> ";
		cin >> ch;
		switch (ch) {
		case '1':
			a.bookRoom();
			cout << "\t\t\t\t\t    ";
			system("pause");
			break;
		case '2':
			cin.ignore();
			cout << "\n\t\tEnter the Name to Search: ";
			getline(cin, user);
			transform(user.begin(), user.end(), user.begin(), ::toupper);
			if (searchName(user)) {
				a.searchBooking(user);
			}
			else {
				cout << "\n\t\tBooking Do Not Exist." << endl;
				cout << "\n\t\t";
				system("pause");
			}
			break;

		case '3':
			a.viewAllBooking();
			cout << "\t\t\t\t\t  ";
			system("pause");
			break;

		case '4':
			cin.ignore();
			cout << "\n\t\tEnter the Name to Search: ";
			getline(cin, user);
			transform(user.begin(), user.end(), user.begin(), ::toupper);
			if (searchName(user)) {
				a.updateBooking(user);
			}
			else {
				cout << "\n\t\tBooking Do Not Exist." << endl;
				cout << "\n\t\t";
				system("pause");
			}
			break;

		case '5':
			cin.ignore();
			cout << "\n\t\tEnter the Name to Search: ";
			getline(cin, user);
			transform(user.begin(), user.end(), user.begin(), ::toupper);
			if (searchName(user)) {
				a.deleteBooking(user);
			}
			else {
				cout << "\n\t\tBooking Do Not Exist." << endl;
				cout << "\n\t\t";
				system("pause");
			}
			break;
		case '6':
			break;
		default:
			cout << "\n\n\t\t\t\t\t       Invalid Choices...." << endl;
			cout << "\n\t\t\t\t\t   ";
			system("pause");
			break;
		}
	} while (ch != '6');
}

void custMenu(string name, string password) {
    Customer c;
    char ch;
    do {
        system("cls");
        cout << "\n\n\t\t\t\t\t    @@@@@@ HOTEL DEL LUNA @@@@@@";
        cout << "\n\n\t\t\t\t>> WELCOME, \"" << name << "\" !" << endl;
        cout << "\t\t\t\t __________________________________________________\n";
        cout << "\t\t\t\t|                                                  |\n";
        cout << "\t\t\t\t|       [NO.]  |  [Function]                       |\n";
        cout << "\t\t\t\t|        [1]   |   Book Room                       |\n";
        cout << "\t\t\t\t|        [2]   |   View Booking Information        |\n";
        cout << "\t\t\t\t|        [3]   |   View Personal Info              |\n";
        cout << "\t\t\t\t|        [4]   |   Exit                            |\n";
        cout << "\t\t\t\t|__________________________________________________|\n\n";
        cout << "\t\t\t\t\t\tOption> ";
        cin >> ch;
        switch (ch) {
        case '1':
            c.bookRoom(name);  
            system("pause");
            custMenu(name, password);
            break;
        case '2':
            c.viewBookedRoom(name, password);
            cout << "\t\t\t\t\t   ";
            system("pause");
            custMenu(name, password);
            break;
        case '3':
            c.viewInfo(name, password);
            cout << "\t\t\t\t\t   ";
            system("pause");
            custMenu(name, password);
            break;
        case '4':
            main();
            break;
        default:
            cout << "\n\n\t\t\t\t\t\tInvalid Choices" << endl;
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
		cout << "\n\n\t\t\t@@@@@@@@@@@@@@@@@@@@@@ HOTEL DEL LUNA @@@@@@@@@@@@@@@@@@@@@@@\n";
		cout << "\t\t\t@                                                           @\n";
		cout << "\t\t\t@                                                           @\n";
		cout << "\t\t\t@        Welcome to use our Room Reservation Service,       @\n";
		cout << "\t\t\t@          Please choose the view to proceed next.          @\n";
		cout << "\t\t\t@                  Have a nice day to you :)                @\n";
		cout << "\t\t\t@                                                           @\n";
		cout << "\t\t\t@                 -------------------------                 @\n";
		cout << "\t\t\t@                   | 1 |  Admin View                       @\n";
		cout << "\t\t\t@                   | 2 |  Customer View                    @\n";
		cout << "\t\t\t@                   | 3 |  Exit                             @\n";
		cout << "\t\t\t@                 -------------------------                 @\n";
		cout << "\t\t\t@                                                           @\n";
		cout << "\t\t\t@                                                           @\n";
		cout << "\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
		cout << "\n\t\t\t                        Option> ";
		cin >> ch;
		switch (ch) {
		case '1':
			login();
			adminMenu();
			break;
		case '2': {
			system("cls");
			cout << "\n\n\t\t\t\t      * HOTEL DEL LUNA * \n";
			cout << "\t\t\t\t------------------------------\n";
			cout << "\t\t\t\t\tCUSTOMER LOGIN \n";
			cout << "\t\t\t\t------------------------------\n\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t\tEnter Username: ";
			getline(cin, user);
			transform(user.begin(), user.end(), user.begin(), ::toupper);
			cout << "\n\t\t\t\tEnter Password: ";
			cin.getline(pw, 40);
			string userPassword = string(pw);
			if (searchNameAndPassword(user, userPassword)) {  
				custMenu(user, userPassword);  
			}
			else {
				cout << "\n\t\t\t\tInvalid Username or Password...\n\n";
				system("pause");
			}
			break;
		}
		case '3':
			cout << "\n\n\t\t\t\tThank You for using our Room Reservation Service!\n\n";
			exit(0);
		default:
			cout << "\n\n\t\t\t\t\t       Invalid Choices..." << endl;
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

    // int bookingCount = countCustomerBookings(loggedInUser);
    // cout << "\n\t\t\t\t\t  You currently have " << bookingCount << " booking(s)" << endl;
    
    // Auto-use logged-in username
    c.name = loggedInUser;
    cout << "\n\t\t\t\t\t     Username: " << c.name << endl;
    
    bool validPassword = false;
    int attempts = 3;
	string userPassword;
    
    while (attempts > 0 && !validPassword) {
        cout << "\t\t\t\t\t     Enter Password (Attempts left: " << attempts << "): ";
        cin.getline(c.pw, 20);
		userPassword = string(c.pw);
        
        // Check if password matches existing record
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
                // Copy phone number from existing record
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
    
    // If customer already has a booking, ask if they want to add another
    if (bookingCount > 0) {
        char choice;
        cout << "\n\t\t\t\t\t     You already have " << bookingCount << " booking(s)." << endl;
        cout << "\t\t\t\t\t     Add another booking? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear newline
        
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
        return 0; // File doesn't exist yet
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

//draw border line
void vline(int n) {
	for (int i = 0; i < n; i++)
		cout << "=";
	cout << endl;
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


