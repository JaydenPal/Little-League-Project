#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_PLAYERS 10
#define MAX_NAME_LEN 32
#define MAX_CITY_LEN 64
#define BUFFER_SIZE 1024


//declare enum data types globally so functions can accept the actual non-global enum variables as parameters
enum phoneTypes {HOME, WORK, CELL, NOPHONE};
enum relationships {MOTHER, FATHER, GRANDMOTHER, GRANDFATHER, OTHER, NORELATION};
//fucntion prototypes to check parameters and maintain code readability(otherwise all function definitions would be before main)
void printSummary(char **firstNames, char **lastNames, unsigned short *streetNums, char **streetNames, char **cities, unsigned short *birthYears, char **parentFirstNames, char **parentLastNames, enum phoneTypes *parentPhoneTypes, enum relationships *parentRelationships, unsigned int *phoneNumbers, int counter, int start); 
void printFile(char **firstNames, char **lastNames, unsigned short *streetNums, char **streetNames, char **cities, unsigned short *birthYears, char **parentFirstNames, char **parentLastNames, enum phoneTypes *parentPhoneTypes, enum relationships *parentRelationships, unsigned int *phoneNumbers, int counter, int start);
void getName(char *strArr[], int MAX_LEN, char prompt[], int curIndex);
int checkString(char buffer[], int MAX_LEN); 
void clearBuffer();
void retrieveShort(unsigned short *value, int min, int max, char prompt[]);
void getChoice(char *value, char prompt[]);
void clean_stdin(void);
void printEnum(enum relationships value, enum phoneTypes dummy, int toPrint);
void printEnumToFile(enum relationships value, enum phoneTypes dummy, int toPrint, FILE* pF);
void freeStringMemory(char **arr, int counter);
bool isDataValid = false;
char buffer[BUFFER_SIZE];  // no restrictions stated on making buffer a global variable

