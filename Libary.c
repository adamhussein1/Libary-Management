

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_LIBRARY_SIZE 20
#define MAX_TITLE_SIZE 16
#define MAX_AUTHOR_SIZE 16
#define MAX_ISBN_SIZE 25
#define MAX_MONTH_SIZE 2
#define MAX_YEAR_SIZE 4


/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
typedef struct date{
	unsigned int month;
	unsigned int year;
}date_t;

typedef struct book{
	char title[MAX_TITLE_SIZE];
	char author[MAX_AUTHOR_SIZE];
	char isbn[MAX_ISBN_SIZE];
	char genre[20];
	date_t publication_date;
}book_t;
/*Central array */
int book_count = 0;
book_t booklist[MAX_LIBRARY_SIZE];


/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void Addbook(void);
void deleteBook(void );
void displayBook(void);
void saveDatabase(void);
void readDatabase(void);
void printMenu(void);
/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){
	char temp[256];
	int userInput;
    printMenu();
    /*char dbFileName[] = "database";*/
	while (1){
	printf("Enter your choice>\n");
	fgets(temp,sizeof(temp),stdin);
	sscanf(temp, "%d", &userInput);
	if (userInput == 6) {
		break;
	}
	if (userInput <1 || userInput>6){
		printf("Invalid choice.\n");
		printMenu();
		continue;
	}
		switch (userInput){
			case 1 :Addbook();break;
			case 2 :deleteBook() ;break;
			case 3 :displayBook() ;break;
			case 4 :saveDatabase() ;break;
			case 5:readDatabase() ;break;
			default : printf("Read error");break; 
		}
		printMenu();
		
	}
    return 0;
}


/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void printMenu(void){
    printf("\nLibrary Management System \n"
    	"1. Add book\n"
    	"2. Delete last book\n"
    	"3. Display book list\n"
    	"4. Save the book list to the database\n"
    	"5. Read the book list from the database\n"
    	"6. Exit the program\n");
}
/*******************************************************************************
 * Add Book 
*******************************************************************************/

  void Addbook(void){
	if (book_count> MAX_LIBRARY_SIZE){
		printf("List is full");
		return;
	}
	book_t *b=&booklist[book_count]; 
	char temp[256];

	/* Gets Title */
	printf("Title: >");
	fgets(temp,sizeof(temp),stdin);
	sscanf(temp, "%[^\n]", b->title);

	/* Gets Author */
	printf("Author: >");
	fgets(temp,sizeof(temp),stdin);
	sscanf(temp,"%[^\n]", b->author);

	/* Gets ISBN */
	while (1){	
		printf("ISBN: >");
		fgets(temp,sizeof(temp),stdin);
		temp[strcspn(temp,"\n")] = '\0'; /* strip newline before scan*/
		sscanf(temp, "%[^\n]", b->isbn);
		if ((int)strlen(b->isbn) >=1 &&(int)strlen(b->isbn) <=11){
			break; /* loop is valid and stop the loop*/
		}
		printf("Invalid ISBN.\n");
	}

	/* Gets publication_date month */
	while (1){
		printf("Publication_date(month): >");
		fgets(temp,sizeof(temp),stdin);
		sscanf(temp, "%u", &b->publication_date.month);
		if (b->publication_date.month >= 1 && 
			b->publication_date.month <=12){
		break;
	}
	printf("Invalid month.\n");
	}
	
	/* Gets publication_date year */
	while (1){
	printf("Publication_date(year): >");
	fgets(temp,sizeof(temp),stdin);
	sscanf(temp, "%u", &b->publication_date.year);
	if (b->publication_date.year >= 1950 && 
	b->publication_date.year <=2024){
		break;
	}
	printf("Invalid year. \n");
	
	}

	/* Gets Genre */
	printf("Genre: >");
	fgets(temp,sizeof(temp),stdin);
	sscanf(temp, "%19[^\n]", b->genre);

	printf("\n");
	book_count++;
 }

 /*******************************************************************************
 * Delete Book 
*******************************************************************************/
  void deleteBook(void){
	if (book_count == 0){
		printf("List is empty");
	}else{
		book_count--;
	}
  }

/*******************************************************************************
 * displayBook
*******************************************************************************/

	void displayBook(void){
	int i;
	
	if (book_count == 0){
		printf("List is empty\n");
		return;
	}
	else{
	/* Header */
	/* printf("%-15s %-15s %-15s %-11s %-10s\n",
	"Title", "Author",
	 "ISBN", "Pub. Date", 
	 "Genre");
	 printf("----------","----------"," ----------", "---------", " --------");*/

	printf("Title          Author         ISBN       Pub. Date Genre\n");
	printf("----------     ----------     ---------- --------- --------\n");

	for (i = 0; i<book_count;i++){
		printf("%-15s %-15s %-11s %02u-%-4u %-10s\n",
		booklist[i].title, 
		booklist[i].author, 
		booklist[i].isbn,
		booklist[i].publication_date.month,
		booklist[i].publication_date.year,
		booklist[i].genre);
	
	}	
	}	
}
/*******************************************************************************
 * Save Book list
*******************************************************************************/
void saveDatabase(void){
	int i;
	FILE *fp;
	fp = fopen("database","pp");

	if (fp == NULL){
		printf("error");
		return; 
	}
	/* write book_count*/
	fprintf(fp, "%d\n", book_count);

	for (i=0; i<book_count;i++){
		fprintf(fp, "%s\n", booklist[i].title);
		fprintf(fp, "%s\n", booklist[i].author);
		fprintf(fp, "%s\n", booklist[i].isbn);
		fprintf(fp, "%d\n", booklist[i].publication_date.month);
		fprintf(fp, "%d\n", booklist[i].publication_date.year);
		fprintf(fp, "%s\n", booklist[i].genre);

	}
	fclose(fp);
	
}
/*******************************************************************************
 * read Book list
*******************************************************************************/
void readDatabase(void){
	if(book_count == 0 ){
		printf("read error");
		return;
	}
}