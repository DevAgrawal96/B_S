#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include<string.h>
#include <graphics.h>
#define LEN 100
//**************************************************************************//
		// FUNCTIONS THAT ARE USED IN PROGRAM //
//**************************************************************************//

void lineHor(int, int, int) ;   //drawing horizental line
void lineVer(int, int, int) ;   //drawing vertical line
void box(int,int,int,int) ;     //drawing a box
void mainMune(void);            //function that is used for represent main manu
void manu(void);                //this is used in main manu
void gra2();                    //drawing for front page
void addToFile(void);           //add record in initial file
void displayList(void);         //display list of accountsfrom initial file
void updateBalance(int,double); //update balance at the time of transaction etc
void deleteAccount(int);        //delete a record from initial file
void modify(void);              //modified  record from initial file
int lastAccno(void);            //return last account number
int foundAccount(int);          //check account
char *returnName(int);          //return name
char *returnFname(int);         //return father name
char *returnAddress(int);       //return address
double giveBalance(int);        //save balance time to time in account.rec and initial.txt
int recordno(int);              //return total number of record
void newAccount(void);          //opening new account
void editAccount(void);         //edit account
void  display(void) ;           //display a specific account
void help(void);                //function that give help about program
void transaction(void);         //transaction in account
void  addToFileA(void) ;        //add a record in account.rec file
void  delete_account(int) ;     //delete a record from account.rec
void Delete(void);              //delete record using delete_account()&deleteAccount()
int  noOfDays(int, int, int, int, int, int) ; //count no of days
double calculateInterest(int, double) ;       //calculate interest

//**************************************************************************//
       // INITIAL STRUCTURE WHICH USED FOR  STORE DATA OF NEW ACCOUNT //
	 // IN INITIAL.REC FILE AND RETURN DATA FROM INITIAL FILE //
//**************************************************************************//

struct initial
{
   int accno;       //account no.
   char name[25];
   char fName[25];
   char address[60];
   double balance;
};
struct initial ini[LEN];

//**************************************************************************//
	// ACCOUNT STRUCTURE WHICH IS USED FOR STORE DATA OF ACCOUNTS //
	// IN ACCOUNT.REC FILE AND RETURN DATA FROM ACCOUNT.REC FILE  //
//**************************************************************************//

struct account
{
   int   accno ;       //account no.
   char  type[10] ;      // Cheque or Cash
   int   dd, mm, yy ;   // Date
   char  tran ;       // Deposit or Withdraw
   double  interest, amount, balance ;
};
struct account acc[LEN];

//**************************************************************************//
	      // FUNCTION THAT IS USED FOR CLEAR A LINE //
//**************************************************************************//

void clear(int col, int row)
{
   int i;
   for (i=col; i<=78; i++)     //print spaces in one line
   {
      gotoxy(i,row) ;
      printf(" ") ;
   }
}

//**************************************************************************//
     // FUNCTION THAT IS USED FOR DRAW HORIZONTAL LINE USING CHARACTER //
//**************************************************************************//

void lineHor(int column1, int column2, int row)
{
   char c = 205;
   for ( column1=column1;column1<=column2; column1++ )
   {
      gotoxy(column1,row) ;
      cprintf("%c",c);
   }
}

//**************************************************************************//
      // FUNCTION THAT IS USED FOR DRAW VERTICAL LINE USING CHARACTER //
//**************************************************************************//

void lineVer(int row1, int row2, int column)
{
   char c = 186;
   for ( row1=row1; row1<=row2; row1++ )
   {
      gotoxy(column,row1) ;
      printf("%c",c) ;
   }
}

//**************************************************************************//
	//  FUNCTION THAT IS USED FOR DRAW A BOX USING HORIZONTAL //
		// LINES AND VERTICAL LINES FUNCTIONS //
//**************************************************************************//

void box(int column1, int row1, int column2, int row2)
{

   char c1=201 ,c2=187 ,c3=200 ,c4=188 ;
   gotoxy(column1,row1) ;
   printf("%c",c1) ;
   gotoxy(column2,row1) ;
   printf("%c",c2) ;
   gotoxy(column1,row2) ;
   printf("%c",c3) ;
   gotoxy(column2,row2) ;
   printf("%c",c4) ;
   column1++ ;
   column2-- ;
   lineHor(column1,column2,row1) ; //drawing horizental line
   lineHor(column1,column2,row2) ;
   column1-- ;
   column2++ ;
   row1++ ;
   row2-- ;
   lineVer(row1,row2,column1) ;
   lineVer(row1,row2,column2) ;
}

//**************************************************************************//
   // FUNCTION THAT IS RETURN LAST ACCOUNT NUMBER FROM INITIAL.REC FILE //
//**************************************************************************//

int lastAccno(void)
{
   FILE *fptr;              //file pointer
   int n=0;
   int t;
   if( (fptr = fopen("initial.txt","r")) == NULL) //open account for reading
     return 0;
   else
   {
      while( fread(&ini[n], sizeof(ini[n]), 1, fptr) == 1)
      {
	 t = ini[n].accno;
	 n++;
      }
      fclose(fptr);     //close file
      return t;
   }
}

//**************************************************************************//
     // FUNCTION USED FOR OPEN A NEW ACCOUNT IN INITIAL.REC FILE //
//**************************************************************************//

