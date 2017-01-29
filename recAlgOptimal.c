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
	/* Structs */

/* struct info of user */
typedef struct user {
	char name[SIZE_NAME];			/*	   name of user      */
	char username[SIZE_USERNAME];	/*	  	username 	     */
	int *grades;
} userT;

/* struct info of book */
typedef struct book {
	char title[SIZE_BOOK];
	char author[SIZE_BOOK];
}bookT;


	/* Prototypes of Functions */

bookT* getBook (int num_books);
userT* getUserGrade (int num_users, int num_books);
int findUsername (userT *users,char *username,int num_users);
userT* findBuyer (userT *users,int num_users);
userT* getBuyerGrades (userT *buyer,int num_books);
int calcDotProduct (int *userGrades,int *buyerGrades,int num_books);
void findSimilarity (userT *buyer, userT *users, bookT *book, int num_users, int num_books);

/**********
 *  main  *
 **********/
int main (int argc, char *argv[]) {
	int num_books,num_users;   /*                          number of books and users 											*/
	int i;                     /*                                counter of loop                                                */
	bookT *books;              /*                 		  array with info of num_books 											*/
	userT *users,*buyer;       /* 					array with info of user and buyer with the values							*/

	scanf("%d", &num_books);

	books = getBook (num_books);
	if (books == NULL) return 1; /* check memory lick */

	scanf("%d", &num_users);

	users = getUserGrade (num_users, num_books);
	if (users == NULL) return 1; /* check memory lick */

	buyer = findBuyer(users, num_users);
	if (buyer == NULL) return 1; /* check memory lick */

	buyer = getBuyerGrades(buyer, num_books);
	if (buyer == NULL) return 1; /* check memory lick */

	findSimilarity (buyer, users, books, num_users, num_books);

	/* free memory */
	free(books); 
	for (i = 0; i < num_users; i++) {
		free(users[i].grades); 
	  
	}
	free(users); 
	free(buyer); 

	return 0;
}

	/**************
	 *  Functions *
	 **************/

/************************************************************************************************ 
 * Sunartisi pou diavazei ta stoixeia ton vivlion kai ta apothikeuei se katallilo pinaka        *
 *                                                                                              *   
 * Tupos     :  bookT* (pointer se struct)                                                      *
 * Parametroi: 1) plithos vivlion                                                               *  
 *                                                                                              *
 * Epistefei : 1) tin dieu8unsi tou pinaka me ta stoixeia ton vivlion                           *
 *             2) NULL se periptosi pou uparxei provlima kata tin dunamiki desmeusi mnimis      *
 *                                                                                              *
 * ************************** *******************************************************************/
bookT* getBook (int num_books) {
	bookT *books;       /* pinakas apo structs pou periexei ta info ton biblion */
	int i;              /*              metritis brogxou                        */
	char format[13];    /*        formatstring gia asfali anagnosi string       */

	books = (bookT*) malloc(num_books * sizeof(bookT));  /* dinamiki desmeusi mnimis */

	/* elegxos gia aneparkia mnimis  kai ektupwsi katallilou minimatos kata tin dinamiki desmeusi mnimis */
	if (books == NULL) {
		printf("No memory");
		return NULL;
	}

	sprintf(format, STRING, SIZE_BOOK - 1);
	for (i = 0; i < num_books; i++) {         /* eisagosi dedomenon(titlos,onoma suggrafea) */
		scanf(format, books[i].title);
		scanf(format, books[i].author);
	}

	return books;
}

/**********************************************************************************************
 * Sunartisi pou diavazei ta stoixeia ton xriston kai ta apothikeuei se katallilo pinana      *                                
 *                                                                                            *
 * Tupos     :  userT*(pointer se struct)                                                     *                        
 * Parametroi: 1) plithos xriston                                                             *
 *             2) plithos vivlion                                                             *
 *                                                                                            *
 * Epistrefei: 1) tin dieu8insi tou pinaka me ta stoixeia ton xriston                         *
 *             2) NULL se periptosi pou uparxei provlima kata tin dunamiki desmeusi mnimis    * 
 *                                                                                            * 
 **********************************************************************************************/
