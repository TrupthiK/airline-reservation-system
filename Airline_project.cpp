#include<iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
#define size 100

class airlines
{
public:
	int count = 0;
	airlines();
	//void main_menu();
	void make_reservation();
	void cancel_reservation();
	void search_passenger();
	void change_reservation();
	void print_list();
	void print_report();


private:
	struct node
	{
	public:
		string full_name, last_name, id, phone_number, menu;
		int reserve_number, seat_num;


		node* next = NULL;

	};

	node* start = NULL;

	node* temp, * temp2;

}obj;

// #include <iostream>
// #include "learnprogramo.h"
// using namespace std;

int reserve = 999;




int seat[size];
void seat_fill()
{
	for (int i = 0; i < size; i++)
	{
		seat[i] = 0;
	}
}

bool taken = false;
void seat_no(int y)
{

	for (int i = 0; i < size; i++)
	{
		//If seat is filled up its value would be -1
		if (seat[i] == -1)
		{
			taken = true;
			cout << "The seat is already taken.\n";
			cout << "Please choose another seat number from below." << endl;
			//j will start from 1st seat onwards and we will print all the available seats in order or 10s
			int j = 1;
			while (j < size + 1)
			{
				//If seats are filled increment the j value and check for next condition
				if (seat[j - 1] == -1)
					j++;
				//If seats are empty print out the seats available unless all seats are covered
				else
				{
					cout << "|" << j << "|";
					//Print available seats in order of 10 seats per row
					if (j % 10 == 0)
						cout << endl;
					j++;
				}
			}
		}
	}

}

void menu()
{
	char choice = 0;
	do {
		cout << "Make Reservation		--------- [1]" << endl;
		cout << "Cancel reservation		--------- [2]" << endl;
		cout << "Search Passenger		--------- [3]" << endl;
		cout << "Change Reservation		--------- [4]" << endl;
		cout << "Print a list			--------- [5]" << endl;
		cout << "Print status report		--------- [6]" << endl;
		cout << "Quit				--------- [7]" << endl;
		cout << "\nOption....					" << endl;

		cin >> choice;
		//to change the choice variable to 48 bit
		choice = ((int)(choice)-48);

		//Choosing options
		switch (choice)
		{
		case 1: system("cls"); obj.make_reservation();
			break;
		case 2: system("cls"); obj.cancel_reservation();
			break;
		case 3: system("cls"); obj.search_passenger();
			break;
		case 4: system("cls"); obj.change_reservation();
			break;
		case 5: system("cls"); obj.print_list();
			break;
		case 6: system("cls"); obj.print_report();
			break;
		case 7: cout << endl << "Thank you come again" << endl;
			break;
		default:
			cout << "Entered wrong number" << endl;
			break;
		}
		cout << "\nProcess completed....\n";

		//Now if the user again presses enter the console should clear the screen for next loop iteration
		cin.get();
		if (cin.get() == '\n')
			system("cls");

		//Again start the reservation system
		cout << endl << "AIRLINE RESERVATION SYSTEM" << endl;
	} while (choice != 7);

}

//************************************************************************
airlines::airlines()
{
	start = NULL;
}

//*************************************************************************