void newAccount(void)
{

   char numstr[20];
   char ch ;
   int i, valid ;
   struct date d;  //built in structure for date

   clrscr();
   ini[0].accno = lastAccno()+1;
   acc[0].accno = ini[0].accno;
   box(1,2,80,24);       //draw a box
   lineHor(2,79,4);      //draw a line
   lineHor(2,79,22);      //draw a line
   gotoxy(70,1);
   printf("<0> = EXIT");
   textbackground(WHITE);
   gotoxy(3,3) ;
   for (i=1; i<=76; i++)
   printf(" ") ;
   textbackground(BLACK);textcolor(BLUE+BLINK);
   textbackground(WHITE);
   gotoxy(32,3) ;
   printf("OPEN NEW ACCOUNT");
   textcolor(LIGHTGRAY); textbackground(BLACK); //return in default color
   getdate(&d);
   acc[0].dd = d.da_day;           //save date in structure
   acc[0].mm = d.da_mon;
   acc[0].yy = d.da_year;
   gotoxy(5,5);
   printf("Date : %d / %d / %d",acc[0].dd,acc[0].mm,acc[0].yy);
   gotoxy(5,7);
   printf("ACCOUNT NO # %d",acc[0].accno);
   gotoxy(5,9);
   printf("NAME          : ");
   gotoxy(5,11);
   printf("FATHER'S NAME : ");
   gotoxy(5,13);
   printf("ADDRESS       : ");
   gotoxy(5,15);
   printf("INITIAL DEPOSITE :");

   do                  //get name of a person
   {
      clear(21,9) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER NAME OF THE PERSON" );
      valid = 1 ;
      gotoxy(21,9) ;
      gets(ini[0].name) ;
      strupr(ini[0].name) ;     //convert string in uppercase
      if (ini[0].name[0] == '0')
	 return ;
      if (strlen(ini[0].name) == 0 || strlen(ini[0].name) > 25)
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 printf("NAME SHOULD NOT BE BLANK OR GREATER THAN 25") ;
	 getch() ;
      }
   } while (!valid) ;

   do                     //get father name of a person
   {
      clear(21,11) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER FATHER'S NAME OF THE PERSON" );
      valid = 1 ;
      gotoxy(21,11) ;
      gets(ini[0].fName) ;
      strupr(ini[0].fName) ;           //convert string in uppercase
      if (ini[0].fName[0] == '0')
	 return ;
      if (strlen(ini[0].fName) == 0 || strlen(ini[0].fName) > 25)
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 printf("NAME SHOULD NOT BE BLANK OR GREATER THAN 25") ;
	 getch() ;
      }
   } while (!valid) ;

   do                                //get address of person
   {
      clear(21,13) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER ADDRESS OF THE PERSON" );
      valid = 1 ;
      gotoxy(21,13) ;
      gets(ini[0].address) ;
      strupr(ini[0].address) ;       //convert string in uppercase
      if (ini[0].address[0] == '0')
	 return ;
      if (strlen(ini[0].address) == 0 || strlen(ini[0].address) > 44)
      {
	 valid = 0 ;
	 clear(5,23);
	 gotoxy(5,23) ;
	 printf("ADDRESS SHOULD NOT BE BLANK OR GREATER THAN 44") ;
	 getch() ;
      }
   } while (!valid) ;

   do                      //get initial deposit from person
   {
      clear(24,15) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER INITIAL AMOUNT TO BE DEPOSIT" );
      valid = 1 ;
      gotoxy(24,15) ;
      gets(numstr) ;
      ini[0].balance = atof(numstr);    //convert character array into float
      if (numstr[0] == '0')
	 return ;

      if ( ini[0].balance < 500)
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("TRANSACTION SHOULD NOT BE LESS THAN 500          ") ;
	 getch() ;
      }
   } while (!valid) ;
   clear(5,23);
   do
   {
      clear(7,19) ;
      valid = 1 ;
      gotoxy(7,19) ;
      printf("Do you want to save the record (y/n) : " );
      ch = getche() ;
      if (ch == '0')
	 return ;
      ch = toupper(ch) ;
   } while (ch != 'N' && ch != 'Y') ;
   if (ch == 'N')
      return ;

   strcpy(acc[0].type,"INITIAL");         //copy string
   acc[0].interest = 0.0;
   acc[0].balance = ini[0].balance;
   acc[0].amount = acc[0].balance;
   acc[0].tran = 'D';
   addToFile();
   addToFileA();
}

//**************************************************************************//
	// FUNCTION THAT IS ADD  NEW DATA IN INITIAL.REC FILE //
//**************************************************************************//

void addToFile(void)
{
   FILE *fptr;
   fptr = fopen("initial.txt","a");
   fwrite (ini, sizeof(ini[0]), 1, fptr);
   fclose(fptr);
}

//**************************************************************************//
	// FUCTION THAT IS USED FOR ADD NEW DATA IN ACCOUNT .REC FILE //
//**************************************************************************//

void addToFileA(void)
{
   FILE *fptr;
   fptr = fopen("account.rec","a");
   fwrite (acc, sizeof(acc[0]), 1, fptr);
   fclose(fptr);
}

//**************************************************************************//
	   // FUNCTION USED FOR TRANSACTION IN ACCOUNT //
//**************************************************************************//