userT* getUserGrade (int num_users, int num_books) {
	userT *users;/*pinakas apo structs pou periexei ta info tou xristi*/
	int i, j;/*metrites brogxon*/
	char format1[13], format2[13];/*formatstring gia asfali anagnosi string*/

	users = (userT*) malloc(num_users * sizeof(userT));/*dinamiki desmeusi mnimis*/

	/*elegxos gia aneparkia mnimis  kai ektupwsi katallilou minimatos kata tin dinamiki desmeusi mnimis*/
	if (users == NULL) {
		printf("No memory\n");
		return NULL;
	}
	sprintf(format1, STRING, SIZE_NAME - 1);
	sprintf(format2, STRING, SIZE_USERNAME - 1);

	for (i = 0; i < num_users; i++) {
		scanf(format1, users[i].name);           /* Eisagogi stoixeion ton xriston */
		scanf(format2, users[i].username);
		users[i].grades = (int*) malloc(num_books * sizeof(int)); /* dinamiki desmeusi mnimis */
		if (users[i].grades == NULL) {
			printf("No memory\n");
			return NULL;
		}
		for (j = 0; j < num_books; j++) {        /* Eisagosi vathmon */
			scanf("%d", &(users[i].grades[j]));
		}
	}

	return users;
}

/**************************************************************************************************************
 * Sinartisi pou entopizei ena string mesa se ena pinaka apo structs pou perixoun string se kapoio pedio tous *
 *                                                                                                            *
 * Tupos      :  int                                                                                          *   
 * Parametroi : 1) pinakas me ta stoixeia ton xriston                                                         *
 *              2) string pou theloume na entopisoume                                                         *   
 *              3) diastasi tou pinaka me ta stoixeia ton xriston                                             *
 *                                                                                                            *
 * Epistrefei : 1)  [ 1 ] se periptosi pou entopisei to string                                                *
 *              2)  [ 0 ] se periptosi pou den entopisei to string                                            *
 *                                                                                                            *
 * ************************************************************************************************************/
int findUsername (userT *users,char *username,int num_users) {
	int i; /* metritis brogxou */

	for (i = 0; i < num_users; i++) {
		if(strcmp(username, users[i].username) == 0) { /* Elegxos me skopo tin euresi tou string meso tis xrisis */ 
	  		return 1;                              /*             tis sunartisis strcmp                      */
	  	}
	}

	return 0;
}

/******************************************************************************
 * Sunartisi pou diavazei ta stoixeia tou agorasti kai ton entopizei          *
 *                                                                            *
 * Tupos      : userT*(Pointer se struct)                                     *         
 * Parametroi : 1) pinakas me ta stoixeia ton xriston                         *
 *              2) plithos xriston                                            *
 *                                                                            *
 * Epistrefei : 1) deikti se struct pou periexei ta stoixeia tou agorasti     *
 *              2) NULL se periptosi pou uparxei provlima kata tin dunamiki   *
 *                                desmeusi mnimis                             *
 *                                                                            *
 ******************************************************************************/
userT* findBuyer (userT *users, int num_users) {
	userT *buyer;                   /* pinakas apo struct pou periexei ta stoixeia tou agorasti */
	char format1[13], format2[13];  /*        formatstring gia asfali anagnosi string           */
	
	buyer = (userT*) malloc(sizeof(userT)); /* dinamiki desmeusi mnimis */

	/* elegxos gia aneparkia mnimis  kai ektupwsi katallilou minimatos kata tin dinamiki desmeusi mnimis */
	if(buyer == NULL) {
		printf("No memory");
		return NULL;
	}
	
	sprintf(format1, STRING, SIZE_NAME - 1);
	sprintf(format2, STRING, SIZE_USERNAME - 1);
	printf("Hi, what's your name? \n");         /* Eisagogi stoieion agorasti */
	scanf(format1, buyer->name);                /* Eisagogi onomatos          */
	printf("Hello %s!\n", buyer->name);
	printf("Enter a username: \n");
	scanf(format2, buyer->username);               
	while (findUsername(users, buyer->username, num_users)) {               /* Eisagogi username xristi kai elegxos an auto  */
		printf("Username exists. Enter a different username: \n");      /* ine monadiko meso tis sunaristis findUsername */
		scanf(format2, buyer->username);
	}

	return buyer;
}

/****************************************************************************** 
 * Sunartisi pou diavazei tis vathmologies tou xristi                         *
 *                                                                            *
 * Tupos      : userT* (deiktis se struct)                                    *
 * Parametroi: 1) struct me ta stoixeia tou agorasti                          *
 *             2) plithos vivlion                                             *
 *                                                                            *
 * Epistrefei :1) tin dieu8insi tou struct me ta stoixeia tou agorasti        *
 *             2) NULL se periptosi pou uparxei provlima kata tin dunamiki    *
 *                             desmeusi mnimis                                *
 *                                                                            *
 * ****************************************************************************/
