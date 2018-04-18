#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct node
{
	int PassportNum;
	char firstName[20];
	char lastName[20];
	int birthYear;
	char email[20];
	int travelFrom;
	int travelClass;
	int numTrips;
	int avgDuration;

	struct node* NEXT;
}passenger;

//Functions
void login(char username[], char password[]);
void addPassenger(struct node** top);
void showPassengers(struct node* top);
void showPassengerDetails(struct node* top);
void updatePassengerStats(struct node* top);
void deletePassenger(struct node* top, int pos);
void generateStats(struct node* top);

void main()
{
	//Files
	FILE *loginfile;
	//Variables 
	char username[20] = "";
	char password[20] = "";
	int choice = 0;
	int position = 0;
	int numOfPassengers = 0;
	struct node* headPtr = NULL;

/*	loginfile = fopen("Login Records.txt", "a");

	if (loginfile == NULL)
	{
		printf("The file could not be opened.");
	}
	else
	{
      login(username, password, loginfile);
	  fclose(loginfile);
	}*/

	//Assuming login was successful
	printf("______________________________________________________________\n");
	printf("Welcome to xyz Airport statistic application\n");
	printf("Press the following keys to activate the following funtions:\n");
	printf("1 - Add a passenger\n2 - Dispaly all pasengers\n3 - Display passenger details\n4 - Update a passengers statistic\n5 - Delete Passenger\n6 - Generate Statistics");

	scanf("%d",&choice);

	while (choice != -1)
	{
		switch (choice)
		{
		case 1:
			addPassenger(&headPtr);
			numOfPassengers++;
			break;
		case 2:
			showPassengers(headPtr);
			break;
		case 3:
			showPassengerDetails(headPtr);
			break;
		case 4:
			updatePassengerStats(headPtr);
			break;
		case 5:
			printf("Enter passenger Number of the passenger you would like to remove from the database: %d", numOfPassengers);
			scanf("%d", &position);
			while(position < 1 || position > numOfPassengers)
			{
				printf("Passenger does not exist try again: ");
				scanf("%d", &position);
			}
			deletePassenger(headPtr, position);
			numOfPassengers--;
			break;
		case 6:
			generateStats(headPtr);
			break;
		}

		printf("______________________________________________________________\n");
		printf("Press the following keys to activate the following funtions:\n");
		printf("1 - Add a passenger\n2 - Dispaly all pasengers\n3 - Display passenger details\n4 - Update a passengers statistic\n");
		printf("______________________________________________________________\n");
		scanf("%d", &choice);
	}
}

void login(char username[], char password[], FILE *file)
{
		printf("Enter username: ");
		scanf("%s", username);
		printf("your name is %s",username);

		//Check if username is in the file
		char aWord[20];
		int found = 0;

		while (!feof(file))
		{
			fgets(aWord, 2, stdin);
			printf("%s", aWord);
			if (strcmp(aWord, username) == 0)
			{
				found = 1;
				//aWord = eof();
				printf("Username found");
				break;
			}
		}

		if (found == 0)
		{
			printf("Username entered is incorrect");
		}
}

void addPassenger(struct node** top)
{
	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node) * 1);

	printf("You are adding a passenger!\n");
	printf("============================\n");

	printf("Enter passengers passport number: ");
	scanf("%d", &newNode->PassportNum);

	printf("Enter Passengers full name: ");
	scanf("%s %s", &newNode->firstName, &newNode->lastName);

	printf("Enter Passengers birth year: ");
	scanf("%d", &newNode->birthYear);

	printf("Enter Passengers Email: ");
	scanf("%s", &newNode->email);

	printf("Select where passenger is travelling from:\n");
	printf("1 - Uk\n2 - Rest of Europe\n3 - Asia\n4 - Americas\n5 - Australia\n");
	scanf("%d", &newNode->travelFrom);

	printf("Select what travel class the passenger will fly in:\n");
	printf("1 - Economy\n2 - Premium Economy\n3 - Business Class\n4 - First Class\n");
	scanf("%d", &newNode->travelClass);

	printf("Select number of trips made to Ireland: ");
	printf("1 - Less than three times per year\n2 - Less than 5 times per year\n3 - More than five times per year");
	scanf("%d",&newNode->numTrips);

	printf("Select the average length of duration of the passegners visits");
	printf("\n1 - One day\n2 - Less than 3 days\n3 - Less than 7 days\n4 - More than 7 days\n");
	scanf("%d",&newNode->avgDuration);

	newNode->NEXT = *top;
	*top = newNode;
}

