#include <stdio.h>
#include <string.h>

#define NAME_LEN 40
#define ADDRESS_LEN 100
#define TOWN_POP 100
#define EMPTY_TEL 0000000

enum months {ERR, JAN, FEB, MAR, APR, MAY, JUN, JULY, AUG, SEP, OCT, NOV, DEC};

typedef struct {
	int day;
	months app_month ;
	int year;
}date;
date EMPTY_DATE{ EMPTY_DATE.day = 0,EMPTY_DATE.app_month = ERR,  EMPTY_DATE.year = 0000 };

 
typedef struct {

	char name[NAME_LEN];
	char adress[ADDRESS_LEN];
	date app_date;
	int number;
}application;

application EMPTY_APP = { {'\0'}, {'\0'},  EMPTY_DATE , EMPTY_TEL };


typedef struct {

	application apps[TOWN_POP];
	int rear;
	int front;
	int counter;

}waiting_Apps_q;

typedef struct {
	application accepted_Apps[TOWN_POP];
	int top;
}users_s;

typedef struct {
	int numbers[TOWN_POP];
	int top;
}telephones_s;



//--------------------------------------------------------------------------------------
//QUEUE FUNCTIONS
void initialize(waiting_Apps_q *list);

int is_Full_q(waiting_Apps_q *list);

int is_Empty_q(waiting_Apps_q *list);

void insert(waiting_Apps_q *list, application app);

application remove(waiting_Apps_q *list);


//--------------------------------------------------------------------------------------
//Users STACK FUNCTIONS
void init_users(users_s *list);

int is_Full_users(users_s *list);

int is_Empty_users(users_s *list);

void push_users(users_s *list, application inp);

application pop_users(users_s *list);

//--------------------------------------------------------------------------------------
//Telephone STACK FUNCTIONS

void init_telep(telephones_s *list);

int is_Full_telep(telephones_s *list);

int is_Empty_telep(telephones_s *list);

void push_telep(telephones_s *list, int num);

int pop_telep(telephones_s *list);

void install_From(telephones_s *list, int initial);

//--------------------------------------------------------------------------------------
//MENU FUNCTIONS

int apply(waiting_Apps_q *list);

int give_Number(waiting_Apps_q *list, users_s *person, telephones_s *num);

int search_User(users_s *list, int phoneNum);

