#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
The program is a delivery schedule application that records courier's 
progress on their current jobs. It asks for basic inofrmation and several
inputs from the user regarding their deliveries for the day.
It can also output work receipts that the user can print.
A more detailed explanation of the features can be found in the documentation

This program uses some functions from the program called "struct07.cpp" 
made by Mr. J. Catalan. The read, write and databases function in the program
heavily based on his program

Authors: Miro Hernandez & Joaquin Gasmido


*/

//declaration of classes
//class for the start menu of the program
class MenuObject {
	public:
		char choice;
		int start;

    	
    	MenuObject() {
    		choice = 0;
    		start = 0;
		}
		
		void display () {
			int n;
			do {
				printf(" 'GASMIDO AND HERNANDEZ DELIVERY SERVICES'\n");
				printf("______________________________________________");
				
				printf("\n\nGOOD DAY VALUED EMPLOYEE!\n");
				printf("\nPlease select action you would like to do.\n");
				printf("\n1. Input Deliveries\n");
		        printf("2. Search Deliveries for the Day\n");
		        printf("3. Update/download Work Receipt\n");
		        printf("4. Recover lost Data\n");
		        printf("5. Exit Program\n");
		        printf("______________________________________________");
		        printf("\nChoice: ");
		        choice=fgetc(stdin);
				fgetc(stdin);
		
		    } while((choice<'1')&&(choice>'5'));		
		}
 
};


//class that contains the information of the delivery
class delivery {
	public:
	char address[20];
	char item[15];
	char time[10];
	char comments[30];
	
	int order;
	int quantity;
	
};
//class of counters used to store information of deliveries
class dbAppType {
	public:
		delivery addressdb[100];
		int n;
		char *fname;	
		int count;
	
};
//class of objects used in the program
class dbObject {
	public:
		
		dbAppType db[100]; 
		MenuObject menu;
		char date[20];
		char name[50];
		
		dbObject() {
			db->count = 0;
		}
		
		void start();
		void Search();
		void Input();
		void CreateReceipt();
		void Exit();
		int getDelimitedItem(char s[],char d, FILE *fp);
		void savePoint(int *p);
		void WriteToFile(dbAppType *db, const char str[20]);
		void CreateReceipt(dbAppType *db);
		void ReadFromFile(dbAppType *db, const char str[20]);
		
		
};




int main (void) {
	
	dbObject ab;
	ab.start();
	
}
//function that runs the different functions declared earlier based on users selection
void dbObject::start() {
	int n;
	printf("Driver Name: ");
	gets(name);
	printf("Enter the Date today: ");
	gets(date);
	while(menu.choice != '5') {
		system("Pause");
		system("CLS");
		menu.display();
		switch (menu.choice) {
          case '1':
             Input();
             break;
          case '2':
             Search();
             break;
          case '3':
             CreateReceipt(db);
             break;
          case '4':
          	ReadFromFile(db, "savePoint.dat");
          	break;
          case '5':
          	Exit();
          	break;
        }
	}
	
}

//function that is used to transfer across arrays of deliveries stored into classes
int dbObject::getDelimitedItem(char s[],char d, FILE *fp) {
	int c;
    int i=0;
    c=0;
    s[i]=0;
    while (!feof(fp)) {
        c=fgetc(fp);
        if (c==d||c=='\n'||c==10||c==EOF) return i;
        else {
            s[i]=c;
            i++;
            s[i]=0;
        }
    }
    return i;
}

void dbObject::Input() {
	  if (db->count == 20) {
      printf("Maximum Delivery Limit Reached.");
      return;
	   }
	   //gets input from user and stores into arrays declared in classes earlier
	   printf("Delivery address: ");
	   gets(db->addressdb[db->count].address);
	   printf("Item to be delivered: ");
	   gets(db->addressdb[db->count].item);
	   printf("Time item was delivered: ");
	   gets(db->addressdb[db->count].time);
	   printf("Comment on delivery: ");
	   gets(db->addressdb[db->count].comments);
	   
	   printf("Delivery order: ");
	   scanf("%i",&(db->addressdb[db->count].order));
	   printf("Quantity of Item: ");
	   scanf("%i",&(db->addressdb[db->count].quantity));
	   
	   getchar();
	   db->count++;
	   savePoint(&menu.start);// savepoint that writes data every iteration
} 
//function that searches for deliveries based on the item delivered
void dbObject::Search() {
	char s[10];
   int i, disp=0;

   printf("\nSearch Delivery Info of an Item: ");
   gets(s);
   for (i=0;i<db->count;i++) {
      if (stricmp(s,db->addressdb[i].item)==0) {
	    printf("\nDelivery address: %s\n",db->addressdb[i].address);
        printf("\nItem delivered: %s\n",db->addressdb[i].item);
        printf("\nTime item was delivered: %s\n",db->addressdb[i].time);
        printf("\nComment on delivery: %s\n",db->addressdb[i].comments);
        printf("\nDelivery order: %i\n",db->addressdb[i].order);
        printf("\nQuantity: %i\n",db->addressdb[i].quantity);
        disp++;
        if (disp % 3 == 0) getchar();
      }
   }
   if (disp==0) { //displays when the item searched for was not part of the delivery of the day
      printf("%s The item was not part of your delivery for today! \n",s);
   }
}