void showPassengers(struct node* top)
{
	struct node* curr;
	int i = 1;
	curr = top;

	printf("\n");
	printf("ALL PASSENGERS\n");
	printf("=================\n");

	while (curr != NULL)
	{
		printf("Passenger %d: %d\n",i, curr->PassportNum);
		curr = curr->NEXT;
		i++;
	}
}

void showPassengerDetails(struct node* top)
{
	//Variables
	struct node* curr;
	int passportNum = 0;
	char *travelFrom[] = {"", "UK","Rest of Europe", "Asia", "Americas","Australia"};
	char *travelClass[] = {"","Economy","Premium Economy","Business Class","First Class"};
	char *trips[] = {"","Less than three times a year","Less than five times a year","More than five tiems a year"};
	char *avgStay[] = {"","One day","Less than 3 days","Less than 7 days","More than 7 days"};
	
	curr = top;

	printf("Select Passenger's passport Number: ");
	scanf("%d", &passportNum);
	printf("\n");
	printf("PASSENGER DETAILS\n");
	printf("=================\n");

	while (curr != NULL)
	{
		if (curr->PassportNum == passportNum)
		{
			
			/*printf("==================");
			printf("\nPASSENGER %d\n", i);
			printf("==================\n");*/
			printf("Passport Number: %d\nName: %s %s\nBirth Year: %d\nEmail Address: %s\nTravelled from: %s\nTravel Class: %s\nNumber of Trips to Ireland: %s\nAverage Length of Duration %s\n", curr->PassportNum, curr->firstName, curr->lastName, curr->birthYear, curr->email, travelFrom[curr->travelFrom], travelClass[curr->travelClass], trips[curr->numTrips], avgStay[curr->avgDuration]);
			break;
		}
		curr = curr->NEXT;
		if (curr->PassportNum == passportNum)
		{
			break;
		}
	}
}

void updatePassengerStats(struct node* top)
{
	int passportNum = 0;
	struct node* curr;

	curr = top;

	printf("Select Passenger's passport Number: ");
	scanf("%d", &passportNum);

	while (curr != NULL)
	{
		if (curr->PassportNum == passportNum)
		{
			printf("You are editing a passenger!\n");
			printf("============================\n");

			printf("Enter new passport number: ");
			scanf("%d", &curr->PassportNum);

			printf("Enter new full name: ");
			scanf("%s %s", &curr->firstName, &curr->lastName);

			printf("Enter new birth year: ");
			scanf("%d", &curr->birthYear);

			printf("Enter new Email: ");
			scanf("%s", &curr->email);

			printf("Select new point where travelled from:\n");
			printf("1 - Uk\n2 - Rest of Europe\n3 - Asia/n4 - Americas/n5 - Australia\n");
			scanf("%d", &curr->travelFrom);

			printf("Select new travel class:\n ");
			printf("1 - Economy\n2 - Premium Economy\n3 - Business Class\n4 - First Class\n");
			scanf("%d", &curr->travelClass);

			printf("Select new number of trips made to Ireland: ");
			scanf("%d", &curr->numTrips);

			printf("Select new average length of duration of the passegners visits");
			printf("\n1 - One day\n2 - Less than 3 days\n3 - Less than 7 days\n4 - More than 7 days\n");
			scanf("%d", &curr->avgDuration);
		}
		if (curr->PassportNum == passportNum)
			break;
		curr = curr->NEXT;
	}
}

void deletePassenger(struct node* top, int pos)
{
	struct node* temp;
	struct node* prev;
	//int pos = 0;
	int i;

	temp = top;
	prev = temp;

	for (i = 0; i < pos - 1; i++)
	{
		prev = temp;
		temp = temp->NEXT;
	}

	prev->NEXT = temp->NEXT;
	free(temp);
}

void generateStats(struct node* top)
{

}