void transaction(void)
{
   int accno;
   int d,m,y;
   int i ,valid;
   char strnum[10];
   char name[25];
   char fName[25];
   char address[60];
   double balance,amt,amount,interest;
   char tran;
   char type[10];
   char tm[20];
   char ch;
   struct date d1;
   clrscr();
   box(20,7,50,12);
   gotoxy(43,6);
   printf("<0> = EXIT");
   textcolor(BLUE+BLINK) ;
   textbackground(WHITE) ;
   gotoxy(26,8) ;
   cprintf(" ENTER ACCOUNT NO ") ;
   textcolor(LIGHTGRAY) ;
   textbackground(BLACK) ;
   gotoxy(22,10);
   printf("ACC N0 : ");
   gets(strnum);
   accno=atoi(strnum);

   if(accno == 0)
      return;

   if(foundAccount(accno) == 0)
   {
      gotoxy(22,14);
      cprintf("ACCOUNT NO IS NOT FOUND");
      getch();
      return;

   }
   clrscr();
   box(1,2,80,24);
   lineHor(2,79,4);
   lineHor(2,79,22);
   gotoxy(70,1);
   printf("<0> = EXIT");
   textbackground(WHITE) ;
   gotoxy(3,3) ;
   for (i=1; i<=76; i++)
   cprintf(" ") ;
   textbackground(BLACK) ;
   textcolor(BLUE+BLINK) ;
   textbackground(WHITE) ; //return to default color
   gotoxy(30,3) ;
   cprintf("TRANSACTION IN ACCOUNT") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;  //return to default color
   getdate(&d1);
   d = d1.da_day;
   m = d1.da_mon;
   y = d1.da_year;
   gotoxy(5,5);
   printf("Date : %d / %d / %d",d,m,y);
   gotoxy(5,7);
   printf("Account No # %d",accno);
   box(25,9,55,13);
   strcpy(name,returnName(accno));
   strcpy(fName,returnFname(accno));
   strcpy(address,returnAddress(accno));
   balance = giveBalance(accno);
   gotoxy(27,10);
   printf("Name        : %s",name);
   gotoxy(27,11);
   printf("Father Name : %s",fName);
   gotoxy(27,12);
   printf("Address     : %s",address);
   gotoxy(5,15);
   printf("Last Balance : Rs. %.2lf",balance);

   do
   {
      clear(5,17) ;
      valid = 1 ;
      clear(5,23) ;
      gotoxy(5,23) ;
      cprintf("Do You Want to Deposit Or Withdraw ") ;
      gotoxy(5,17) ;
      printf("Deposit or Withdraw (D/W) : ") ;
      tran = getche() ;
      if (tran == '0')
	 return ;
      tran = toupper(tran) ;        //convert character into upper case
   } while (tran != 'D' && tran != 'W') ;
   do
   {
      clear(5,19) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER TRANSACTION BY CASH OR CHEQUE" );
      valid = 1 ;
      gotoxy(5,19) ;
      printf("(Cash/Cheque) : " );
      gets(type) ;
      strupr(type) ;   //covert string into upper case
      if (type[0] == '0')
	 return ;
      if (strcmp(type,"CASH") && strcmp(type,"CHEQUE")) //copare string
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("ENTER CORRECTLY                       ") ;
	 getch() ;
      }
   } while (!valid) ;
   do
   {
      clear(5,21) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER AMOUNT FOR TRANSACTION" );
      valid = 1 ;
      gotoxy(5,21) ;
      printf("Amount : Rs." );
      gets(tm) ;
      amt = atof(tm) ;
      amount = amt ;
      if (tm[0] == '0')
	 return ;
      if ((tran == 'W' && amount > balance) || (amount < 1))
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("INVALID DATA ENTERED               ") ;
	 getch() ;
      }
   } while (!valid) ;
   clear(5,23) ;
   do
   {
      clear(40,20) ;
      valid = 1 ;
      gotoxy(40,20) ;
      printf("Save transaction (y/n): ") ;
      ch = getche() ;
      if (ch == '0')
	 return ;
      ch = toupper(ch) ;
   } while (ch != 'N' && ch != 'Y') ;
   interest = calculateInterest(accno,balance) ;

   if (tran == 'D')
      balance = balance + amount + interest ;
   else
      balance = (balance - amount) + interest ;

   updateBalance(accno,balance) ;

   acc[0].accno = accno;
   acc[0].dd = d;
   acc[0].mm = m;
   acc[0].yy = y;
   acc[0].balance = balance;
   strcpy(acc[0].type , type);
   acc[0].tran = tran;
   acc[0].interest = interest;//interest, amount, balance ;
   acc[0].amount = amount;
   addToFileA();
   getch();
}

//**************************************************************************//
    // FUNCTION THAT IS RETURN NAME OF PERSON FROM INITIAL.REC FILE  //
//**************************************************************************//

char *returnName(int a_no)
{
   FILE *fptr;
   long int offset;

   char name[30];

   if( (fptr = fopen("initial.txt","r") ) == NULL)
      exit(1);
   offset = (a_no - 1) * sizeof(ini[0]);

   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found");
      exit(1);
   }
   fread(&ini[a_no],sizeof(ini[a_no]),1,fptr);
    {

      strcpy(name, ini[a_no].name);
    }
    return name;
}

//**************************************************************************//
   // FUNCTION THAT IS RETURN FATHER NAME OF PERSON FROM INITIAL.REC FILE //
//**************************************************************************//

char *returnFname(int a_no)
{
   FILE *fptr;
   long int offset;

   char fName[25];

   if( (fptr = fopen("initial.txt","r") ) == NULL)
      exit(1);
   offset = (a_no - 1) * sizeof(ini[0]);

   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found ");
      exit(1);
   }
   fread(&ini[a_no],sizeof(ini[a_no]),1,fptr);
    {

      strcpy(fName, ini[a_no].fName);
    }
    return fName;
}

//**************************************************************************//
    // FUNCTION THAT IS RETURN ADDRESS OF A PERSON FROM INITIAL.REC FILE //
//**************************************************************************//

char *returnAddress(int a_no)
{
   FILE *fptr;
   long int offset;

   char address[30];

   if( (fptr = fopen("initial.txt","r") ) == NULL)
      exit(1);
   offset = (a_no - 1) * sizeof(ini[0]);

   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found ");
      exit(1);
   }
   fread(&ini[a_no],sizeof(ini[a_no]),1,fptr);
    {

      strcpy(address, ini[a_no].address);
    }
    return address;
}

//**************************************************************************//
	       // THIS FUNCTION  ADD DEPOSIT IN BALANCE  //
//**************************************************************************//

double giveBalance(int a_no)
{

   FILE *fptr;
   long int offset;
   long  balance;
   if( (fptr = fopen("initial.txt","r") ) == NULL)
      exit(1);
   offset = (a_no - 1) * sizeof(ini[0]);
   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found");
      exit(1);
   }
   fread(&ini[a_no],sizeof(ini[a_no]),1,fptr);
    {
    balance = ini[a_no].balance;
    }
    return balance;
}

