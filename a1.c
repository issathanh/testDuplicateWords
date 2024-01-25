//-----------------------------------------
// NAME: Thanh Thuong
// STUDENT NUMBER: 7887762
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: 	Saulo Santos
// ASSIGNMENT: assignment 1, QUESTION: question 1
// 
// REMARKS: What is the purpose of this program?
// Convert the Duplicates.java Java program into a C program that performs identical processing, including automated testing.
//-----------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
static int testsExecuted = 0; 
static int testsFailed = 0; 
static const int MAX_WORD_LENGTH=15;

static void testCountDuplicateWords(int expected, char str[]);
static int countDuplicateWords( char str []); 
static bool findWord(char str [], char word [], int len);


int main (void)
{   
    printf("Testing typical cases\n");
    testCountDuplicateWords(0,"hello world"); 
    testCountDuplicateWords(0, "bye-bye"); 
    testCountDuplicateWords(1, "the quick brown foxes jumped over the lazy dogs"); 
    testCountDuplicateWords(0, "The quick brown foxes jumped over the lazy dogs"); 
    testCountDuplicateWords(2, "A palindrome: a man a plan a canal panama"); 
    testCountDuplicateWords(8, "I felt happy because I saw the others were happy and because I knew I should feel happy but I wasn’t really happy"); 
    testCountDuplicateWords(3, "One fish two fish\nred fish blue\nfish"); 
    testCountDuplicateWords(5, "doo be \t doo be \t doo be \t  doo"); 
    testCountDuplicateWords(8, "... -- -- -- ...\n... -- -- -- ..."); 
    testCountDuplicateWords(26, "a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z"); 


    printf("\nTesting empty cases\n"); 
    testCountDuplicateWords(0, "");
    testCountDuplicateWords(0, " ");
    testCountDuplicateWords(0, "\t \t");
    testCountDuplicateWords(0, "   \n  \n  ");

    printf("\nTesting invalid cases\n"); 
    testCountDuplicateWords(-1, "the word antidisestablishmentarianism is very long but antidisestablishmentarianism is a political movement");
    testCountDuplicateWords(-1, "abcdefghijabcdef");
    testCountDuplicateWords(0, "abcdefghijabcde");

    printf("\nTesting edge cases\n"); 
    testCountDuplicateWords(1, "go Jets go");
    testCountDuplicateWords(2, "tomato tomato potato potato");
    testCountDuplicateWords(2, " tomato tomato potato potato ");
    testCountDuplicateWords(7, "buffalo buffalo buffalo buffalo buffalo buffalo buffalo buffalo");


    printf("\nThese tests will be opposite in the C version\n"); 
    testCountDuplicateWords(1, "In Java, the strings may contain \0 in the interior");
    testCountDuplicateWords(0, "In C, the strings cannot contain \0 in the interior");
    
    printf("\nTotal number of tests executed: %d", testsExecuted); 
    printf("\nNumber of tests passed:         %d" , (testsExecuted - testsFailed));
    printf("\nNumber of tests failed:         %d" , (testsFailed));


    return 0; 
}

//------------------------------------------------------
// testCountDuplicateWords
//
// PURPOSE: compare resullt with expected, if they match print passedalong with the tested string, if dont match print failed along iwth result, expected value and the tested string
//also increment testFailed to keep track of number of failed test and regardless of outcome, testExecute is incremented to track total number of tests
// INPUT PARAMETERS: an expected result and a string to test
//------------------------------------------------------
static void testCountDuplicateWords (int expected, char str [])
{
    int result = countDuplicateWords(str);
    if (result == expected)
    {
        printf("Passed: %d from '%s'\n", result, str); 
    }
    else 
    {
        printf("FAILED: %d instead of %d from '%s'\n", result, expected,str);
        testsFailed++; 
    }
    
    testsExecuted++; 
}
//------------------------------------------------------
// countDuplicateWords
//
// PURPOSE: count the number of duplicate words in a given string 
// INPUT PARAMETERS: String to look for duplicate words
// OUTPUT PARAMETERS: return the number of duplicated word
//------------------------------------------------------
static int countDuplicateWords( char str [])
{

    int count = 0; 
    int wordIndex = 0; 
    char word [MAX_WORD_LENGTH+1]; 
    int pos; 
    char currentChar; 

    pos = 0; 
    while(str[pos] != '\0' && count >= 0)
    //loop through each char as long as not the end of string
    {
        currentChar = str[pos]; 
        if (isspace((unsigned char) currentChar)) //since issa space expect int
        //converting unsigned char to char ensure that char get converted correctly
        //if current char is a space
        {
            word[wordIndex++] = '\0'; 
            if(strlen(word) > 0)
            //check if a word has been formed
            { 
                if(findWord(&str[pos+1],word,wordIndex-1))
                //create a sub string starting from the pos position of str
                //until the end
                {
                    //if duplicate is found increment count
                    count++; 
                }
                
                //move the pointer of word to the beginning of word a gain to reset it     
            } 
            wordIndex = 0; 

        }
            else 
            {
                if(wordIndex >= MAX_WORD_LENGTH )
                {
                    count = -1; 
                    //if adding a character makes the word longer than MAX_WORD_LENGTH
                    //count is set to -1 to end the loop
                }
                else
                {
                    word[wordIndex++] = currentChar; 
                    //wordIndex++; 
                }
            }
            pos++; 
    }
    return count; 
}

//------------------------------------------------------
// findWord
//
// PURPOSE: check wether the 'word' found has a duplicate in the str  
// INPUT PARAMETERS: 'word' to check for duplicate from the str 
// OUTPUT PARAMETERS: return a bool to see if a word was found duplicated or not
// parameters.
//------------------------------------------------------    
static bool findWord(char str [], char word [], int len)
{
    char checkWord [MAX_WORD_LENGTH]; 
    int checkPos = 0; 
    bool dontCheckWord, found = 0; 
    char checkChar; 
    int wordIndex = 0; 
    dontCheckWord = 0; 
    //printf("string str is: %s\n", str );
    while(str[checkPos] != '\0' && !found)
    //loop through characters of str using checkpos
    {
        checkChar = str[checkPos]; 
        if(isspace((unsigned char) checkChar))
        {//if theres a space
            checkWord[wordIndex++] = '\0';
            //printf("the word getting check: '%s\n", checkWord); 
            if(!strcmp(word,checkWord) && !dontCheckWord)
            //strcmp reutrn 0 when the word match !strcmp to return true to identify when the word match
            {
                found = 1;  // if found a duplicate set found as true
            }
            dontCheckWord = 0; 
            wordIndex = 0; 
            //reset dontCheckWOrd and checkWord
        }
        else
        {
            if(wordIndex >= len)
            {
                //if the length of checkWOrd bigger than the word length
                dontCheckWord = 1; 
            }
            else 
            {
                //printf("before adding checkchar: '%s', checkChar is: '%c'\n",checkWord,checkChar);
                checkWord[wordIndex++] = checkChar;  
                //else set the current char to be = the string char 
                //increment the wordIndex
            }
        }
        checkPos++;
    }
    checkWord[wordIndex++] = '\0'; 
    if(!found && !dontCheckWord && strlen(word) > 0)
    {
        if(!strcmp(word,checkWord))
        {
            found = 1; 
        }
    }


    return found; 
}