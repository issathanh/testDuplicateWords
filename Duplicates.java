public class Duplicates {
    private static int testsExecuted = 0;
    private static int testsFailed = 0;
  
    private static final int MAX_WORD_LENGTH=15;
  
    public static void main(String[] args) {
      System.out.println("Testing typical cases\n");
      testCountDuplicateWords(0, "hello world");
      testCountDuplicateWords(0, "bye-bye");
      testCountDuplicateWords(1, "the quick brown foxes jumped over the lazy dogs");
      testCountDuplicateWords(0, "The quick brown foxes jumped over the lazy dogs");
      testCountDuplicateWords(2, "A palindrome: a man a plan a canal panama");
      testCountDuplicateWords(8, "I felt happy because I saw the others were happy and because I knew I should feel happy but I wasn’t really happy");
      testCountDuplicateWords(3, "One fish two fish\nred fish blue\nfish");
      testCountDuplicateWords(5, "doo be \t doo be \t doo be \t  doo");
      testCountDuplicateWords(8, "... -- -- -- ...\n... -- -- -- ...");
      testCountDuplicateWords(26, "a b c d e f g h i j k l m n o p q r s t u v w x y z a b c d e f g h i j k l m n o p q r s t u v w x y z");
  
      System.out.println("\nTesting empty cases\n");
      testCountDuplicateWords(0, "");
      testCountDuplicateWords(0, " ");
      testCountDuplicateWords(0, "\t \t");
      testCountDuplicateWords(0, "   \n  \n  ");
  
      System.out.println("\nTesting invalid cases\n");
      testCountDuplicateWords(-1, "the word antidisestablishmentarianism is very long but antidisestablishmentarianism is a political movement");
      testCountDuplicateWords(-1, "abcdefghijabcdef");
      testCountDuplicateWords(0, "abcdefghijabcde");
  
      System.out.println("\nTesting edge cases\n");
      testCountDuplicateWords(1, "go Jets go");
      testCountDuplicateWords(2, "tomato tomato potato potato");
      testCountDuplicateWords(2, " tomato tomato potato potato ");
      testCountDuplicateWords(7, "buffalo buffalo buffalo buffalo buffalo buffalo buffalo buffalo");
  
      System.out.println("\nThese tests will be opposite in the C version\n");
      testCountDuplicateWords(1, "In Java, the strings may contain \0 in the interior");
      testCountDuplicateWords(0, "In C, the strings cannot contain \0 in the interior");
    
      System.out.println("\nTotal number of tests executed: " + testsExecuted);
      System.out.println("Number of tests passed:         " + (testsExecuted - testsFailed));
      System.out.println("Number of tests failed:         " + testsFailed);
    }
//------------------------------------------------------
// testCountDuplicateWords
//
// PURPOSE: compare resullt with expected, if they match print passedalong with the tested string, if dont match print failed along iwth result, expected value and the tested string
//also increment testFailed to keep track of number of failed test and regardless of outcome, testExecute is incremented to track total number of tests
// INPUT PARAMETERS: an expected result and a string to test
//------------------------------------------------------
    private static void testCountDuplicateWords(int expected, String str) {
      int result = countDuplicateWords(str);
      
      if (result == expected) {
        System.out.println("Passed: " + result + " from '" + str + "'");
      } else {
        System.out.println("FAILED: " + result + " instead of " + expected + " from '" + str + "'");
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
    public static int countDuplicateWords(String str) {
      int count = 0;
      String word = "";
      int pos;
      char currentChar;
      
      pos = 0;
      while (pos < str.length() && count >= 0) {
        //loop thru each char using pos
        currentChar = str.charAt(pos);
        if (Character.isWhitespace(currentChar)) {
            //if current char is a white space check if a word has been formed
          if (word.length() > 0) {
            //check if a word has been formed
            if (findWord(str.substring(pos), word)) {
                //call find word if this word appears again in the remainder of the string
                //if a duplicate is found count is incremented 
              count++;
            }
            //word is reset to start forming the next word
            word = "";
          }
        } else {
          if (word.length() >= MAX_WORD_LENGTH) {
            count = -1;
            //if addeing a character makes the word longer than MAX_WORD_LENGTH
            //count is set to -1 to end the loop
          } else {
            word += currentChar;
            //else if character is not a white space then add a character to word
          }
        }
        pos++; 
        //increment position to move to the next character 
      }
      
      return count;
      //once the loop end return count, the number of duplicate words found or -1
      //if an invalid word is encountered
    }
//------------------------------------------------------
// findWord
//
// PURPOSE: check wether the 'word' found has a duplicate in the str  
// INPUT PARAMETERS: 'word' to check for duplicate from the str 
// OUTPUT PARAMETERS: return a bool to see if a word was found duplicated or not
// parameters.
//------------------------------------------------------    
    private static boolean findWord(String str, String word) {
      String checkWord = "";
      int checkPos = 0;
      boolean dontCheckWord, found = false;
      char checkChar;
  
      dontCheckWord = false;
      while (checkPos < str.length() && !found) {
        //loop through the characters of str using checkpos
        checkChar = str.charAt(checkPos);
        //if the current character is a white space
        if (Character.isWhitespace(checkChar)) {
          if (word.equals(checkWord) && !dontCheckWord) {
            //checkWord matched word and dontCheckWord is false
            found = true;
          }
          dontCheckWord = false;
          checkWord = "";
          //reset dontCheckWord and checkWord
        } else {
          if (checkWord.length() >= word.length()) {
            //if the length of checkWOrd bigger than the word length
            dontCheckWord = true;
            //set dont checkWord to true
          } else {
            checkWord += checkChar;
            // add a character at the end of checkWord if theres no white space and the 
            //checWord is not bigger than word's length
          }
        }
        checkPos++; // increment position to move to the next character
      }
      
      //since the loop check a word when encounter a white space
      //this is to check the last word since the last word wont encounter 
      //a white space at the end 
      if (!found && !dontCheckWord && word.length() > 0)
        found = word.equals(checkWord); 
      
      return found;
    }
  }