//**************************************************************************//
	  //  FUNCTION USED FOR CALCULATE INTEREST //
//**************************************************************************//

double calculateInterest(int accno, double balance)
{
   FILE *fptr;
   int d1,m1,y1;
   int d2, m2, y2 ;
   struct date d;
   double interest=0 ;
   int days,months=0 ;
   int count = 0;

   if( (fptr = fopen("account.rec","r")) == NULL)
     return 0;

   while( fread(&acc[count], sizeof(acc[0]), 1, fptr) == 1)
   {

      if(accno == acc[count].accno)
      {
	   d1 = acc[count].dd;
	   m1 = acc[count].mm;
	   y1 = acc[count].yy;
	   break;
      }
      count++;
   }

   getdate(&d);
   d2 = d.da_day ;
   m2 = d.da_mon ;
   y2 = d.da_year ;

   if ((y2<y1) || (y2==y1 && m2<m1) || (y2==y1 && m2==m1 && d2<d1))
      return interest ;
   days = noOfDays(d1,m1,y1,d2,m2,y2) ;

   if (days >= 30)
   {
      months = days/30 ;
      interest = ((balance*2)/100) * months ;
   }
   fclose(fptr) ;
   return interest ;

}

//**************************************************************************//
	 //  FUNCTION USED FOR COUNTING NUMBER OF DAYS //
//**************************************************************************//

int noOfDays(int d1, int m1, int y1, int d2, int m2, int y2)
{
   static int month[] = {31,28,31,30,31,30,31,31,30,31,30,31} ;
   int days = 0 ;
   while (d1 != d2 || m1 != m2 || y1 != y2)
   {
      days++ ;
      d1++ ;
      if (d1 > month[m1-1])
      {
	 d1 = 1 ;
	 m1++ ;
      }
      if (m1 > 12)
      {
	 m1 = 1 ;
	 y1++ ;
      }
   }
   return days ;
}

//**************************************************************************//
     // FUNCTION THAT IS RETURN UPDATE BALANCE FROM INITIAL.REC FILE //
//**************************************************************************//

void updateBalance(int a_no,double bal)
{
   FILE *fptr;
   long int offset;
   int acc = a_no -1;


   fptr = fopen("initial.txt","r+");

   ini[acc].balance = bal;


   offset = (a_no - 1) * sizeof(ini[0]);

   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found ");
      exit(1);
   }
   fwrite(&ini[acc], sizeof(ini[0]),1,fptr);

   fclose(fptr);
}

//**************************************************************************//
     // FUNCTION THAT IS USED FOR CHECK  A RECORD FROM INITIAL.REC  //
//**************************************************************************//

int foundAccount(int ac)
{
   int found = 0;
   FILE *fptr;
   int count = 0;

   if( (fptr = fopen("initial.txt","r")) == NULL)
     return 0;

   while( fread(&ini[count], sizeof(ini[0]), 1, fptr) == 1)
   {

      if(ac == ini[count].accno)
      {
	    found = 1;
	    break;
      }
      count++;
   }
   fclose(fptr);
   return found;

}

//**************************************************************************//
      // THIS FUNCTION RETURN A COMPLETE RECORD FROM INITIAL.REC FILE //
//**************************************************************************//

void display(void)
{
   int d1,m,y,n = 0;
   int accno;
   int row = 8, flag = 0 ;
   char numstr[10];
   char name[25];
   char fName[25];
   char address[60];
   FILE *fptr;
   struct date d;
   clrscr();

   box(20,7,50,12);
   gotoxy(43,6);
   printf("<0> = EXIT");
   textcolor(BLUE+BLINK) ; textbackground(WHITE) ;
   gotoxy(26,8) ;
   cprintf(" ENTER ACCOUNT NO ") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(22,10);
   printf("ACC N0 : ");
   gets(numstr);
   accno=atoi(numstr);
   if(accno == 0)
      return;

   if(foundAccount(accno) == 0)
   {
      gotoxy(22,14);
      cprintf("ACCOUNT NO IS NOT FOUND");
      getch();
      return;

   }

   clrscr();

   box(1,1,80,24);
   lineHor(2,79,22);
   getdate(&d);
   d1 = d.da_day;
   m = d.da_mon;
   y = d.da_year;
   strcpy(name, returnName(accno));
   strcpy(fName, returnFname(accno));
   strcpy(address, returnAddress(accno));
   gotoxy(64,3);
   printf("DATE : %d/%d/%d",d1,m,y);
   textcolor(WHITE) ;
   gotoxy(2,3) ;
   printf("ACCOUNT NO # %d",accno) ;
   gotoxy(30,2);
   printf("NAME       : %s",name);
   gotoxy(30,3);
   printf("FATHER NAME: %s",fName);
   gotoxy(30,4);
   printf("ADDRESS    : %s",address);
   lineHor(2,79,5);
   textbackground(WHITE) ;
   gotoxy(2,4) ;
   textcolor(BLUE);
   gotoxy(3,6);
   printf(" DATE       PARTICULAR     DEPOSIT      WITDRAW     INTEREST		BALANCE ");
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   lineHor(2,79,7);
   fptr = fopen("account.txt","r");
   while( fread(&acc[n], sizeof(acc[n]), 1, fptr) ==1)
   {
      if (accno == acc[n].accno)
      {
	 flag = 0 ;
	 delay(10) ;
	 gotoxy(3,row) ;
	 printf("%d/%d/%d",acc[n].dd,acc[n].mm,acc[n].yy) ;
	 gotoxy(16,row) ;
	 printf("%s",acc[n].type) ;
	 if (acc[n].tran == 'D')
	    gotoxy(30,row) ;
	 else
	    gotoxy(43,row) ;
	 printf("%.2lf",acc[n].amount);
	 gotoxy(57,row) ;
	 printf("%.2lf",acc[n].interest) ;
	 gotoxy(71,row) ;
	 printf("%.2lf",acc[n].balance) ;
	 row++ ;

	 if (row == 22)
	 {
	    flag = 1 ;
	    row = 8 ;
	    gotoxy(4,23) ;
	    printf("press a key to continue..." );
	    getch() ;
	    clrscr() ;
	    box(1,1,80,24);
	    lineHor(2,79,22);
	    textcolor(WHITE) ;
	    gotoxy(2,3) ;
	    cprintf("ACCOUNT NO # %d",accno) ;
	    gotoxy(30,2);
	    cprintf("NAME       : %s",name);
	    gotoxy(30,3);
	    cprintf("FATHER NAME: %s",fName);
	    gotoxy(30,4);
	    cprintf("ADDRESS    : %s",address);
	    lineHor(2,79,5);
	    textbackground(WHITE) ;
	    gotoxy(2,4) ;
	    textcolor(BLUE);
	    gotoxy(3,6);
	    cprintf(" DATE       PARTICULAR     DEPOSIT      WITDRAW     INTEREST	BALANCE ");
	    textcolor(LIGHTGRAY) ;
	    textbackground(BLACK) ;
	    lineHor(2,79,7);
	 }
      }
      n++;
   }
   fclose(fptr) ;
   if (!flag)
   {
      gotoxy(4,23) ;
      printf("press a key to continue...") ;
      getch() ;
   }
}