void dbObject::CreateReceipt(dbAppType *db) {
	//Info from Input function will be written to a txt file, and the text file in this code
	
	//displays what the receipt will look like
	FILE *fp;
	char x[100] = "Receipt for ";
	int i, choice = 0;
	printf("#######################################################\n");
	printf(" \t\t   Work Receipt\n");
	printf("Driver Name: %s\n", name);//includes personalized data
	printf(" \t   Date: %s\n", date);// like date and name
	printf(" \t   Total Deliveries Made %d\n", (db->count));//total deliveries done on that day
	for (i=0;i<db->count;i++) {		//for loop that prints every info that will be on the receipt
		printf("\n\n\n");
	 	printf("\nDelivery order: %i\n",db->addressdb[i].order);
	 	printf("\nItem delivered: %s\n",db->addressdb[i].item);
	    printf("\nDelivery address: %s\n",db->addressdb[i].address);
        printf("\nTime item was delivered: %s\n",db->addressdb[i].time);
        printf("\nComment on delivery: %s\n",db->addressdb[i].comments);
        printf("\nQuantity: %i\n",db->addressdb[i].quantity);
   }
	
	printf("#######################################################\n");
	//asks the user for an option
	printf("1. Print this Receipt\n");
	printf("2. Return\n");
	printf(">>>> ");
	scanf("%d", &choice);
	fflush(stdin);
	strcat(x,date);
	strcat(x,".txt");	//concatinates string so that the receipt is unique
	if (choice == 1){	// according to the date given by the user
			fp = fopen(x, "w"); //w mode so that it clears previous receipt if the 
								//user made a mistake and the receipt doesn't dupicate
			fprintf(fp, "#######################################################\n");
			fprintf(fp, " \t\t   Work Receipt\n");
			fprintf(fp, "Driver Name: %s\n", name);
			fprintf(fp, " \t   Date: %s\n", date);
			fprintf(fp, " \t   Total Deliveries Made %d\n", (db->count));
				for (i=0;i<db->count;i++) {		//for loop that puts the data into a uniquely named text file
					fprintf(fp, "\n\n\n");
		 			fprintf(fp, "\nDelivery order: %i\n",db->addressdb[i].order);
		 			fprintf(fp, "\nItem delivered: %s\n",db->addressdb[i].item);
		    		fprintf(fp, "\nDelivery address: %s\n",db->addressdb[i].address);
   	     			fprintf(fp, "\nTime item was delivered: %s\n",db->addressdb[i].time);
   	     			fprintf(fp, "\nComment on delivery: %s\n",db->addressdb[i].comments);
    	    		fprintf(fp, "\nQuantity: %i\n",db->addressdb[i].quantity);
   					}
	
			fprintf(fp, "#######################################################\n");
			fclose(fp);
	} else {
		return; //return to menu option;
	}


	
	
	printf("\nReceipt successfully printed!\n");
	
}

void dbObject::Exit() {
	printf("Thank you for using our program!");

	exit(0); // exits the program
}

void dbObject::savePoint(int *n) {
	FILE *fp;
// function that writes the info to savePoint.dat every iteration of Input()
// checks if its the first iteration of Input() so that it can utilize w mode
	if (*n == 0){
		*n = 1; // changes the value so that the next iterations would not 
				// use write mode which overwrites every iteration of data
		fp = fopen("savePoint.dat","w");
		fclose(fp); 
		WriteToFile(db, "savePoint.dat");
	}else if (*n == 1){
		WriteToFile(db, "savePoint.dat"); //write to file uses append mode

	}
	
	
}
// accepts a database and a unique string that it will use to name the file
void dbObject::WriteToFile(dbAppType *db, const char str[20]) {
   FILE *fp;
   int i;
   

   fp = fopen(str,"a");
   if (fp==NULL) {
      printf("\nCannot Open %s: ", str);
   }
   else {
      fprintf(fp,"%i\n",db->count);
      //for (i=0; i<db->count; i++) 
          fprintf(fp,"%s|%s|%s|%s|%i|%i\n",db->addressdb[i].address,
                  db->addressdb[i].item,db->addressdb[i].time,
                  db->addressdb[i].comments, db->addressdb[i].order, db->addressdb[i].quantity);
      
      fclose(fp);
   }
}
//recover option when the program closes unexpectedly
//overwrites the inputted values by the user (on the program not the dat file)
//resusable , not just applicable on savePoint.dat
void dbObject::ReadFromFile(dbAppType *db, const char str[20]) {
   FILE *fp;
   int i;
   char s[100];

   fp = fopen(str,"r");
   if (fp==NULL) {
      printf("\nCannot Open %s\n: ",db->fname);
   }
   else {
      getDelimitedItem(s,'|',fp);
      db->count = atoi(s);
      for (i=0; i<db->count; i++) {
          getDelimitedItem(db->addressdb[i].address,'|',fp);
          getDelimitedItem(db->addressdb[i].item,'|',fp);
          getDelimitedItem(db->addressdb[i].time,'|',fp);
          getDelimitedItem(db->addressdb[i].comments,'|',fp);
          getDelimitedItem(s, '|',fp);
          db->addressdb[i].order = atoi(s);
          getDelimitedItem(s,'|',fp);
          db->addressdb[i].quantity = atoi(s);
      }
      fclose(fp);
      if (db->count>0) {
         printf("%i records read. \n",db->count);
      }
   }
}

