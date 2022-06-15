#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_PLAYERS 10
#define MAX_NAME_LEN 32
#define MAX_CITY_LEN 64
#define BUFFER_SIZE 1024
//declare global arrays for variables and global bool validator
char firstNames[MAX_PLAYERS][MAX_NAME_LEN];
char cities[MAX_PLAYERS][MAX_CITY_LEN];
unsigned short birthYears[MAX_PLAYERS];
char buffer[BUFFER_SIZE];
bool isDataValid = false;
//fucntion prototypes to check parameters and maintain code readability(otherwise all function definitions would be before main)
void printSummary(int counter, int start); 
void getName(char value[], int MAX_LEN, char prompt[]);
void retrieveShort(unsigned short *value, int min, int max, char prompt[]);
void getChoice(char *value, char prompt[]);
void clean_stdin(void);
int main() {
//establish variables that control flow of program and anything else that still needs to be declared
   char prompt[50];
   char choice;
   char infoCorrect;
   int counter = 0;
    do{
      counter++;
      int curIndex = counter - 1;      //curindex of players[]
      //get child last and first name
      strcpy(prompt, "Enter your first name: ");
      getName(firstNames[curIndex], MAX_NAME_LEN, prompt);
      //retrieve city name
      strcpy(prompt, "Enter the name of the city you were born: ");
      getName(cities[curIndex], MAX_CITY_LEN, prompt);
      //retrieve birthyear
      strcpy(prompt, "Enter your birth year: ");
      unsigned short *pBirthYear = &birthYears[curIndex];
      retrieveShort(pBirthYear, 2010, 2013, prompt);
      //display current input info to see if user is okay with input
        printSummary(counter, curIndex);
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
   printSummary(counter, 0);
   return 0;
}
void getName(char value[], int MAX_LEN, char prompt[]){
    bool isDataValid;
   do{
         // retrieve name
         printf("%s", prompt);
         strcpy(buffer, "");
         scanf("%[^\n]s", buffer);
         //validate name
         if(strlen(buffer) > MAX_LEN){
            printf("That name is too long! Please enter a name no longer than %d characters.\n", MAX_LEN);
            clean_stdin(); // prevents error if user inputs string > MAXlength WITH spaces when asking for input again
            isDataValid = false;
            continue;
         } else {
            strcpy(value, buffer);
            isDataValid = true;
            clean_stdin();
         }
      } while(isDataValid == false);
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
void printSummary(int counter, int start){
   printf("\n\n///////////////SUMMARY///////////////\n\n\n");
   int playerNum;
   int i;
      for(i = start; i < counter; i++){
      playerNum = i + 1;
      printf("\n\n\t\t****Player %d****\n", playerNum);
      //display childs info
      printf("Name: %s\n", firstNames[i]);
      printf("City: %s\n",cities[i]);
      printf("Date of Birth: %hu\n", birthYears[i]);
   }
   if(counter >= 10){printf("\nYou have entered the max ammount of inputs. Your summary is printed above^^^.\nThank you for your input!\n");}
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