//**************************************************************************//
     // FUNCTION THAT IS DISPLAY ALL RECORD FROM  INITIAL.REC FILE //
//**************************************************************************//

void displayList(void)
{
   FILE *fptr;
   int n = 0,i;
   struct date d;
   int d1,m,y;
   box(1,1,80,24);
   lineHor(2,79,22);
   lineHor(2,79,3);
   getdate(&d);
   d1 = d.da_day;
   m = d.da_mon;
   y = d.da_year;
   gotoxy(60,2);
   printf("DATE : %d/%d/%d",d1,m,y);
   textcolor(BLUE+BLINK) ; textbackground(WHITE) ;
   gotoxy(25,2) ;
   cprintf(" LIST OF ACCOUNT ") ;
   textbackground(WHITE) ;
   gotoxy(2,4) ;
   for (i=1; i<=78; i++) cprintf(" ") ;
   textcolor(RED);
   gotoxy(3,4);
   cprintf("ACC NO       NAME              FATHER NAME             BALANCE");
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   lineHor(2,79,5);
   if ( (fptr = fopen("initial.txt","r"))== NULL)
      printf("File is Empty.......");
   else
   {

      while( fread(&ini[n], sizeof(ini[n]), 1, fptr) ==1)
      {
	 gotoxy(3,6+n);
	 printf("%d",ini[n].accno);
	 gotoxy(15,6+n);
	 printf(" %s",ini[n].name);
	 gotoxy(33,6+n);
	 printf(" %s",ini[n].fName);
	 gotoxy(57,6+n);
	 printf(" %.2lf",ini[n].balance);
	 n++;
      }
      fclose(fptr);
   }
gotoxy(5,23) ;
printf("press a key to continue..." );
}

//**************************************************************************//
	 // FUCTION THAT IS USED FOR EDIT A RECORD FROM FILE //
//**************************************************************************//

void editAccount(void)
{
   int no,i,accno;
   char op,strnum[10];
   clrscr();
   box(22,8,58,20);
   lineHor(23,57,10);
   textbackground(WHITE) ;
   gotoxy(23,9) ;
   for (i=1; i<=35; i++) cprintf(" ") ;
   textbackground(BLACK) ;
   textcolor(BLACK+BLINK) ; textbackground(WHITE) ;
   gotoxy(30,9) ;
   cprintf("EDIT ACCOUNT SCREEN") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(29,12);
   printf("1 - MODIFY ACCOUNT");
   gotoxy(29,14);
   cprintf("2 - CLOSE ACCOUNT");
   gotoxy(29,16);
   cprintf("0 - QUIT");
   gotoxy(28,18);
   printf("ENTER YOUR CHOICE..");
   op = getche();
   switch(op)
   {
      case '0':
	 return;

      case '1':
	 modify();
	 break;
      case '2':
	 {
	 Delete();
	 break;
	 }


   }
}
//**************************************************************************//
    // FUNCTION THAT IS USED FOR MODIFIED A RECORD FROM INITIAL.REC FILE //
//**************************************************************************//

