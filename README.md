# Self Food Project (C++)
## Student Information
Name: Mahan Panahi
Student Number: 140416082002
## Project Description
1️⃣ Project Objective
This project was developed as the final project of the first semester for the Fundamentals of Computer Programming course in the Computer Engineering program.
The main purpose of this project is to apply the basic programming concepts learned during the course in a practical and meaningful way.
Instead of working on isolated exercises, I designed a complete console-based system that simulates a student food reservation environment.
Through this project, I focused on understanding core C++ concepts such as arrays, functions, loops, conditional statements, and file handling, while keeping the implementation simple, readable, and suitable for a first-semester project.

2️⃣ Program Functionality
The program simulates a simple university food reservation system with two main roles: Admin and Student.
Key functionalities include:
Student authentication and account management
Admin management of students and food menus
Food reservation for different days and meal types (breakfast, lunch, dinner)
Automatic balance updates after reservations
Persistent data storage using text files (users, foods, and reservations)
Viewing reservation history
Saving personal reservation reports to TXT files
Generating simple text-based QR codes for reservations
Colored console output to improve user interaction and clarity
I tried to keep everything simple using only the C++ basics we learned this semester—no fancy libraries or magic!

3️⃣ Menu Description
🔹 login menu 
includes admin login, student login, and logout
if the password and username are entered correctly, it will show whether the user is an admin or not.

🔹 Admin Menu
The admin panel allows full control over the system.
Through this menu, the admin can:
Add, delete, and edit student accounts
Manage food items and prices for each day and meal
View food menus
Monitor daily reservations

🔹 User Menu
The user menu is designed for students and focuses on simplicity.
Using this menu, a student can:
View food menus
Reserve meals
Check previous reservations
Increase account balance
Change password
Save reservations to a personal TXT file
View text-based QR codes for reservations
## Files
- food_site.cpp
The main source file of the project.
This file contains the complete implementation of the food reservation system, including menus, user authentication, admin and user roles, and file handling logic.

- food_site.exe
The compiled executable version of the program.
This file allows the program to be run directly without recompiling the source code.

.vscode/
Configuration files used by Visual Studio Code for running and debugging the project during development.
This folder is not required for running the program but is included for development purposes.

Text files (generated at runtime)
Files such as user data, food lists, and reservation records are automatically created by the program when it is executed for the first time.
These files are not required to be present beforehand and will be generated based on program usage.

.gitignore
Specifies files and folders that should not be tracked by Git.

- README.md
Contains project documentation, including project description, functionality, file structure, and execution instructions.
## How to Run
Compile and run:
```bash
g++ food_site.cpp -o food
./food