void airlines::make_reservation()
{
	//Create variables for meal option
	int meal_choice, x;

	//Initiate the temporaty node pointer variable
	temp = new node;

	//Enter all the passenger details in the temp pointer node
	cout << endl << "Enter first name of person : " << endl;
	cin >> temp->full_name;
	cout << "\nEnter last name of person : \n";
	cin >> temp->last_name;
	cout << "\nEnter ID of the person : \n";
	cin >> temp->id;
	cout << "\nEnter phone number of the person : \n";
	cin >> temp->phone_number;

	//Check the seat which the passenger wants whether its full or not
	do {
		cout << "\nPlease enter the seat number : \n";
		cin >> x;
		//If seat number entered by passenger is greater than max amounts of seats let them enter the seat number again
		while (x > size)
		{
			cout << "Try again::";
			cin >> x;
		}

		cout << endl;
		if (seat[x - 1] > -1)
			taken = false;
		else
			seat_no(x);
		//Book seat
		seat[x - 1] = -1;
		temp->seat_num = x;

	} while (taken == true);

	//----------------------------------------------------------------------

	//Final stage of ticket reservation
	//Select meal preference
	cout << "Please enter meal of your choice : \n";
	cout << "Veg		...... 1\n";
	cout << "Non-veg		...... 2\n";
	cout << "No meal		...... 3\n" << endl;;

	cout << "Your choice : ";
	cin >> meal_choice;

	//If entered value is any other than provided options enter the options again
	while (meal_choice > 3 || meal_choice < 1)
	{
		cout << "Try again : ";
		cin >> meal_choice;
	}

	//Set value of temp pointer meal preference
	if (meal_choice == 1)
		temp->menu = "Veg";
	else if (meal_choice == 2)
		temp->menu = "non-veg";
	else
		temp->menu = "No meal";

	//Increment reserve value by 1 as it works as registeration number for passengers
	//If after incrementing 1st passengers registeration number is 1000
	//next one would get 1001 as reserve is a global variable
	//and can be constantly updated
	reserve++;
	temp->reserve_number = reserve;
	cout << "\nYour reservation number is : " << reserve << endl;

	//Put next of temp as null because it contains the value of latest registered passenger
	temp->next = NULL;

	//If head node list is null make temp as head
	if (start == NULL)
		start = temp;
	//else take 2nd temp variable pointer and point to head
	//then iterate throughout temp2 unless u get null value of next
	else
	{
		temp2 = start;
		while (temp2->next != NULL)
		{
			temp2 = temp2->next;
		}
		//Point the last node in list to newly created temp pointer
		temp2->next = temp;
	}
	count++;
}
//********************************************************************************************
//Create a cancel variable to count number of seats cancelled
int cancel = 0;
void airlines::cancel_reservation()
{
	node* pre;
	int num;
	cout << "Please enter your reservation number :";
	cin >> num;

	//Create a new node and point to head of the list of passengers
	node* cur = start;
	//If there are non zero passengers
	if (cur != NULL)
	{
		//If the reservation number of 1st passenger
		//matches the entered registeration number
		//Delete the record of that passenger
		//& increment cancelled list value
		if (start->reserve_number == num)
		{
			node* del = start;
			start = start->next;
			delete del;
			//Update 1st seat value to 0
			//As it is cancelled now
			seat[0] = 0;
			cancel++;
			count--;
			return;
		}
		else
		{
			/*node* pre, * cur;*/
			pre = start;
			cur = start->next;
			while (cur != NULL)
			{
				if (cur->reserve_number == num)
					break;
				pre = cur;
				cur = cur->next;
			}
			seat[cur->seat_num - 1] = 0;
			if (cur != NULL)
				pre->next = cur->next;
		}
		count--;
		cancel++;
	}
	//If no passengers r registered
	else
		cout << "Nothing to delete or invalid entry\n" << endl;

}
//********************************************************************************************
//Method to search for passenger details
void airlines::search_passenger()
{
	string name;
	cout << "Please enter your first name here: ";
	cin >> name;

	//Start searching from head node of passengers list
	node* cur = start;
	while (cur != NULL)
	{
		//If passenger name is found in list
		//Print all the details of the passenger
		if (cur->full_name == name)
		{
			cout << "First Name : " << cur->full_name << endl;
			cout << "Last Name : " << cur->last_name << endl;
			cout << "ID " << cur->id << endl;
			cout << "Phone number: " << cur->phone_number << endl;
			cout << "Seat Number: " << cur->seat_num << endl;
			cout << "Reservation No. " << cur->reserve_number << endl;
			return;
		}
		//Point to next passenger by using next pointer
		cur = cur->next;
	}	cout << " Passenger not found on record!! \n\n";

}

//********************************************************************************************
//Method to change reservation seat of passenger
void airlines::change_reservation()

{
	int option, next_seat;
	cout << " Please enter your seat number: ";
	do {
		cin >> option;
		if (seat[option - 1] == 0)
			cout << "\nKindly provide correct seat number : \n";
	} while (seat[option - 1] != -1);

	node* cur = start;

	//Check for node containing passenger's entered seat number
	while (cur->seat_num != option)
	{
		cur = cur->next;
	}
	//Show number of seats empty
	cout << "Please choose another seat number from below.";
	//J is declared for absolute seat number
	int j = 1;
	while (j < size + 1)
	{
		//If seat value is -1
		//which means already booked
		//skip to the next seat by using incremental operator
		if (seat[j - 1] == -1)
			j++;
		else
		{
			//Printout all the available seats in sequence of 10
			cout << "| " << j << "|";
			if (j % 10 == 0)
				cout << endl;
			j++;
		}
	}
	//Get seat number input from user
	do {
		cin >> next_seat;
		if (seat[next_seat - 1] == -1)
			cout << "\nAlready booked, choose another!\n";
	} while (seat[next_seat - 1] != 0);

	//Change the previously booked seat status to 0
	//Which means seat is empty now
	seat[cur->seat_num - 1] = 0;
	//Update new seat detail in passenger's node
	cur->seat_num = next_seat;
	//Change new seat status value to -1 means booked
	seat[next_seat - 1] = -1;

}

//********************************************************************************************
//Method to print details of all the passengers currently booked
void airlines::print_list()
{
	temp = start;
	//If no one booked yet exit this method
	if (temp == NULL)
		cout << " End of lists" << endl;
	else
	{
		int cnt = 1;
		cout << "\tNumber\t First Name\t Last Name\t ID\t";
		cout << "Phone Number\t Seat Number\t Reservation No\t Menu\n";

		while (temp != NULL)
		{
			//setw() function is used to add correct width spacing between characters
			cout << "\t" << cnt << setw(15);
			cout << temp->full_name << setw(15);
			cout << temp->last_name << setw(12);
			cout << temp->id << setw(12);
			cout << temp->phone_number << setw(15);
			cout << temp->seat_num << setw(15);
			cout << temp->reserve_number << setw(12);
			cout << temp->menu << "\n";

			temp = temp->next;
			cnt++;
		}
		cout << "\n\n";

	}
}
//********************************************************************************************
//Method to print number of passengers booked
//& number of passengers cancelled so far
void airlines::print_report()
{
	//int count = 0;
	//for (int i = 0; i < size; i++)
	//{
	//	//Count the number of booked passengers
	//	if (seat[i] == -1)
	//		count++;
	//}
	cout << "The number of reserved seats are: " << count << endl;
	cout << "The number of cancellations are: " << cancel << endl;
}

//********************************************************************************************

int main()
{

	//ClS is used for clearing the screen
	system("CLS");
	cout << "\nAIRLINE RESERVATION SYSTEM \n";
	menu();
	seat_fill();

	return 0;


}