void modify(void)
{


   int acc ;
   FILE *fptr;
   long int offset;
   int i;
   int accno,txt;
   char ch;
   int modified=0, valid=0 ;
   char strnum[20];
   struct date d1;
   getdate(&d1);
   clrscr();

   box(20,7,50,12);
   gotoxy(43,6);
   printf("<0> = EXIT");
   textcolor(BLUE+BLINK) ; textbackground(WHITE) ;
   gotoxy(26,8) ;
   cprintf(" ENTER ACCOUNT NO ") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(22,10);
   printf("ACC N0 : ");
   gets(strnum);
   accno = atoi(strnum);

   if(accno == 0)
      return;

   if(foundAccount(accno) == 0)
   {
      gotoxy(22,14);
      cprintf("ACCOUNT NO IS NOT FOUND");
      getch();
      return;

   }
   clrscr();
   strcpy(ini[0].name,returnName(accno));
   strcpy(ini[0].fName, returnFname(accno));
   strcpy(ini[0].address, returnAddress(accno));
   box(1,2,80,24);
   lineHor(2,79,4);
   lineHor(2,79,22);
   gotoxy(1,1) ;
   printf("PRESS (0) TO EXIT") ;
   textbackground(WHITE) ;
   gotoxy(3,3) ;
   for (i=1; i<=76; i++) cprintf(" ") ;
   textbackground(BLACK) ;
   textcolor(BLACK+BLINK) ; textbackground(WHITE) ;
   gotoxy(30,3) ;
   cprintf("MODIFY ACCOUNT SCREEN") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(3,6);
   printf("ACCOUNT NO.# %d",accno);
   gotoxy(63,6);
   printf("DATE : %d/%d/%d",d1.da_day,d1.da_mon,d1.da_year);
   box(20,7,60,12);
   gotoxy(23,8);
   printf("NAME       : %s",ini[0].name);
   gotoxy(23,9);
   printf("FATHER NAME: %s",ini[0].fName);
   gotoxy(23,10);
   printf("ADDRESS    : %s",ini[0].address);
   do
   {
      clear(5,13) ;
      gotoxy(5,13) ;
      printf("Modify this account (y/n): ");
      ch = getche() ;
      if (ch == '0')
	 return ;
      ch = toupper(ch) ;
   } while (ch != 'N' && ch != 'Y') ;
   if (ch == 'N')
      return ;
   clear(5,13) ;
   gotoxy(5,15) ;
   printf("Name        : " );
   gotoxy(5,17) ;
   printf("Father Name : " );
   gotoxy(5,19) ;
   printf("Address     : " );
   do
   {
      clear(19,15) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER NAME or PRESS <ENTER> FOR NO CHANGE");
      valid = 1 ;
      gotoxy(21,15) ;
      gets(ini[0].name) ;
      strupr(ini[0].name) ;
      if (ini[0].name[0] == '0')
	 return ;
      if (strlen(ini[0].name) > 25 )
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("NAME SHOULD NOT BE GREATER THAN 25") ;
	 getch() ;
      }
   } while (!valid) ;

   if (strlen(ini[0].name) > 0)

      modified = 1 ;
   else

      strcpy(ini[0].name,returnName(accno) );

       do
   {
      clear(19,17) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER NAME or PRESS <ENTER> FOR NO CHANGE");
      valid = 1 ;
      gotoxy(21,17) ;
      gets(ini[0].fName) ;
      strupr(ini[0].fName) ;
      if (ini[0].fName[0]=='0')
	 return;
      if (strlen(ini[0].fName) > 25)
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("NAME SHOULD NOT BE GREATER THAN 25") ;
	 getch() ;
      }
   } while (!valid) ;
   if (strlen(ini[0].fName) > 0)
      modified = 1 ;
   else
      strcpy(ini[0].fName,returnFname(accno));
   do
   {
      clear(19,19) ;
      clear(5,23) ;
      gotoxy(5,23) ;
      printf("ENTER ADDRESS or PRESS <ENTER> FOR NO CHANGE");
      valid = 1;
      gotoxy(21,19) ;
      gets(ini[0].address) ;
      strupr(ini[0].address) ;
      if (ini[0].address[0] == '0')
	 return ;
      if (strlen(ini[0].address) > 25)
      {
	 valid = 0 ;
	 gotoxy(5,23) ;
	 cprintf("SHOULD NOT BE BLANK OR GREATER THAN 55") ;
	 getch() ;
      }
   } while (!valid) ;
   if (strlen(ini[0].address) > 0)
      modified = 1 ;
   else
      strcpy(ini[0].address,returnAddress(accno) );

   if (!modified)
      return ;
   clear(5,23) ;
   do
   {
      clear(5,18) ;
      gotoxy(35,19) ;
      printf("Do you want to save changes (y/n): ") ;
      ch = getche() ;
      if (ch == '0')
	 return ;
      ch = toupper(ch) ;
   } while (ch != 'N' && ch != 'Y') ;
   if (ch == 'N')
      return ;
   //==============================================================
   //==============================================================

   acc = accno -1;

   fptr = fopen("initial.txt","r+");

   ini[acc].accno = accno;
   strcpy(ini[acc].name, ini[0].name);
   strcpy(ini[acc].fName, ini[0].fName);
   strcpy(ini[acc].address, ini[0].address);
   ini[acc].balance = giveBalance(accno);


   offset = (accno - 1) * sizeof(ini[0]);

   if( fseek(fptr, offset, 0) !=0 )
   {
      printf("Record Not Found");
      exit(1);
   }
   fwrite(&ini[acc], sizeof(ini[0]),1,fptr);

   fclose(fptr);

   gotoxy(5,21) ;
   printf("Record Modified");
   gotoxy(5,23) ;
   printf("press a key to continue..." );

   getch();
}

//**************************************************************************//
     // FUNCTION THAT IS USED DELETION RECORD FROM BOTH FILES //
     // USING DELETEACCOUNT() AND DELETE_ACCOUNT() FUNCTIONS //
//**************************************************************************//

void Delete(void)
{
   int accno,i;

   char strnum[10],ch;

   struct date d1;
   getdate(&d1);
   clrscr();
   box(20,7,50,12);
   gotoxy(43,6);
   printf("<0> = EXIT");
   textcolor(BLUE+BLINK) ; textbackground(WHITE) ;
   gotoxy(26,8) ;
   cprintf(" ENTER ACCOUNT NO ") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(22,10);
   printf("ACC N0 : ");
   gets(strnum);
   accno=atoi(strnum);
   if(strnum[0]=='0')
      return;
    if(foundAccount(accno) == 0)
   {
      gotoxy(22,14);
      cprintf("ACCOUNT NO IS NOT FOUND");
      getch();
      return;
   }
       clrscr();
       strcpy(ini[0].name,returnName(accno));
       strcpy(ini[0].fName, returnFname(accno));
       strcpy(ini[0].address, returnAddress(accno));
       box(1,2,80,24);
       lineHor(2,79,4);
       lineHor(2,79,22);
   gotoxy(1,1) ;
   printf("PRESS (0) TO EXIT") ;
   textbackground(WHITE) ;
   gotoxy(3,3) ;
   for (i=1; i<=76; i++) cprintf(" ") ;
   textbackground(BLACK) ;
   textcolor(BLACK+BLINK) ; textbackground(WHITE) ;
   gotoxy(30,3) ;
   cprintf("CLOSE ACCOUNT SCREEN") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(3,6);
   printf("ACCOUNT NO.# %d",accno);
   gotoxy(63,6);
   printf("DATE : %d/%d/%d",d1.da_day,d1.da_mon,d1.da_year);
   box(20,7,60,12);
   gotoxy(23,8);
   printf("NAME       : %s",ini[0].name);
   gotoxy(23,9);
   printf("FATHER NAME: %s",ini[0].fName);
   gotoxy(23,10);
   printf("ADDRESS    : %s",ini[0].address);
   do
   {
      clear(5,13) ;
      gotoxy(5,17) ;
      printf("close this account (y/n): ");
      ch = getche() ;
      if (ch == '0')
	 return ;
      ch = toupper(ch) ;
   } while (ch != 'N' && ch != 'Y') ;
   if (ch == 'N')
      return ;
   deleteAccount(accno);
   delete_account(accno);
   gotoxy(5,21) ;
   printf("Record Delete");
   gotoxy(5,23) ;
   printf("press a key to continue..." );
   getch();
}

