// Mahan Panahi
// food site

#include<iostream>
#include <fstream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
const int MAX_USERS = 1000;
const int MAX_FOODS = 20;
string usernames [MAX_USERS] = {};
string passwords [MAX_USERS] = {};
long long student_number [MAX_USERS] = {};
long long user_balance [MAX_USERS] = {};
string food_names [21][MAX_FOODS] = {}; //هر سطر برای یک روز از هفته و هر ستون برای یک غذا
int food_prices [21][MAX_FOODS] = {};
int food_ID [21][MAX_FOODS] = {};
string users_reservations [21][MAX_USERS] = {};
int user_count = 0;
int food_count[21] = {};




void add_student(string username, long long studentN, long long balance);
int check_user(long long studentN);
void remove_user(long long studentN);
void edit_user(long long studentN);
bool login(string username, string password);
//=======================food==========================
void add_food(string foodN, int price, int foodID, int day);
void remove_food(int foodID);
void edit_food(int foodID, string new_food, int new_price);
void show_foods(int day, string meal);
int meal_to_int(string meal);
//==================search food and QR=====================
void search_food();
void generate_qr(int user_index);
void save_my_reservations(int user_index);
//======================User reservations===========================
void user_reservation(int user_index);
//======================save and load from txt===========================
void save_users_file();
void load_users_file();
void save_foods_file();
void load_foods_file();
void save_reservations_file();
void load_reservations_file();
int find_user_index_by_student_number(long long studentN);
//======================قابلیت های ویژه ادمین===========================
void show_reservations_sorted();
void most_popular_food();
void income_and_refunds();
void top_reserving_students();
//======================show users===========================
void show_user_and_pas()
{
    cout << "  username  |  password  |  student number  |  balance" << endl;
    cout<<"\033[31m-----------------------------------------\033[0m"<<endl;
    for (int i = 0; i < user_count; i++)
    {
        if (usernames[i] == "")
            break;
        cout << i << ")" << usernames[i] << "  " << passwords[i] << "  " << student_number[i] << "  " << user_balance[i] << endl;
        cout<<"\033[31m-----------------------------------------\033[0m"<<endl;
    }
}


// admin username: admin
// admin password: admin_1234