void cancel_User(users_s *person, telephones_s *numbers, int order);


 int main() {

	 int choice, phoneNum;

	 waiting_Apps_q list;
	 initialize(&list);
	 users_s accepted;
	 init_users(&accepted);
	 telephones_s numbers;
	 init_telep(&numbers);
	 install_From(&numbers, 2260000);


	 printf("MENU\n-----\n1)Apply\n2)Take a number\n3)Cancel account\n4)EXIT\nEnter your choice: ");
	 scanf("%d", &choice);

	 while (choice != 4) {
		 switch (choice)
		 {
		 case 1: apply(&list);//NEW USER APPLÝES
			 break;
		 case 2: give_Number(&list, &accepted, &numbers); //GIVING A NUMBER TO USER
			 break;
		 case 3: {//CANCEL USER
			 int index;
			 printf("\n If you cancel your account, please enter your telephone number: ");
			 scanf("%d", &phoneNum);

			 index = search_User(&accepted , phoneNum);
			 cancel_User(&accepted, &numbers, index);
		 }
			 break;
		 default: printf("Invalid Answer!!");
			 break;
		 }
		 printf("\n\n\nMENU\n-----\n1)Apply\n2)Take a number\n3)Cancel account\n4)EXIT\nEnter your choice: ");
		 scanf("%d", &choice);
	 }
	

	 return 0;
 }




 //--------------------------------------------------------------------------------------
 //QUEUE FUNCTIONS
 void initialize(waiting_Apps_q *list) {
	 list->rear = 0;
	 list->counter = 0;
	 list->front = 0;
 }

 int is_Full_q(waiting_Apps_q *list) {
	 if (list->counter == TOWN_POP)
		 return 1;
	 return 0;
 }

 int is_Empty_q(waiting_Apps_q *list) {
	 if (list->counter == 0)
		 return 1;
	 return 0;
 }

 void insert(waiting_Apps_q *list, application app) {
	 if (is_Full_q(list))
		 printf("Error!! There is no enough telephone number!!");
	 else {
		 list->apps[list->rear] = app;
		 list->rear = ((list->rear + 1) % TOWN_POP);
		 list->counter++;
	 }
 }

 application remove(waiting_Apps_q *list) {

	 application carrier;
	 if (is_Empty_q(list))
		 printf("Error!! There is no waiting application!!");
	 else {
		 carrier = list->apps[list->front];
		 list->front = ((list->front + 1) % TOWN_POP);
		 list->counter--;
		 return carrier;
	 }
	 carrier = EMPTY_APP;

	 return carrier;
 }


 //--------------------------------------------------------------------------------------
 //Users STACK FUNCTIONS
 void init_users(users_s *list) {
	 //initializes user structure
	 list->top = -1;
 }

 int is_Full_users(users_s *list) {
	 if (list->top == TOWN_POP - 1)
		 return 1;
	 return 0;
 }

 int is_Empty_users(users_s *list) {
	 if (list->top == -1)
		 return 1;
	 return 0;
 }

 void push_users(users_s *list, application inp) {
	 if (is_Full_users(list))
		 printf("Error!! Population is exceeded!!");
	 else {
		 list->top++;
		 list->accepted_Apps[list->top] = inp;
	 }
 }

 application pop_users(users_s *list) {
	 application carrier;

	 if (is_Empty_users(list))
		 printf("Error!! Anyone doesn't use telephone");
	 else {
		 carrier = list->accepted_Apps[list->top];
		 list->top--;
		 return carrier;
	 }

	 carrier = EMPTY_APP;
	 return carrier;
 }

 //--------------------------------------------------------------------------------------
 //Telephone STACK FUNCTIONS

 void init_telep(telephones_s *list) {
	 //initializes telephone structure
	 list->top = -1;
 }

 int is_Full_telep(telephones_s *list) {
	 if (list->top == TOWN_POP - 1)
		 return 1;
	 return 0;
 }

 int is_Empty_telep(telephones_s *list) {
	 if (list->top == -1)
		 return 1;
	 return 0;
 }

 void push_telep(telephones_s *list, int num) {
	 if (is_Full_telep(list))
		 printf("There are numbers as much as Town Population.So number cannot be pushed");
	 else {
		 list->top++;
		 list->numbers[list->top] = num;
	 }

 }

 int pop_telep(telephones_s *list) {
	 int carrier;
	 if (is_Empty_telep(list))
		 printf("Error!! There is no enough number!\nAre you sure that you live in this town");

	 else {
		 carrier = list->numbers[list->top];
		 list->top--;
		 return carrier;
	 }
	 carrier = EMPTY_TEL;

	 return carrier;
 }

 void install_From(telephones_s *list, int initial) {
	 //THIS FUNCTION INSTALL NUMBER POOL

	 if (initial <= EMPTY_TEL)
		 printf("You cannot initial from %d", initial);

	 while (!is_Full_telep(list)) {
		 for (int i = initial; i < initial + TOWN_POP; i++)
			 push_telep(list, i);
	 }
 }


 //--------------------------------------------------------------------------------------
 //MENU FUNCTIONS

 int apply(waiting_Apps_q *list) {
	 bool sent = true;
	 char sep, cont;
	 application info;

	 while (sent != false) {
		 printf("\n\n\n-----------------------------------------------------------------------------------------------\n");
		 printf("Welcome!!\nPlease answer the question:\nWhat is your name?(# for exit)\n");
		 scanf(" %[^\n]", info.name);

		 if (info.name[0] == '#')
			 return 0;

		 printf("Your adress?(# for exit)\n");
		 scanf(" %[^\n]", info.adress);
		 if (info.adress[0] == '#')
			 return 0;

		 printf("Application Date?(etc. 16/12/2018)\n(0 for exit)\n");
		 scanf("%d", &info.app_date.day);
		 if (info.app_date.day == 0)
			 return 0;

		 scanf(" %c%d %c%d", &sep, &info.app_date.app_month, &sep, &info.app_date.year);

		 printf("Thanks for time!!\n Do you want to add one more person?(Y/N)");
		 scanf(" %c", &cont);
		 printf("\n-----------------------------------------------------------------------------------------------\n");
		 insert(list, info); //insert taken informations

		 switch (cont)
		 {
		 case 'Y':
		 case 'y':
			 break;
		 case 'N':
		 case 'n': sent = false;
			 break;
		 default: {
			 printf("Wrong Answer!!\nExited!");
			 return 0;}
		 }

	 }
	 return 1;
 }

 int give_Number(waiting_Apps_q *list, users_s *person, telephones_s *num) {
	 if (is_Empty_q(list)) {
		 printf("There isn't any application");
		 return EMPTY_TEL;
	 }
	 push_users(person, remove(list));
	 person->accepted_Apps[person->top].number = pop_telep(num);

	 printf("New user is accepted:\n%s\t%d", person->accepted_Apps[person->top].name, person->accepted_Apps[person->top].number);

	 return person->accepted_Apps[person->top].number;
 }

 int search_User(users_s *list, int phoneNum) {
	 for (int i = list->top; i > -1; i--) {
		 if (list->accepted_Apps[i].number == phoneNum)
			 return i;
	 }
	 printf("User has number %d was not found!!", phoneNum);

	 return -1;

 }



 void cancel_User(users_s *person, telephones_s *numbers, int order) {

	 application carrier;
	 users_s temp;
	 init_users(&temp);

	 if (is_Full_telep(numbers))
		 printf("\nThere isn't anyone which is use telephone");
	 else {

		 for (int i = person->top; i >= order; i--) {
			 push_users(&temp, pop_users(person));
		 }

		 carrier = pop_users(&temp);
		 push_telep(numbers, carrier.number);

		 while (!is_Empty_users(&temp))
			 push_users(person, pop_users(&temp));


		 printf("%s is deleted", carrier.name);
	 }
 }