//**************************************************************************//
    // FUNCTION THAT IS DELETE A RECORD FROM INITIAL.REC FILE //
//**************************************************************************//

void deleteAccount(int acc_no)
{
   FILE *fptr;
   FILE *tptr;
   int n=0;

   fptr = fopen("initial.txt","r");//open the orginal file
   tptr = fopen("temp.txt","w");//opening a temparay file

   while(fread (&ini[n], sizeof(ini[n]),1,fptr)==1)
   {
      if(acc_no != ini[n].accno)
	 fwrite (&ini[n], sizeof(ini[0]), 1, tptr);
      n++;
   }
   fclose(fptr);
   fclose(tptr);

   fptr = fopen("initial.txt","w");//open the orginal file
   tptr = fopen("temp.txt","r");//opening a temparay file

   while(fread (&ini[n], sizeof(ini[n]),1,tptr)==1)
   {
      fwrite (&ini[n], sizeof(ini[0]), 1, fptr);
      n++;
   }
   fclose(fptr);
   fclose(tptr);


}

//**************************************************************************//
       // FUNCTION THAT IS DELETE A RECORD FROM ACCOUNT.REC FILE //
//**************************************************************************//

void delete_account(int acc_no)
{
   FILE *fptr;
   FILE *tptr;
   int n=0;

   fptr = fopen("account.txt","r");//open the orginal file
   tptr = fopen("temp.txt","w");//opening a temparay file

   while(fread (&acc[n], sizeof(acc[n]),1,fptr)==1)
   {
      if(acc_no != acc[n].accno)
	 fwrite (&acc[n], sizeof(acc[0]), 1, tptr);
      n++;
   }
   fclose(fptr);
   fclose(tptr);

   fptr = fopen("account.txt","w");//open the orginal file
   tptr = fopen("temp.txt","r");//opening a temparay file

   while(fread (&acc[n], sizeof(acc[n]),1,tptr)==1)
   {
      fwrite (&acc[n], sizeof(acc[0]), 1, fptr);
      n++;
   }
   fclose(fptr);
   fclose(tptr);
}

//**************************************************************************//
  // FUNCTION THAT IS RETURN TOTAL NUMBER OF RECORD IN INITIAL.REC FILE //
//**************************************************************************//

int txtordno(int a_no)
{
   FILE *fptr;
   int count = 0;

   if( (fptr = fopen("initial.txt","r")) == NULL)
     return 0;
   else
   {
      while( fread(&ini[count], sizeof(ini[0]), 1, fptr) == 1)
      {

	    if(a_no == ini[count].accno)
	       break;

	 count++;
      }
      fclose(fptr);
      return count;
   }
}

//**************************************************************************//
			 // HELP OF PRGRAM //
//**************************************************************************//

void help(void)
{
   clrscr();
   textmode(BW80);
   box(2,2,79,25);
   gotoxy(20,3);
   textcolor(RED);
   cprintf("*** WELCOME TO THE PROJECT OF BANKING ***") ;
   gotoxy(6,5);  printf("IN THIS PROJECT YOU CAN  KEEP  RECORD FOR  DAILY BANKING  TRANSACTIONS.");
   gotoxy(11,7);  printf(" THIS  PROGRAM IS CAPABLE OF HOLDING ANY No. OF ACCOUNTS.");
   gotoxy(3,9); printf("1) THE FIRST OPTION YOU CAN OPEN A NEW ACCOUNT OF A PARTICULAR PERSON.");
   gotoxy(3,11); printf("(NOTE:OPENING AMOUNT i.e.THE FIRST DEPOSIT SHOULD NOT BE LESS THAN RS.500.");
   gotoxy(3,13); printf("2) SECOND OPTION IS DISPLAYED BY GIVING SIMPLY THE ACCOUNT NO.THAT PERSON.");
   gotoxy(3,15); printf("3) IN THIRD OPTION YOU CAN SEE THE LIST OF ACCOUNTS.");
   gotoxy(3,17); printf("4) THROUGH FOURTH OPTION YOU CAN DO BANKING TRANSACTIONS (DEPOSIT/WITHDRAW).");
   gotoxy(3,19); printf("5) IN FIFTH OPTION YOU CAN CLOSE OR MODIFY ACCOUNT OF A PERSON." );
   gotoxy(3,21); printf("6) IN SIX OPTION THE HELP MENU IS DISPLAYED.");
   gotoxy(3,23); printf("7) In SEVENTH OPTION  YOU EXIT FROM PROJECT.");
   textcolor(BLUE+BLINK) ; textbackground(WHITE+BLINK) ;
   gotoxy(26,25) ; cprintf(" Press a key to continue ") ;
   textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
   gotoxy(25,2) ;
   getch();
}

//**************************************************************************//
		// HEART OF PROGRAM MAIN FUNCTION //
//**************************************************************************//