int main() {
   //declare and allocate space for dynamic arrays
int i;
char **firstNames = malloc(sizeof(char*) * MAX_PLAYERS);
char **lastNames = malloc(sizeof(char*) * MAX_PLAYERS);
unsigned short *streetNums = malloc(sizeof(unsigned short) * MAX_PLAYERS);
char **streetNames = malloc(sizeof(char*) * MAX_PLAYERS);
char **cities = malloc(sizeof(char*) * MAX_PLAYERS);
unsigned short *birthYears = malloc(sizeof(unsigned short) * MAX_PLAYERS);
// unsigned short *birthMonths = malloc(sizeof(unsigned short) * MAX_PLAYERS);
// unsigned short *birthDays = malloc(sizeof(unsigned short) * MAX_PLAYERS);
char **parentFirstNames = malloc(sizeof(char*) * MAX_PLAYERS);
char **parentLastNames = malloc(sizeof(char*) * MAX_PLAYERS);
unsigned int *phoneNumbers = malloc(sizeof(unsigned int) * MAX_PLAYERS);
enum phoneTypes *parentPhoneTypes = malloc(sizeof(enum phoneTypes) * MAX_PLAYERS);
enum relationships *parentRelationships = malloc(sizeof(enum relationships) * MAX_PLAYERS);
//establish variables that control flow of program and anything else that still needs to be declared
   char prompt[50];
   char choice;
   char infoCorrect;
   char printRoster;
   int counter = 0;
    do{
      counter++;
      int curIndex = counter - 1;      //curindex of players[]
      //get child last and first name
      strcpy(prompt, "Enter your first name: ");
      getName(firstNames, MAX_NAME_LEN, prompt, curIndex); //see function declaration for memory allocation
      strcpy(prompt, "Enter your last name: ");
      getName(lastNames, MAX_NAME_LEN, prompt, curIndex);
      //retrieve streetNum
      strcpy(prompt, "Enter your street number: ");
      unsigned short *pStreetNum = &streetNums[curIndex];
      retrieveShort(pStreetNum, 0, 99999, prompt);
      //retrieve street name
      strcpy(prompt, "Enter the name of your street: ");
      getName(streetNames, MAX_CITY_LEN, prompt, curIndex);
      //retrieve city name
      strcpy(prompt, "Enter the name of the city you were born: ");
      getName(cities, MAX_CITY_LEN, prompt, curIndex);
      //retrieve birthyear
      strcpy(prompt, "Enter your birth year: ");
      unsigned short *pbirthYears = &birthYears[curIndex];
      retrieveShort(pbirthYears, 2010, 2013, prompt);
      //retrieve parent first and last names
      strcpy(prompt, "Enter parent/guardian first name: ");
      getName(parentFirstNames, MAX_NAME_LEN, prompt, curIndex); //see function declaration for memory allocation
      strcpy(prompt, "Enter parent/guardian last name: ");
      getName(parentLastNames, MAX_NAME_LEN, prompt, curIndex);
      //retrieve phone number 
      do{
         printf("Please enter parent/guardian phone number(only digits): ");
         int temp = scanf("%10u", &phoneNumbers[curIndex]);
         clean_stdin();   //clean fucntion prevents infinite loop when invalid data is entered by clearing input stream                
         //validate
         if(temp == 1 && phoneNumbers[i] >= 1000000000){   //validates data type entered (only chars 0-9) if less than 1, no fields converted meaing no int was entered
          isDataValid = true;     
         }else{
            printf("You have entered invalid data or not enough digits to be a valid number(10)! Please enter a phone number that only contains the digits 0-9.\n");
            isDataValid = false;
            continue;
      }
      }while(isDataValid == false);
      //retrieve phone type
      do{
         int temp;
         printf("Is this a home, work, or cell number?\nEnter (0) for home; (1) for work; (2) for cell: ");
         scanf("%d", &temp);
         switch(temp){                    //I could not get gcc to work with enums directly bc it compiled them as enum pointers rather than integers. This switch just "translates" the enums into ints
            case 0:
               parentPhoneTypes[curIndex] = HOME;
               break;
            case 1:
               parentPhoneTypes[curIndex] = WORK;
               break;
            case 2:
               parentPhoneTypes[curIndex] = CELL;
               break;
            default: 
               parentPhoneTypes[curIndex] = NOPHONE;
         }
         clean_stdin();
         //validate entry
         if(parentPhoneTypes[curIndex] == WORK || parentPhoneTypes[curIndex] == CELL || parentPhoneTypes[curIndex] == HOME ){
            isDataValid = true;
         } else {
            printf("You have entered invalid data! Please try again.\n\n");
            isDataValid = false;
            continue;
         }
      }while(isDataValid == false);

      //retrieve parent/guardian relationship
      do{
         int temp;
         printf("What is your relationship to the child?\nEnter (0) for mother; (1) for father; (2) for grandmother; (3) for grandfather;  (4) for other: ");
         scanf("%d", &temp);
         switch(temp){
            case 0:
               parentRelationships[curIndex] = MOTHER;
               break;
            case 1:
               parentRelationships[curIndex] = FATHER;
               break;
            case 2:
               parentRelationships[curIndex] = GRANDMOTHER;
               break;
            case 3:
               parentRelationships[curIndex] = GRANDFATHER;
               break;
            case 4:
               parentRelationships[curIndex] = OTHER;
               break;
            default:
               parentRelationships[curIndex] = NORELATION;
         }
         clean_stdin();
         //validate entry
         if(parentRelationships[curIndex] == MOTHER || parentRelationships[curIndex] == FATHER ||parentRelationships[curIndex] == GRANDMOTHER ||parentRelationships[curIndex] == GRANDFATHER || parentRelationships[curIndex] == OTHER ){
            isDataValid = true;
         } else {
            printf("You have entered invalid data! Please try again.\n\n");
            isDataValid = false;
            continue;
         }
      }while(isDataValid == false);
      //display current input info to see if user is okay with input
      printSummary(firstNames, lastNames, streetNums, streetNames, cities, birthYears, parentFirstNames, parentLastNames, parentPhoneTypes, parentRelationships, phoneNumbers, counter, curIndex);
      //check if user info is correct
      strcpy(prompt, "Is this information correct?(y/n)");
      char *pInfoCorrect = &infoCorrect;
      getChoice(pInfoCorrect, prompt);
      //if no allow user to re enter info
      if(infoCorrect == 'n'){
         printf("\nPlease re-enter your information.\n");
         choice = 'y';
         counter--;
         continue;
      }
      printf("\nThe information is correct!\n");
      //check if max nums of input has been reached
      if(counter >= 10){
      break;
   }
      // check if user has more information to put in
      strcpy(prompt, "Would you like to enter more information?(y/n)");
      char *pChoice = &choice;
      getChoice(pChoice, prompt);
   }while(choice == 'y' && counter < 10);
   //ask user if they want to save the roster to local txt file
   if(counter >= 10){printf("\nYou have entered the max ammount of inputs!\n");}
   strcpy(prompt, "Would you like to save this roster?(y/n)");
   char *pPrintRoster = &printRoster;
   getChoice(pPrintRoster, prompt);
   if(printRoster == 'y'){printFile(firstNames, lastNames, streetNums, streetNames, cities, birthYears, parentFirstNames, parentLastNames, parentPhoneTypes, parentRelationships,phoneNumbers, counter, 0);}
   printf("Displaying summary....\n");
   sleep(printRoster == 'y' ? 5 : 2);  //delays priint of summary by 5 seconds so user can see confirmation message from calling print file
   printSummary(firstNames, lastNames, streetNums, streetNames, cities, birthYears, parentFirstNames, parentLastNames, parentPhoneTypes, parentRelationships, phoneNumbers, counter, 0);
   //free space allocated with malloc
   freeStringMemory(firstNames, counter);
   freeStringMemory(lastNames, counter);
   freeStringMemory(parentFirstNames, counter);
   freeStringMemory(parentLastNames, counter);
   freeStringMemory(cities, counter);
   freeStringMemory(streetNames, counter);
   free(streetNums);
   streetNums = NULL;
   free(birthYears);
   birthYears = NULL;
   free(parentPhoneTypes);
   parentPhoneTypes = NULL;
   free(parentRelationships);
   parentRelationships = NULL;
   free(phoneNumbers);
   phoneNumbers = NULL;
   return 0;
}
void getName(char *strArr[], int MAX_LEN, char prompt[], int curIndex){
    bool isDataValid;
   do{
         // retrieve name
         printf("%s", prompt);
         clearBuffer();             //clear buffer before asking for input each time function is called
         scanf("%[^\n]s", buffer);
         //validate name
         int temp = checkString(buffer, MAX_LEN);
         if(temp == 0){
            strArr[curIndex] = malloc(strlen(buffer) * (int)sizeof(char));  //dynamically allocate memory for string input (length of string times 1 byte for each char)
            strcpy(strArr[curIndex], buffer);
            isDataValid = true;
         } else{
            isDataValid = false;
         }
      } while(isDataValid == false);
}
int checkString(char buffer[], int MAX_LEN){
   if(strlen(buffer) > MAX_LEN){
            printf("That name is too long! Please enter a name no longer than %d characters.\n", MAX_LEN);
            clean_stdin(); // prevents error if user inputs string > MAXlength WITH spaces when asking for input again
            return strlen(buffer) - MAX_LEN;
         } else {
            clean_stdin();
            return 0;
         }
         return -1;
}
void retrieveShort(unsigned short *value, int min, int max, char prompt[]){
   bool isDataValid;
   do{
         //retrieve value(month day or year)
         int temp;
         printf("%s", prompt);
         temp = scanf("%hu", value);
         clean_stdin();
         //validate value
         if(temp == 1 && *value <=max && *value >= min){
            isDataValid = true;
         } else {
            printf("You have entered invalid data! Please enter a value between %d-%d.\n", min, max);
            isDataValid = false;
            continue;
         }
      }while(isDataValid == false);
}
void clean_stdin()
{
    int c;
    do {
        c = getchar();                  //Flushes input buffer by getting characters remaining in buffer
    } while (c != '\n' && c != EOF);    //Flushes until new line is reached, flushing the \n char as well, 
}                                       // or until end of input buffer is reach(input buffer is a file pointer)
void printSummary(char **firstNames, char **lastNames, unsigned short *streetNums, char **streetNames, char **cities, unsigned short *birthYears, char **parentFirstNames, char **parentLastNames, enum phoneTypes *parentPhoneTypes, enum relationships *parentRelationships, unsigned int *phoneNumbers, int counter, int start){
   /*passed pointers to function for practice but i think it could be cleaner to establish pointers inside of 
   this function like this but maybe not due to the way memory works

   char (*pFirstNames)[MAX_NAME_LEN] = NULL; 
   char (*pCities)[MAX_CITY_LEN] = NULL;
   pFirstNames = firstNames;
   pCities = cities;  
   */

   printf("\n\n///////////////SUMMARY///////////////\n\n\n");
   int playerNum;
   int i;
      for(i = start; i < counter; i++){
      playerNum = i + 1;
      printf("\n\n\t\t****Player %d****\n", playerNum);
      //display childs info
      printf("Name: %s %s\n", firstNames[i], lastNames[i]);
      printf("Adress: %hu ", streetNums[i]);
      printf("%s, %s\n", streetNames[i], cities[i]);
      printf("Date of Birth: %hu\n", birthYears[i]);
      //display parent info
      printf("\nParent/Guardian info: \n\n");
      printf("Name: %s %s\n", parentFirstNames[i], parentLastNames[i]);
      printf("Phone Number: %u\n", phoneNumbers[i]);
      printEnum(parentRelationships[i], parentPhoneTypes[i], 0);
      printEnum(parentRelationships[i], parentPhoneTypes[i], 1);
   }

}
void printFile(char **firstNames, char **lastNames, unsigned short *streetNums, char **streetNames, char **cities, unsigned short *birthYears, char **parentFirstNames, char **parentLastNames, enum phoneTypes *parentPhoneTypes, enum relationships *parentRelationships,unsigned int *phoneNumbers, int counter, int start){
   int playerNum;
   int i;
   FILE *pF = fopen("roster.txt", "w");
   fprintf(pF, "Little League Roster");
   for(i = start; i < counter; i++){
      playerNum = i + 1;
      fprintf(pF, "\n\nPlayer %d:\n\n", playerNum);
      //display childs info
      fprintf(pF,"Name: %s %s\n", firstNames[i], lastNames[i]);
      fprintf(pF,"Adress: %hu ", streetNums[i]);
      fprintf(pF,"%s, %s\n", streetNames[i], cities[i]);
      fprintf(pF,"Date of Birth: %hu\n", birthYears[i]);
      //display parent info
      fprintf(pF,"\nParent/Guardian info: \n\n");
      fprintf(pF,"Name: %s %s\n", parentFirstNames[i], parentLastNames[i]);
      fprintf(pF, "Phone Number: %u\n", phoneNumbers[i]);
      printEnumToFile(parentRelationships[i], parentPhoneTypes[i], 0, pF);
      printEnumToFile(parentRelationships[i], parentPhoneTypes[i], 1, pF);
   }
   fclose(pF);
   printf("\nYour roster has been saved to a local file named 'roster.txt' \n");
}
void clearBuffer(){
   memset(buffer, 0, sizeof(buffer));
}
void getChoice(char *value, char prompt[]){
      do{
      printf("\n%s", prompt);
      scanf(" %c", value);
      clean_stdin();
      //validate choice
      if(*value == 'n' || *value == 'y'){
         isDataValid =true;
      }  else {
         printf("\nPlease enter \'y\' for yes and \'n\' for no.");
         isDataValid = false;
         continue;
      }
      }while(isDataValid == false);
}
void printEnum(enum relationships value, enum phoneTypes dummy, int toPrint){
   if(toPrint == 0){
   printf("Parent/Guardian Relationship: ");
      switch(value) {
         case MOTHER:
         printf("Mother\n");
         break;
         case FATHER: 
         printf("Father\n");
         break;
         case GRANDMOTHER:
          printf("Grandmother\n");
          break;
          case GRANDFATHER:
          printf("Grandfather\n");
          break;
          case OTHER:
          printf("other\n");
          break;
          case NORELATION:
            printf("No relation");
            break;
      }
   }
   if(toPrint == 1){
      printf("Phone Type: ");
      switch(dummy) {
         case CELL: 
         printf("Cell\n");
         break;
         case WORK: 
         printf("Work\n");
         break;
         case HOME:
          printf("Home\n");
          break;
         case NOPHONE:
            printf("NO PHONE");
      }
      }
}
void printEnumToFile(enum relationships value, enum phoneTypes dummy, int toPrint, FILE* pF){
   if(toPrint == 0){
   fprintf(pF,"Parent/Guardian Relationship: ");
      switch(value) {
         case MOTHER:
         fprintf(pF, "Mother\n");
         break;
         case FATHER: 
         fprintf(pF,"Father\n");
         break;
         case GRANDMOTHER:
         fprintf(pF,"Grandmother\n");
         break;
         case GRANDFATHER:
         fprintf(pF,"Grandfather\n");
         break;
         case OTHER:
         fprintf(pF,"other\n");
         break;
         case NORELATION:
         fprintf(pF,"No relation");
         break;
      }
   }
   if(toPrint == 1){
      fprintf(pF,"Phone Type: ");
      switch(dummy) {
         case CELL: 
         fprintf(pF,"Cell\n");
         break;
         case WORK: 
         fprintf(pF,"Work\n");
         break;
         case HOME:
         fprintf(pF,"Home\n");
         break;
         case NOPHONE:
         fprintf(pF,"NO PHONE");
      }
      }
}
void freeStringMemory(char **arr, int counter){
   int i;
   for(i = 0; i < counter; i++){
      free(arr[i]);
      arr[i] = NULL;
   }
   free(arr);
   arr = NULL;
}