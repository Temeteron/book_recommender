/********************************************************
 *                                                      *
 *      			Dimitris Greasidis                  *
 *                                                      *
 *				Email: temeteron@gmail.com				*
 *														*
 *      		Github Username: Temeteron         		*
 *                                                      *
 *      			Recommend books from       			*
 *      		  	  	   votes            			*
 *            			                       			*
 *                                                      *
 ********************************************************/
#include "libraries.h"

/* Global Variables */
char info_books[BOOKS][NUM_OF_CHARS_OF_INFO] /* Array 2d, contains info of books */
, customers[NUM_OF_CUST][NUM_OF_CHARS_OF_USERNAMES] /*Array 2d, contains the name of the customers */;
int  grades_of_books[NUM_OF_CUST][BOOKS] /* Array 2d, contains the evaluation of the customers */;

/* Read number of books and save their info */
int num_books_funct(){
	char help_info_books[NUM_OF_CHARS_OF_INFO];/* Help string */
	int number_books, i;

	scanf("%d", &number_books);

	for (i = 0; i < number_books; i++){
		scanf("%s", help_info_books);
		strcpy(info_books[i], help_info_books);
	}
	return number_books;
}

/* Read names of customers, until it finds "EndOfNames", and the evaluation */
int cust_grades(int number_books){
	int i , j;/* Counter of loops */
	int number_of_customers, help_grades;
	char help_string[NUM_OF_CHARS_OF_USERNAMES], strEOF[] = "EndOfNames";

	scanf("%s", help_string);
	i = 0;
	do {
		strcpy(customers[i], help_string);
		j = 0;
		do {
			scanf("%d", &help_grades);
			grades_of_books[i][j] = help_grades;
			j++;
		} while (j < (number_books));
		scanf("%s", help_string);
		i++;
	} while ((strcmp(strEOF, help_string))!= (VALID));
	number_of_customers = i;
	
	return number_of_customers;
}

/* Read name of client and find pos in the array */
int find_username(int number_of_customers){
	int i, position = -1;/* counter of loop & and var with the pos of client */
	char username[NUM_OF_CHARS_OF_USERNAMES];


	printf("Hi, what's your name? ");
	scanf("%s", username);
	printf("Hello %s!\n", username);

	/* Find name of client if it exists */
	i = 0;
	do {
		if (strcmp(customers[i], username) == 0){	
			position = i;
		}
		i++;
	} while(i < number_of_customers && position < 0);
	if (position < 0){
		printf("No such user!\n");
	}

	return position;
}

/* Find customer with the higher similarity, in the evaluation of the books, with the client and print the value */
int similar_grades_funct(int number_of_customers, int position, int number_of_books){
	int i, j;/* Counters of loops */
	int max_similarity_position, grade_similarity[NUM_OF_CUST];

	/* Initialize */
	for (i = 0; i < NUM_OF_CUST; i++){
		grade_similarity[i] = 0;
	}

	/* Fill array with similarity number */
	i = 0;
	max_similarity_position = 0 ;
	while (i < number_of_customers){
		if (i != position){
			for (j = 0; j < number_of_books; j++){
				grade_similarity[i] = grade_similarity[i] + (grades_of_books[i][j] * grades_of_books[position][j]);
			}
			if ( grade_similarity[i] > grade_similarity[max_similarity_position]){
				max_similarity_position = i;
			}
		}
		i++;
	}

	 return max_similarity_position;
}

/* Find recommended books for client and print them sorted */
void sorted_books_to_propose(int position_user, int position_similar_customer, int number_of_books){
	char proposing_books[BOOKS][NUM_OF_CHARS_OF_INFO], help_string[NUM_OF_CHARS_OF_INFO];
	int i, j;/* Counters of loops */
	int recommended_books = -1, num_of_recommended_books = 0;

	/* Save recommended books to the new array */
	i = 0;
	j = 0;
	while (i < number_of_books){
		if (grades_of_books[position_similar_customer][i] > 0 && grades_of_books[position_user][i] == 0){
			num_of_recommended_books++;
			strcpy(help_string, info_books[i]);
			strcpy(proposing_books[j], help_string);
			recommended_books = VALID;
			j++;
		}
		i++;
	}

	/* Sort array of books */
	for (i = 0; i < num_of_recommended_books; i++){
		for (j = i + 1; j < num_of_recommended_books; j++) {
			if (strcmp(proposing_books[j], proposing_books[i]) < 0){
				/*swap strings*/
				strcpy(help_string, proposing_books[i]);
				strcpy(proposing_books[i], proposing_books[j]);
				strcpy(proposing_books[j], help_string);
			}
		}
	}

	/* Print message */
	if (recommended_books >= 0){
		printf("We recommend:\n");
		for (i = 0; i < num_of_recommended_books; i++){
			printf("%s\n", proposing_books[i]);
		}
	}
	else {
		printf("Sorry, no recommendations!\n");
	}
	
}

/*
 * main
 */

int main (int argc, char* argv[]){
	int num_books, number_of_customers = 0, position = -1, i, max_similarity_pos, max_esoteriko_ginomeno = 0;/*arithmos bibliwn, arithmos pelatwn, thesi username, thesi pelati me tin megisti omoiotita me ton username, megisto eswteriko ginomeno twn protimisewn*/

	/* Get number of books */
	num_books = num_books_funct();

	/* Get number of clients */
	number_of_customers =  cust_grades(num_books);

	/* Get name of client until it is in the customers list */
	while (position == -1){
		position = find_username(number_of_customers);
	}

	/* Find pos of customer with the highest similarity with the client */
	max_similarity_pos = similar_grades_funct(number_of_customers, position, num_books);

	/* Find max inner product */
	for (i = 0; i < num_books; i++){
		max_esoteriko_ginomeno = max_esoteriko_ginomeno + (grades_of_books[position][i] * grades_of_books[max_similarity_pos][i]);
	}

	/* Print name of customer with the highest inner product with the client */
	printf("%s %d\n", customers[max_similarity_pos], max_esoteriko_ginomeno);

	/* Find recommended books */
	sorted_books_to_propose(position, max_similarity_pos, num_books);

	return 0;
}