userT* getBuyerGrades (userT *buyer,int num_books) {
	int i;/*metritis brogxou*/
	
	buyer->grades = (int*) malloc(num_books*sizeof(int));/*dinamiki desmeusi mnimis*/

	/*elegxos gia aneparkia mnimis  kai ektupwsi katallilou minimatos kata tin dinamiki desmeusi mnimis*/
	if (buyer->grades == NULL) {
		printf("No memory");
		return NULL;
	}

	for (i = 0; i < num_books; i++) {    /* Eisagogi vathmon xristi gia kathe vivlio */
		scanf("%d", &(buyer->grades[i]));
	}

	return buyer;
}

/****************************************************************************************
 * Sunartisi pou upologizei to esoteriko ginomeno duo dianusmaton                       *
 *                                                                                      * 
 * Tupos       : int                                                                    *
 * Parametroi : 1) Pinakas me tous vathmous ton xriston                                 *
 *              2) Pinakas me tous vathmous tou agorasti                                *
 *                                                                                      *                            
 * Epistefei : To esoteriko ginomeno kathe xristi                                       *
 * **************************************************************************************/
int calcDotProduct (int *userGrades,int *buyerGrades,int num_books) {
	int j,dot_product;                                           /* metritis brogxon,esoteriko ginomeno kathe xristi */

	dot_product = 0;                                 /* arxikopoihsi esoterikou ginomenou kathe xristi */
	for (j = 0; j < num_books; j++) {
		dot_product = dot_product + (userGrades[j]) *buyerGrades[j];  /* Ypologismos esoterikou ginomenou kathe xristi gia kathe vivlio */
	}
	
	return dot_product;
}

/**************************************************************************************************** 
 * Sunartisi pou entopizei to xristi me ton megisto vathmo omoiotitas kai ektuponei ta stoixeia tou *
 *                                                                                                  *
 * Tupos      : void                                                                                *
 * Parametroi : 1) pinakas me ta stoixeia ton xriston                                               *
 *              2) struct  me ta stoixeia tou agorasti                                              *
 *              3) pinakas me ta stoixeia ton vivlion                                               *
 *              4) plithos xriston                                                                  *
 *              5) plithos vivlion                                                                  *
 *                                                                                                  *
 * Epistrefei : Tipota                                                                              *
 *                                                                                                  *
 * **************************************************************************************************/
void findSimilarity (userT *buyer, userT *users, bookT *book, int num_users, int num_books) {
	int i,dot_product,max_dot_product;  /* metritis brogxon,esoteriko ginomeno kathe xristi,megisto esoteriko ginomeno */
	int max_similarity;                  /* thesi tou xristi me ton megisto vathmo omoiotitas                           */
	
	max_dot_product = (-25) * (num_books - 1);   /* arxikopoihsi megistou bathmou omoiotitas me tin elaxisti dunati timi */
        for (i = 0; i < num_users; i++) {
		dot_product=calcDotProduct(users[i].grades,buyer->grades,num_books);   /*                          Ypologismos esoterikou ginomenou kathe xristi                      */
	    	if (dot_product > max_dot_product) {                                   /* Sugrkisi kathe ginomenou me to megisto oste na vrethei telika to megisto esoteriko ginomeno */
	        	max_dot_product = dot_product;
	        	max_similarity=i;
	    	}
	}
	
	printf("%s %d\n", users[max_similarity].name,max_dot_product);

	for(i = 0 ; i < num_books; i++) {                                                   /* Ektuposi stoixeion xristi me ton megisto vathmo omoiotitas      */
		if(buyer->grades[i] == 0 && users[max_similarity].grades[i] > 0) {          /* Elegxos me skopo tin euresi tou vivliou pou den exei diavasei   */
      			printf("We recommend: %s by %s\n",book[i].title, book[i].author);   /* (agorastis(buyer->grades[i] == 0)  kai den aresei ston xristi   */
			break;
		}	
	}

	if (i == num_books) {                           /* An vgoume apo to loop kai to i exei tin timi num_book simainei oti den exei vrethei kapoio vivlio */
		printf("No recommendations\n");         /*                               opote ektuponoume to katallilo minima                               */ 
	}
			
}