//======================Main===========================
int main() {

//***********load txts**********
    load_users_file();
    load_foods_file();
    load_reservations_file();


    srand(time(0));
    cout << "Welcome to the Food Site!" << endl;
    cout << "\n1) Log in as admin\n2) Log in as user\n0) Exit" << endl;
    int logchoice;
    cin >> logchoice; //فقط برای انتخاب در صفحه لاگین
    string user, pas;
            switch(logchoice){
                case 1:{
                    cout << "\nPlease enter your username: \033[1;34m";
                    cin >> user;
                    cout<<"\033[0m\nPlease enter your password: \033[1;34m";
                    cin >> pas;
                    cout<<"\033[0m";
                    break;
                }
                case 2:{
                    cout << "\nPlease enter your username: \033[1;34m";
                    cin >> user;
                    cout<<"\033[0m\nPlease enter your password: \033[1;34m";
                    cin >> pas;
                    cout<<"\033[0m";
                    break;
                }
                case 0:{
                    cout << "\033[1;31mExiting the program. Goodbye!\033[0m" << endl;
                    return 0;
                }
                default:{
                    cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
                    cout << "1) Log in as admin      2) Log in as user      3) Exit" << endl;
                    cin >> logchoice;
            }
        }

//==================Admin Pannel=====================
if (user == "admin"  && pas == "admin_1234") {
    system("cls");
    cout << "\033[4;34m Access granted. Welcome, admin!\033[0m" << endl;
    cout << endl;
    while (true){
        cout << "1) Add a new student\n2) Delete a student\n3) Edit student information\n4) students List"
			<<"\n5) Add food\n6) Delete food\n7) Edit food information\n8) Food Lists"
			<<"\n9) View the list of reservations for a specific day\n10) Management reports\n0) Exit" << endl;
        cout << "choose: ";
        int admin_choice; //برای منوی ادمین
        cin >> admin_choice;
    
        switch (admin_choice){
            case 1: {
                // add new student
                cout <<"Enter the student number of the new user: ";
                long long studentN;
                long long balance;
                cin>>studentN;
                cin.ignore();
                string new_username;
                cout << "Enter the username of the new user: ";
                cin>>new_username;
                cin.ignore();
                cout << "Enter the student Balance of the new user: ";
                cin>>balance;
                cin.ignore();
                add_student( new_username, studentN, balance);
                save_users_file();
                cout<<"\033[3;32mNew user added successfully!"<<endl;
                cout<<"Default password is set to\033[0m \033[42m'1234new'\033[0m"<<endl;
                cout << "=========================================" << endl;
                show_user_and_pas();
                break;
            }
            case 2: {
                // delete student
                show_user_and_pas();
                cout << endl;
                cout << "Select the student number you want to delete: " << endl;
                long long studentN;
                cin >> studentN;
                cin.ignore();
                remove_user(studentN);
                save_users_file();
                cout << "\033[2;31mUser number \033[0m" << studentN << "\033[2;31m was successfully deleted.\033[0m" << endl;
                cout<<"Updated user list: "<<endl;
                show_user_and_pas();
                break;
            }
            case 3: {
                // edit student info
                show_user_and_pas();
                cout << "Select the student number you want to edited: " << endl;
                long long studentN;
                cin >> studentN;
                edit_user(studentN);
                save_users_file();
                break;
            }
            case 4: {
                // show students list
                show_user_and_pas();
                cout<<endl;
                break;
            }
            case 5: {
                // add food
                string foodN, meal;
                int price;
                int randomID = rand() % 9000 + 1000; // Generate a random food ID between 1000 and 9999
                int day;
                cout << "Enter the day of the week to add food (1: Saturday, ..., 7: Friday): ";
                cin >> day;
                if (day < 1 || day > 7) {
                    cout << "Invalid day selection!" << endl;
                    break;
                }
                if (food_count[day - 1] >= MAX_FOODS) {
                    cout << "Cannot add more foods for this day!" << endl;
                    break;
                }
                cout << "Enter breakfast or lunch or dinner: ";
                cin >> meal;
                cout << "Enter the name of the new food: ";
                cin.ignore();
                getline(cin, foodN);
                cout << "Enter the price of the new food: ";
                cin >> price;
                add_food(foodN, price, randomID, day);
                save_foods_file();
                cout << "New food added successfully!" << endl;
                show_foods(day, meal);
                cout << "\n=========================================================" << endl;
                break;
            }
            case 6: {
                // delete food
                cout << "\n=========================================" << endl;
                cout << "Select the food ID you want to delete: " << endl;
                int foodID;
                cin >> foodID;
                remove_food(foodID);
                save_foods_file();
                        break;
            }
            case 7: {
                // edit food
                cout << "\n=========================================" << endl;
                cout << "Select the food ID you want to edit: " << endl;
                int foodID;
                cin >> foodID;
                cout << "Select the new food name: \033[33m" << endl;
                string newfood;
                cin.ignore();
                getline(cin, newfood);
                cout << "\033[0mSelect the new food price: \033[33m" << endl;
                int newprice;
                cin >> newprice;
                cout<<"\033[0m";
                edit_food(foodID, newfood, newprice);
                save_foods_file();
                break;
            }
            case 8: {
                // show foods list
                int day;
                string meal;
                cout << "Enter day to show foods: ";
                cin >> day;
                cout << "enter breakfast or lunch or dinner: ";
                cin >> meal;
                show_foods(day, meal);
                break;
            }
            case 9: {
                // view reservations a day
                int day;
                cout << "Enter the day of the week to view reservations (1: Saturday, 2: Sunday, 3: Monday, 4: Tuesday, 5: Wednesday, 6: Thursday, 7: Friday): ";
                cin >> day;
                if (day < 1 || day > 7)
                {
                    cout << "Invalid day selection!" << endl;
                    break;
                }
                cout << "\nReservations for day " << day << ":\n";
                for (int meal = 0; meal < 3; meal++)
                {
                    int row = (day - 1) + meal * 7;
                    if (meal == 0) cout << "\n--- Breakfast ---\n";
                    else if (meal == 1) cout << "\n--- Lunch ---\n";
                    else cout << "\n--- Dinner ---\n";
                    bool found = false;
                    for (int i = 0; i < user_count; i++)
                    {
                        if (users_reservations[row][i] != "")
                        {
                            cout << "User: " << usernames[i]
                                << " | Food: " << users_reservations[row][i] << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No reservations.\n";
                }
                break;
            }
            case 10: {
                system("cls");
                // management reports
                int adminChoice2;
                while(true)
                {
                    cout << "1) Sorting the reservation list by registration time" << endl;
                    cout << "2) The most popular food" << endl;
                    cout << "3) Total income and total refunds" << endl;
                    cout << "4) Students with the most reservations" << endl;
                    cout << "0) Exit" << endl;
                    cout << "choose: ";
                    cin.ignore();
                    cin >> adminChoice2;
                    switch(adminChoice2)
                    {
                        // void show_reservations_sorted();
                        // void most_popular_food();
                        // void income_and_refunds();
                        // void top_reserving_students();
                        case 1:{
                            show_reservations_sorted();
                            break;
                        }
                        case 2:{
                            most_popular_food();
                            break;
                        }
                        case 3:{
                            income_and_refunds();
                            break;
                        }
                        case 4:{
                            top_reserving_students();
                            break;
                        }
                        case 0:{
                            break;
                        }
                        default:{
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                        }
                    }//end switch management reports
                    if (adminChoice2 == 0)
                        break;
                }//end while for management reports
            }//end case 10
            case 0: {
                cout << "\033[1;31mExiting the program. Goodbye!\033[0m" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        if (admin_choice == 0) 
            break;
        } //end switch admin pannel
    }//end while admin pannel
} //if --> admin pannel

else if (login(user,pas)) {
    int user_index = -1;
    system("cls");
    cout << "\033[7;36mLogin successful! Welcome, " << user << "!\033[0m" << endl;
    
    if (pas == "Aa@123456")
    {
        //==================تغییر اجباری رمز عبور=====================
        cout << "\033[1;3;33mUser " << user << " your default password is " << pas << " you need to change it:\033[0m" << endl;
        cout<< "please enter your new password: " ;

    //======================پیدا کردن اندیس کاربر========================

    for (int i = 0; i < user_count; i++)
    {
        if (usernames[i] == user)
        {
            user_index = i;
            break;
        }
    }

if (user_index == -1) {
    cout << "User index error!" << endl;
    return 0;
}

    //======================================================================
        string new_password;
        while (true){
            cin >> new_password;
            if (new_password == pas){
                cout << "The password cannot be the primary password!\nTry again: ";
                continue;
            }
            passwords[user_index] = new_password;
            save_users_file();
            cout << "\033[3;32mPassword changed successfully!\033[0m" << endl;
            break;
        }//end while تغییر رمز عبور
    }//end if
    
    while (true){
        cout << "\033[1;3;32m1) show foods list\n2) Food reservation\n3) View previous reservations"
            << "\n4) Increase in inventory\n5) Change password\n6) Save my reservations to TXT\n"
            << "7) Show QR codes for reservations\n0) Exit\033[0m" << endl;
    int user_choice;    //برای منوی کاربر
        cout << "choose: ";
    cin >> user_choice;

        switch (user_choice){
            case 1: {
                // show foods list
                int day;
                string meal;
                cout << "Enter day to show foods: ";
                cin >> day;
                cout << "enter breakfast or lunch or dinner: ";
                cin >> meal;
                show_foods(day, meal);
                break;
            }
            case 2: {
                // food_reservation();
                user_reservation(user_index);
                cout << "Your current balance is: " << user_balance[user_index] << endl;
                cout << "Do you want your reservations to be saved in a text file? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                    save_my_reservations(user_index);
                cout << "Do you want to generate a QR code for your reservations? (y/n): ";
                char qr_choice;
                cin >> qr_choice;
                if (qr_choice == 'y' || qr_choice == 'Y')
                    generate_qr(user_index);
                break;
            }
            case 3: {
                // view_previous_reservations();
                long long student_Num;
                cout << "enter your student number: ";
                cin >> student_Num;
                int userIndex = check_user(student_Num);
                for (int i = 0; i < 21; i++)
                {
                    // if (i >= 0 && i < 7)
                    //     cout << "**********Breakfasts reservations**********" << endl;
                    // if ( i >=7 && i < 14)
                    //     cout << "**********Lunchs reservations**********" << endl;
                    // if (i >= 14 && i < 21)
                    //     cout << "**********Dinner reservations**********" << endl;
                    cout << users_reservations[i][userIndex] << endl;
                }
                break;
            }
            case 4: {
                // increase_inventory();
                long long student_Num;
                long long p;
                cout << "enter your student number: ";
                cin >> student_Num;
                int userIndex = check_user(student_Num);
                if (userIndex == -1) {
                    cout << "Student number not found!" << endl;
                    break;
                }
                cout << "Enter the amount you want to add to your wallet: ";
                cin >> p;
                user_balance [userIndex] += p;
                cout << "The amount of " << p << " has been added to your account." << endl;
                cout << "Your inventory is: " << user_balance [userIndex];
                break;
            }
            case 5: {
                // change password
                long long student_Num;
                string new_password;
                cout << "enter your student number: ";
                cin >> student_Num;
                int userIndex = check_user(student_Num);
                if (userIndex == -1) {
                    cout << "Student number not found!" << endl;
                    break;
                }
                cout << "Enter your new password: ";
                cin >> new_password;
                if (new_password == passwords[userIndex]) {
                    cout << "The new password cannot be the same as the old password!" << endl;
                    break;
                }
                passwords[userIndex] = new_password;
                cout << "Password changed successfully!" << endl;
                break;
            }  
            case 6: {
                // save my reservations to TXT
                save_my_reservations(user_index);
                break;
            }
            case 7: {
                // show QR codes for reservations
                generate_qr(user_index);
                break;
            }
            case 0: {
                cout << "\033[1;31mExiting the program. Goodbye!\033[0m" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } //while for switch

} //بدنه else if --> user pannel
}


else
    cout << "\033[3;5;31m\n\aInvalid password or username!\033[0m" << endl;

    return 0;
}

//##################################################################################

//===============add, check, remove user==================

void add_student(string username, long long studentN, long long balance)
{
    usernames[user_count] = username;
    passwords[user_count] = "Aa@123456"; // Default password
    student_number[user_count] = studentN;
    user_balance[user_count] = balance;
    user_count++;
}

int check_user(long long studentN)
{
    for(int i = 0; i < user_count; i++)
    {
        if(student_number[i] == studentN)
        {
            return i;
        }
    }
    return -1;
}

void remove_user(long long studentN)
{
    for (int i = 0; i < user_count; i++)
    {
        if (student_number[i] == studentN)
        {
            for (int d = 0; d < 21; d++)
            {
                users_reservations[d][i] = "";
            }
            for (int j = i; j < user_count - 1; j++)
            {
                usernames[j] = usernames[j + 1];
                passwords[j] = passwords[j + 1];
                student_number[j] = student_number[j + 1];
                user_balance[j] = user_balance[j + 1];
            }
            user_count--;
            cout << "User removed successfully." << endl;
            save_reservations_file();
            return;
        }
    }
    cout << "Student number not found!" << endl;
}


void edit_user(long long studentN)
{
    for (int i = 0; i < user_count; i++)
    {
        if (student_number[i] == studentN)
        {
            string new_username;
            cout << "Current username: " << usernames[i] << endl;
            cout << "Enter new username: ";
            cin >> new_username;
            usernames[i] = new_username;
            cout << "Username updated successfully!" << endl;
            cout << "New username: " << usernames[i] << endl;
            return;
        }
    }
    cout << "Student number not found!" << endl;
}


bool login(string username, string password)
{
    for (int i = 0; i < user_count; i++)
    {
        if (usernames[i] == username && passwords[i] == password)
            return true;
    }
    return false;
}


//=======================food add , remove, edit and show==========================

void add_food(string foodN, int price, int foodID, int day)
{
    if (day < 1 || day > 7)
    {
        cout << "Invalid day selection!" << endl;
        return;
    }

    string Meal;
    cout << "Enter breakfast or lunch or dinner: ";
    cin >> Meal;
    int meal_type = meal_to_int(Meal);
    switch (meal_type)
    {
        case 0: { // breakfast
            food_names[day - 1][food_count[day - 1]] = foodN;
            food_prices[day - 1][food_count[day - 1]] = price;
            food_ID[day - 1][food_count[day - 1]] = foodID;
            food_count[day - 1]++;
            cout << "Food item '" << foodN << "' added successfully to day " << day << "." << endl;
            cout << "Price: " << price << ", Food ID: " << foodID << endl;
            break;
        }
        case 1: {
            food_names[(day - 1) + 7][food_count[(day - 1) + 7]] = foodN;
            food_prices[(day - 1) + 7][food_count[(day - 1) + 7]] = price;
            food_ID[(day - 1) + 7][food_count[(day - 1) + 7]] = foodID;
            food_count[(day - 1) + 7]++;
            cout << "Food item '" << foodN << "' added successfully to day " << day << "." << endl;
            cout << "Price: " << price << ", Food ID: " << foodID << endl;
            break;
        }
        case 2: {
            food_names[(day - 1) + 14][food_count[(day - 1) + 14]] = foodN;
            food_prices[(day - 1) + 14][food_count[(day - 1) + 14]] = price;
            food_ID[(day - 1) + 14][food_count[(day - 1) + 14]] = foodID;
            food_count[(day - 1) + 14]++;
            cout << "Food item '" << foodN << "' added successfully to day " << day << "." << endl;
            cout << "Price: " << price << ", Food ID: " << foodID << endl;
            break;
        }
        default: {
            cout << "Invalid meal type!" << endl;
            return;
        }
    }//end switch meal
}

void remove_food(int foodID)
{
    for (int day = 0; day < 21; day++)
    {
        for (int i = 0; i < food_count[day]; i++)
        {
            if (food_ID[day][i] == foodID) 
            {
                //************ برگشت مبلغ به دانشجو ************
                for (int u = 0; u < user_count; u++)
                {
                    if (users_reservations[day][u] == food_names[day][i])
                    {
                        user_balance[u] += food_prices[day][i];
                        users_reservations[day][u] = "";
                        cout << "Reservation for user " << usernames[u] 
                            << " has been canceled and " 
                            << food_prices[day][i] 
                            << " returned to their balance." << endl;
                    }
                }
                //************ حذف غذا از آرایه ************
                for (int k = i; k < food_count[day] - 1; k++)
                {
                    food_names[day][k] = food_names[day][k + 1];
                    food_prices[day][k] = food_prices[day][k + 1];
                    food_ID[day][k] = food_ID[day][k + 1];
                }
                food_count[day]--;
                cout << "Food item with ID " << foodID << " removed successfully from day " << (day % 7) + 1 << "." << endl;
                save_foods_file();
                save_reservations_file();
                save_users_file();
                return;
            }
        }
    }
    cout << "Food ID not found!" << endl;
}




void edit_food(int foodID, string new_food, int new_price)
{
    for (int day = 0; day < 21; day++) 
    {
        for (int i = 0; i < food_count[day]; i++)
        {
            if (food_ID[day][i] == foodID)
            {
                food_names[day][i] = new_food;
                food_prices[day][i] = new_price;
                cout << "Food item updated successfully for day " << (day % 7 + 1) << "!" << endl;
                return;
            }
        }
    }
    cout << "Food ID not found!" << endl;
}




void show_foods(int day, string meal)
{
    int meal_type = meal_to_int(meal);
    int row = (day - 1) + meal_type * 7;
    if (day < 1 || day > 7)
    {
        cout << "Invalid day selection!" << endl;
        return;
    }
    cout << "Foods for day " << day << ":\n";
    for (int i = 0; i < food_count[row]; i++)
    {
        cout << i << ") " << food_names[row][i] 
            << " | Price: " << food_prices[row][i] 
            << " | Food ID: " << food_ID[row][i] << endl;
        if ((i+1) % 5 == 0) cout << "============================\n";
    }
}



//======================User reservations===========================

void user_reservation(int user_index)
{
    string food_name;
    int day;

    while (true)
    {
        cout << "Enter the day of the week for reservation (1=Saturday, ..., 7=Friday): ";
        cin >> day;
        if (day < 1 || day > 7)
        {
            cout << "Invalid day selection!" << endl;
            continue;
        }

        cout << "enter breakfast or lunch or dinner: ";
        string Meal;
        cin >> Meal;
        int meal_type = meal_to_int(Meal);
        int row = (day - 1) + meal_type * 7;
        show_foods(day, Meal);
        cout << "Enter food name to reserve: ";
        cin.ignore();
        getline(cin, food_name);
// ******پیدا کردن قیمت غذا******
        int price = -1;
        for (int i = 0; i < food_count[row]; i++)
        {
            if (food_names[row][i] == food_name)
            {
                price = food_prices[row][i];
                break;
            }
        }
        if (price == -1)
        {
            cout << "Food not found on this day!" << endl;
            continue;
        }
        if (users_reservations[row][user_index] != "")
        {
            cout << "You have already made a reservation for day " << day << "." << endl;
            return;
        }
        if (user_balance[user_index] < price)
        {
            cout << "Not enough balance. Please increase your balance." << endl;
            return;
        }
        users_reservations[row][user_index] = food_name;
        user_balance[user_index] -= price;
        save_reservations_file();
        save_users_file();
        cout << "Reservation for '" << food_name << "' successful for day " << day << "." << endl;
        break;
    }
}


//======================save and load users===========================
void save_users_file()
{
    ofstream file("users.txt");
    if (!file)
    {
        cout << "Error opening file for saving!" << endl;
        return;
    }
    file << user_count << endl;
    for (int i = 0; i < user_count; i++)
    {
        file << usernames[i] << " "
            << passwords[i] << " "
            << student_number[i] << " "
            << user_balance[i] << endl;
    }
    file.close();
}

void load_users_file()
{
    ifstream file("users.txt");  
    if (!file)
    {
        cout << "No user file found. Starting fresh!" << endl;
        return;
    }
    file >> user_count;
    for (int i = 0; i < user_count; i++)
    {
        file >> usernames[i]
            >> passwords[i]
            >> student_number[i]
            >> user_balance[i];
    }
    file.close();
}


//======================save and load foods===========================
void save_foods_file()
{
    ofstream file("foods.txt");
    if (!file)
    {
        cout << "Error saving foods!" << endl;
        return;
    }
    for (int day = 0; day < 7; day++)
    {
        for (int i = 0; i < food_count[day]; i++)
        {
            file << day + 1 << "|"
                << food_names[day][i] << "|"
                << food_prices[day][i] << "|"
                << food_ID[day][i] << endl;
        }
    }
    file.close();
}

void load_foods_file()
{
    // پاکسازی قبل از لود
    for (int i = 0; i < 7; i++)
        food_count[i] = 0;
    ifstream file("foods.txt");
    if (!file)
    {
        cout << "No food file found!" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        int sep1 = line.find('|');
        int sep2 = line.find('|', sep1 + 1);
        int sep3 = line.find('|', sep2 + 1);
        int day = stoi(line.substr(0, sep1));
        string name = line.substr(sep1 + 1, sep2 - sep1 - 1);
        int price = stoi(line.substr(sep2 + 1, sep3 - sep2 - 1));
        int id = stoi(line.substr(sep3 + 1));
        food_names[day - 1][food_count[day - 1]] = name;
        food_prices[day - 1][food_count[day - 1]] = price;
        food_ID[day - 1][food_count[day - 1]] = id;
        food_count[day - 1]++;
    }
    file.close();
}


//======================save and load foods===========================
void save_reservations_file()
{
    ofstream file("reservations.txt");
    if (!file.is_open())
    {
        cout << "Error saving reservations!" << endl;
        return;
    }
    for (int meal = 0; meal < 3; meal++)
    {
        for (int day = 0; day < 7; day++)
        {
            int row = day + meal * 7;
            for (int user = 0; user < user_count; user++)
            {
                if (users_reservations[row][user] != "")
                {
                    file << day + 1 << "|" << meal << "|"
                        << student_number[user] << "|"
                        << users_reservations[row][user] << endl;
                }
            }
        }
    }
    file.close();
}

void load_reservations_file()
{
    // پاکسازی رزروهای قبلی
    for (int d = 0; d < 21; d++)
        for (int u = 0; u < user_count; u++)
            users_reservations[d][u] = "";
    ifstream file("reservations.txt");
    if (!file.is_open())
        return;
    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;
        int sep1 = line.find('|');
        int sep2 = line.find('|', sep1 + 1);
        int sep3 = line.find('|', sep2 + 1);
        int day = stoi(line.substr(0, sep1));
        int meal = stoi(line.substr(sep1 + 1, sep2 - sep1 - 1));
        long long studentN = stoll(line.substr(sep2 + 1, sep3 - sep2 - 1));
        string food = line.substr(sep3 + 1);
        int index = find_user_index_by_student_number(studentN);
        if (index != -1)
        {
            int row = (day - 1) + meal * 7;
            users_reservations[row][index] = food;
        }
    }
    file.close();
}

int find_user_index_by_student_number(long long studentN)
{
    for (int i = 0; i < user_count; i++)
    {
        if (student_number[i] == studentN)
            return i;
    }
    return -1;
}

int meal_to_int(string meal)
{
    for (int i = 0; i < meal.length(); i++)
        if (meal[i] >= 'A' && meal[i] <= 'Z')
            meal[i] += 32;
    if (meal == "breakfast") return 0;
    if (meal == "lunch")     return 1;
    if (meal == "dinner")    return 2;
    return -1;
}

//==================search food=====================
void search_food()
{
    cout << "Search by (1 Name or (2 Meal type: " << endl;
    cout << "choose: ";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1)
    {
        string name;
        cout << "Enter food name to search: ";
        getline(cin, name);
        bool found = false;
        for (int day = 0; day < 21; day++)
        {
            for (int i = 0; i < food_count[day]; i++)
            {
                if (food_names[day][i].find(name) != string::npos)
                {
                    int meal_type = day / 7;
                    int day_of_week = (day % 7) + 1;
                    string meal = (meal_type == 0) ? "Breakfast" : (meal_type == 1) ? "Lunch" : "Dinner";
                    cout << "Day: " << day_of_week << " | Meal: " << meal 
                        << " | Name: " << food_names[day][i]
                        << " | Price: " << food_prices[day][i]
                        << " | ID: " << food_ID[day][i] << endl;
                    found = true;
                }
            }
        }
        if (!found) cout << "Food not found!\n";
    }
    else if (choice == 2)
    {
        string meal;
        cout << "Enter meal type (breakfast/lunch/dinner): ";
        cin >> meal;
        int meal_type = meal_to_int(meal);
        bool found = false;
        for (int day = 1; day <= 7; day++)
        {
            int row = (day - 1) + meal_type * 7;
            for (int i = 0; i < food_count[row]; i++)
            {
                cout << "Day: " << day 
                    << " | Name: " << food_names[row][i]
                    << " | Price: " << food_prices[row][i]
                    << " | ID: " << food_ID[row][i] << endl;
                found = true;
            }
        }
        if (!found) cout << "No foods found for this meal type!\n";
    }
    else
        cout << "Invalid choice!\n";
}

//=======================save my reservations==========================
void save_my_reservations(int user_index)
{
    string filename = usernames[user_index] + "_reservations.txt";
    ofstream file(filename);
    if (!file)
    {
        cout << "Error saving your reservations!" << endl;
        return;
    }

    for (int day = 0; day < 21; day++)
    {
        if (users_reservations[day][user_index] != "")
        {
            int meal_type = day / 7;
            int day_of_week = (day % 7) + 1;
            string meal = (meal_type == 0) ? "Breakfast" : (meal_type == 1) ? "Lunch" : "Dinner";
            file << "Day: " << day_of_week 
                << " | Meal: " << meal 
                << " | Food: " << users_reservations[day][user_index] << endl;
        }
    }
    file.close();
    cout << "Your reservations have been saved to file: " << filename << endl;
}

void generate_qr(int user_index)
{
    cout << "Your QR codes for reservations:\n";
    for (int day = 0; day < 21; day++)
    {
        if (users_reservations[day][user_index] != "")
        {
            int food_id = -1;
            for (int i = 0; i < food_count[day]; i++)
            {
                if (food_names[day][i] == users_reservations[day][user_index])
                {
                    food_id = food_ID[day][i];
                    break;
                }
            }
            if (food_id != -1)
                cout << "QR#" << food_id << " | " << users_reservations[day][user_index] << endl;
        }
    }
}
//=========================قابلیت های ویژه ادمین==========================
void show_reservations_sorted() //مرتب کردن رزرو بر اساس زمان ثبت
{
    cout << "All reservations (sorted by registration order):" << endl;
    for (int day = 0; day < 21; day++)
    {
        for (int u = 0; u < user_count; u++)
        {
            if (users_reservations[day][u] != "")
            {
                int meal_type = day / 7;
                int day_of_week = (day % 7) + 1;
                string meal;
                if (meal_type == 0) {
                    meal = "Breakfast";
                }
                else if (meal_type == 1) {
                    meal = "Lunch";
                }
                else {
                    meal = "Dinner";
                }
                cout << "Day: " << day_of_week 
                    << " | Meal: " << meal
                    << " | User: " << usernames[u]
                    << " | Food: " << users_reservations[day][u] << endl;
            }
        }
    }
}

void most_popular_food()    //محبوب ترین غذا
{
    string most_food = "";
    int most_count = 0;
    for (int day = 0; day < 21; day++)
    {
        for (int i = 0; i < food_count[day]; i++)
        {
            int count = 0;
            for (int u = 0; u < user_count; u++)
            {
                if (users_reservations[day][u] == food_names[day][i])
                    count++;
            }
            if (count > most_count)
            {
                most_count = count;
                most_food = food_names[day][i];
            }
        }
    }
    if (most_count > 0)
        cout << "Most popular food: " << most_food << " | Reserved " << most_count << " times." << endl;
    else
        cout << "No reservations yet." << endl;
}

void income_and_refunds()   //درآمد کل و مبلغ برگشتی
{
    int total_income = 0;
    int total_refunds = 0;
    // مجموع درآمد از رزروهای انجام شده
    for (int day = 0; day < 21; day++) {
        for (int i = 0; i < food_count[day]; i++)
        {
            for (int u = 0; u < user_count; u++)
            {
                if (users_reservations[day][u] == food_names[day][i])
                    total_income += food_prices[day][i];
            }
        }
    }
    //مجموع مبلغ برگشتی 
    for (int u = 0; u < user_count; u++)
        total_refunds += user_balance[u];
    cout << "Total income: " << total_income << endl;
    cout << "Total refunds: " << total_refunds << endl;
}

void top_reserving_students()   //دانشجویان با بیشترین رزرو
{
    int max_reservations = 0;
    // پیدا کردن بیشترین تعداد رزرو
    int user_reservations[MAX_USERS] = {};
    for (int u = 0; u < user_count; u++)
    {
        int count = 0;
        for (int day = 0; day < 21; day++)
        {
            if (users_reservations[day][u] != "")
                count++;
        }
        user_reservations[u] = count;
        if (count > max_reservations)
            max_reservations = count;
    }
    cout << "Students with the most reservations (" << max_reservations << "):" << endl;
    for (int u = 0; u < user_count; u++) {
        if (user_reservations[u] == max_reservations)
            cout << usernames[u] << " | Student number: " << student_number[u] << endl;
    }
}

//==============ساخت هش کد برای رمز ها=================