void main(void)
{
   gra2();
   mainMune();
 }

//**************************************************************************//
	     // FUNCTION THAT IS USED FOR MAIN MENU //
//**************************************************************************//

void mainMune(void)
{
   char ch;

   int a;
   textmode(BW40);
   textbackground(5) ;
   for (a=1; a<=11700; a++)
   cprintf(" ") ;
   clrscr();
   textbackground(11) ;
   for (a=1; a<=11700; a++)
   cprintf(" ") ;
   textcolor(GREEN) ;
   box(2,2,38,4);
   textcolor(BLUE) ;
   gotoxy(4,3);
   cprintf("P R O J E C T  O F  B A N K I N G");
   for(a=2;a<39;a++)
   {
     lineHor(2,a,5);
     if( (39-a)>1)
     lineHor(39-a,38,1);
     delay(30);
   }
   do
   {
   clrscr();
   manu();
   MAIN:
   textcolor(7);
   gotoxy(30,21);
   ch=getch();
   switch(ch)
    {
      case '1':
	  {
	  clrscr();
	  textmode(BW80);
	  newAccount();
	  gotoxy(53,45);
	  }
	  break;
       case '2':
	    {
	    clrscr();
	    textmode(BW80);
	    display();
	    getch();
	    }
	    break;
       case '3':
	 {
	 clrscr();
	 textmode(BW80);
	 displayList();
	 getch();
	 gotoxy(53,45);
	 cprintf("PRESS ANY KEY  TO CONTINUE...");
	 }
	 break;
      case '4':
	 {
	 clrscr();
	 textmode(BW80);
	 transaction();
	 }
	 break;
      case '5':
	  {
	   textmode(BW80);
	   editAccount();
	   }
	   break;
      case '6':
	   textmode(BW80);
	   help();
	   break;
      case '7':
	      {
		clrscr();
		textmode(4);
		gotoxy(10,10);
		printf("THANK's FOR VISITING");
		gotoxy(11,12);
		printf("In BANKING SYSTEM");
		gotoxy(12,14);
		printf("HAVE A NICE DAY");
		gotoxy(80,25);
		getch();
		exit(0);
		}
		break;
       default:goto MAIN;
	}
     }while(1);

}
/*========================================================================
===
   FUNCTION THAT IS USED FOR REPRESENTING MENU
==========================================================================
=*/
void manu(void)
{
   int a;
   textmode(BW40);
   textbackground(11) ;
   for (a=1; a<=11700; a++)
   cprintf(" ") ;
   textcolor(GREEN) ;
   box(2,2,38,4);
   textcolor(BLUE) ;
   gotoxy(4,3);
   cprintf("P R O J E C T  O F  B A N K I N G");
   lineHor(1,39,5);
   box(1,1,39,25);
   textcolor(RED);
   gotoxy(4,9);cprintf("O");
   gotoxy(36,9);cprintf("O");
   gotoxy(4,11);cprintf("P");
   gotoxy(36,11);cprintf("P");
   gotoxy(4,13);cprintf("T");
   gotoxy(36,13);cprintf("T");
   gotoxy(4,15);cprintf("I");
   gotoxy(36,15);cprintf("I");
   gotoxy(4,17);cprintf("O");
   gotoxy(36,17);cprintf("O");
   gotoxy(4,19);cprintf("N");
   gotoxy(36,19);cprintf("N");
   gotoxy(4,21);cprintf("S");
   gotoxy(36,21);cprintf("S");
   textcolor(GREEN);
   box(7,7,32,23);
   textcolor(6) ;
   textbackground(7) ;
   gotoxy(9,9);
   cprintf("  1 - NEW ACCOUNT     ");
   gotoxy(9,11);
   cprintf("  2 - SEE A ACCOUNT   ");
   gotoxy(9,13);
   cprintf("  3 - LIST OF ACCOUNT ");
   gotoxy(9,15);
   cprintf("  4 - TRANSACTIONS    ");
   gotoxy(9,17);
   cprintf("  5 - EDIT ACCOUNT    ");
   gotoxy(9,19);
   cprintf("  6 - HELP            ");
   gotoxy(9,21);
   cprintf("  7 - QUIT            ");
}

//**************************************************************************//
	     // FUNCTION THAT IS USED FOR DRAWING FOR FRONT PAGE //
//**************************************************************************//

void gra2()
   {

   int gd=DETECT,gm;
   int stangle,col=0;
   clrscr();                               //To make a designer ellipse
   initgraph(&gd, &gm, "C:\\TC\\BGI");
   setcolor(3);
   ellipse(320,240,0,360,315,165);
   settextstyle(10,0,1);
   settextjustify(1,1);
   setcolor(4);
   outtextxy(320,150,"COMPUTRIZED BANKING SYSTEM");
   delay(250);
   settextstyle(1,0,2);
   setcolor(7);
   outtextxy(320,190,"Presented By:-");
   delay(250);
   outtextxy(320,350,"UNDER GUIDENCE OF");
   outtextxy(320,370,"Mr. SHUKLA SIR");
   settextstyle(7,0,2);
   setcolor(2);
   delay(250);
   outtextxy(320,230,"ASHHAR ALI");
   outtextxy(320,250,"'O' LEVEL");
   outtextxy(320,270,"REG. NO. :- 966836");
   outtextxy(320,290,"Natinal Institute Of Electronics And");
   outtextxy(320,310,"Information Technology");
   for (stangle=0;!kbhit();stangle++)
   {
      setcolor(col);
      ellipse(320,240,stangle,stangle+20,310,160);
      ellipse(320,240,stangle+180,stangle+200,310,160);
      delay(9);
      setcolor(col);
      ellipse(320,240,stangle-1,stangle+19,310,160);
      ellipse(320,240,stangle-1+180,stangle+199,310,160);
      col++;
   }
   closegraph();
   }

//**************************************************************************//
			      // THE END //
//**************************************************************************//


