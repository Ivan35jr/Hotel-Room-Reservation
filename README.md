# 🏨 Hotel Del Luna - Room Reservation System

A comprehensive C++ command-line based hotel room reservation system that allows customers to book rooms and administrators to manage bookings efficiently.

## 🎯 Overview

Hotel Del Luna Room Reservation System is a console-based application developed in C++ that provides a complete solution for managing hotel room bookings. The system features two main user roles: **Administrator** and **Customer**, each with specific functionalities tailored to their needs.

### Key Highlights
- 🔐 Secure authentication system for both admins and customers
- 🛏️ Multiple room types with different pricing
- 💰 Automatic cost calculation
- 📊 Comprehensive booking management
- 👥 Multi-user support with unique identification

## ✨ Features

### 👑 Admin Features
- **Room Booking** - Book rooms on behalf of customers
- **Search Bookings** - Search and display customer booking information by name
- **View All Bookings** - Display all bookings in the system
- **Update Bookings** - Modify existing booking details
- **Delete Bookings** - Remove bookings from the system
- **Secure Admin Login** - Password-protected admin access

### 👤 Customer Features
- **User Registration** - Automatic registration during first booking
- **Secure Login** - Username and password authentication
- **Room Booking** - Book rooms with personal information
- **View Bookings** - Display personal booking history
- **View Personal Info** - Display account information
- **Multiple Bookings** - Customers can make multiple bookings (with confirmation)

## 📥 How to Run
### 1. Windows
**Clone the repository**
git clone https://github.com/yourusername/hotel-del-luna.git
cd hotel-del-luna

**Compile the program**
g++ Hotel.cpp -o Hotel.exe

**Run the program**
./Hotel.exe

### 2. Linux/Mac
**Clone the repository**
git clone https://github.com/yourusername/hotel-del-luna.git
cd hotel-del-luna

**Compile the program**
g++ Hotel.cpp -o hotel

**Run the program**
./hotel

## For Administrators
Default Admin Password: 123
1. Select option '1' from main menu
2. Enter admin password

## For Customers
**1. First-time Booking (Auto-registration)**
- Select option '2' from main menu
- Enter username and password (new account will be created)
- Choose "Book Room" option
- Enter personal details (password, phone number)
- Select room type and duration
- System auto-generates room number and calculates total cost

**2. Returning Customer**
- Select option '2' from main menu
- Login with existing username and password
- Access your bookings and personal information

## Data Storage - Customer.txt format
Username,Password,PhoneNumber,RoomType,Days,RoomNumber,TotalCost
