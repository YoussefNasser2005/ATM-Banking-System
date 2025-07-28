🏧 ATM Banking System – C++ Console Project
📋 Description
A simple ATM Banking System written in C++ that runs in the terminal.
The system allows users to log in using an account number and PIN, then perform various banking operations such as:

💵 Quick Withdraw

💸 Normal Withdraw

💰 Deposit

📊 Check Balance

🔐 Logout

Client data is stored in a text file Clients.txt, and is automatically updated upon each transaction.

🛠 Features
Login System with account number and PIN.

Quick Withdraw with preset amounts.

Normal Withdraw with custom amount (multiples of 5).

Deposit with user-defined amount.

Check Balance to view current balance.

File Storage: Uses Clients.txt to store and update client data.

Clean UI using terminal screens and menus.

Data persistence through file reading/writing.

📁 File Structure
main.cpp → Main source code file.

Clients.txt → Stores client data in format:
AccountNumber//Name//PinCode//Phone//Balance

Example:

cpp
Copy
Edit
1234//John Doe//1111//0100000000//20000
5678//Jane Smith//2222//0123456789//50000
✅ How to Run
Compile the code
Using g++:

bash
Copy
Edit
g++ main.cpp -o ATM
Run the executable

bash
Copy
Edit
./ATM
Login with a valid account number and PIN from Clients.txt.

🧠 Code Structure Highlights
struct sClient – stores individual client data.

Login() – prompts for login and validates user.

MainMenu() – displays main banking menu.

QuickWithDrawMainMenu() – quick withdraw options.

HandleTransaction() – processes deposit and normal withdrawal.

SaveClientsDataToFile() – updates file after each transaction.

📌 Requirements
C++ compiler (e.g., g++, MSVC)

C++11 or higher

A Clients.txt file in the same directory

📞 Contact
Made by [Youssef Nasser] – For learning purposes.
