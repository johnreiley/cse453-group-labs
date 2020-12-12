/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER05_H
#define CIPHER05_H

#define NAME "cipher05 Unit Test"

#include <cassert>
#include <string>
#include <algorithm>
#include <cmath>
#include <cctype>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher05 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "John Reiley"; }
   virtual std::string getCipherName() { return "Rail Fence Cipher"; }
   virtual std::string getEncryptAuth() { return "Benjamin Hansen"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "crypto.interactive.maths.com (2019), ";
      s += "\"Rail Fence Cipher\', \n   retrieved: ";
      s += "https://crypto.interactive-maths.com/rail-fence-cipher.html";
      return s;
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // The encrypt pseudocode
      str = "encrypt(plainText, password)\n";
      str += "   ASSERT password is integer and > 1\n";
      str += "   strippedText <- stripNonAlphaChars(plainText)\n";
      str += "   grid <- [password][length of strippedText]\n";
      str += "   interval <- 2 * password - 2\n";
      str += "   FOR letter is all values of strippedText, i is index\n";
      str += "      row <- getRow(i, interval)\n";
      str += "      grid[row][i] <- letter\n";
      str += "   FOR each array in grid\n";
      str += "      FOR each element in array\n";
      str += "         IF element is not empty\n";
      str += "            cipherText <- element\n";
      str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
      str += "decrypt(cipherText, password)\n";
      str += "   grid <- [password][length of cipherText]\n";
      str += "   interval <- 2 * password - 2\n";
      str += "   FOR letter is all values of cipherText, i is index\n";
      str += "      row <- getRow(i, interval)\n";
      str += "      grid[row][i] <- placeholder\n";
      str += "   currentLetter <- 0\n";
      str += "   FOR each array in grid, i is index\n";
      str += "      FOR each element in array, j is index\n";
      str += "         IF element has placeholder\n";
      str += "            grid[i][j] <- cipherText[currentLetter]\n";
      str += "   FOR length of cipherText, i is index\n";
      str += "      row <- getRow(i, interval)\n";
      str += "      plainText += grid[row][i]\n";
      str += "   RETURN plainText\n\n";

      // Helper function
      str += "stripNonAlphaChars(text)\n";
      str += "   strippedText <- empty string\n";
      str += "   FOR char is all values of text\n";
      str += "      IF char is letter\n";
      str += "         strippedText += char\n";
      str += "   RETURN strippedText\n\n";

      // Helper function
      str += "getRow(index, interval)\n";
      str += "   IF index % interval < (interval / 2)\n";
      str += "      RETURN index % interval\n";
      str += "   ELSE\n";
      str += "      RETURN absolute value of ((index % (interval / 2)) - interval)";
      str += " / 2\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText = "";
      std::string strippedText = "";
      int row = 0; // used below to fill fence
      int interval = 0; // reset below
      // since the values for key and plaintext length will be variable,
      // we need to use standard libraries instead of predefined values
      std::vector<std::vector<char>> grid; // empty for now
     
      // remove when certain assumptions are met
      unitTests();
      
      /* use password */
      // update to pseudocode
      // in order to work with all possible passwords, if a non-number password is
      // used, take the length of string instead of the values as the key
      // so, if password is a number, return the absolute value of the number
      // else set the key to be the length of the password
      int key = isInteger(password) ? abs(std::stoi(password)) : password.length();

      // update to pseudocode
      // do something for zero-length keys
      // fences of length 1 or less are pointless. Restrict key to be at least 3
      if (key < 3)
          key = 3; 
      
      // now assign interval value
      interval = 2 * key - 2;

      std::cerr << "Key Length: " << key << std::endl;
      
      /* encrypt plaintext */
      // if plaintext contains invalid characters, remove them
      strippedText = stripNonAlphaChars(plainText);

      // setup grid
      // define our 2D grid with a fence length equal to the length of the plaintext
      // and a fence height equal to the key
      // a vector of vectors
      // allocate enough space for key number of rows (vectors) with each
      // vector having a length equal to the length of the strippedText
      // key is the size. the second argument initializes each row to be a 
      // vector of size strippedText.length(), each sub-vector being initialized
      // with a sequence of null characters
      grid = std::vector<std::vector<char>>(key, 
              std::vector<char>(strippedText.length(), '\0')); // # rows
      
      // fill in fence from left to right with index
      for (int i = 0; i < strippedText.length(); ++i)
      {
          row = getRow(i, interval);
          grid[row][i] = strippedText[i]; // insert letter
      }

      // should be filled in
      displayGrid(grid);

      // now the actual encryption. Read from fence across rows
      // the valid characters (non-null characters) and create our 
      // encryption string
      // walk-through each sub-vector with standard constant iterator
      for (typename std::vector<std::vector<char>>::const_iterator it = 
              grid.begin();
              it != grid.end(); ++it)
      {
          // walk-through each character in the sub-vector
          for (typename std::vector<char>::const_iterator itChar = it->begin(); 
                  itChar != it->end(); ++itChar)
          {
              // if the element is not the null character, add to our cipherText
              if (*itChar != '\0') 
              {
                  cipherText += *itChar; // append letter to cipherText
              }
          }
      }


      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string plainText;

	  std::vector<std::vector<char>> grid;
	  int row;
	  int key = isInteger(password) ? abs(std::stoi(password)) : password.length();
	  // sets lower bound on key
	  if (key < 3)
		  key = 3;
	  int interval = 2 * key - 2;
	  grid = std::vector<std::vector<char>>(key,
		  std::vector<char>(cipherText.length(), '\0'));
	  
	  for (int i = 0; i < cipherText.length(); ++i)
	  {
		  row = getRow(i, interval);
		  grid[row][i] = '*'; // insert 
	  }
	  displayGrid(grid);

	  int currentLetter = 0;
	  for (typename std::vector<std::vector<char>>::iterator it =
		  grid.begin();
		  it != grid.end(); ++it)
	  {
		  // walk-through each character in the sub-vector
		  for (typename std::vector<char>::iterator itChar = it->begin();
			  itChar != it->end(); ++itChar)
		  {
			  // if not null, insert 
			  if (*itChar == '*')
			  {
				   *itChar = cipherText[currentLetter++]; // add letter to grid
			  }
		  }
	  }
	  for (int i = 0; i < cipherText.length(); i++)
	  {
		  row = getRow(i, interval);
		  plainText += grid[row][i]; // insert 
	  }
      return plainText;
   }
private:
   /*********************************************************
    * IS NUMBER
    * Author(s): Benjamin Hansen
    * Returns true if the string is simply a number with no
    * non-number characters
    * Ideas and algorithm taken from: https://stackoverflow.com
    * /questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
    *********************************************************/
   bool isInteger(const std::string s)
   {
       // catch if the number is negative. If so, we still 
       // should return true even though ever character is not a digit
       bool isNegative = s[0] == '-';
       // return true if the string isn't empty and
       // find returns the end iterator for all characters of s
       // using a anonymous functional predicate 
       // Give to the find function the beginning of the string if no negative,
       // if negative, give the next character to begin()
       return !s.empty() && std::find_if(!isNegative ? s.begin() : ++(s.begin()),
               s.end(), [](unsigned char c) { return !std::isdigit(c); }) 
           == s.end();
   }

   /**********************************************************
    * STRIP NON ALPHA CHARS
    * Author(s): Benjamin Hansen
    * Remove from string all non-alphabet characters unless
    * character is a space
    *********************************************************/
   std::string stripNonAlphaChars(std::string plainText)
   {
       std::string strippedText = "";
       // for each character, test if the character isalpha
       for (const char c : plainText)
       {
           // spaces are allowed by citation as well
           if (isalpha(c) || c == ' ')
           {
               strippedText += c;
           }
       }
       return strippedText;
   }

   /*********************************************************
    * GET ROW
    * Author(s): Benjamin Hansen
    * Return the row 
    *********************************************************/
   int getRow(int index, int interval)
   {
       if (index % interval < (interval / 2))
           return index % interval;
       else
           return abs(index % (interval / 2) - interval / 2);
   }

   /**********************************************************
    * UNIT TESTS
    * Author(s): Benjamin Hansen
    * Test our functions, especially isInteger, to verify it 
    * works as expected
    **********************************************************/
   void unitTests()
   {
       std::cout << NAME << ": testing isInteger()\n";
       // one char
       assert(isInteger("1"));
       // multiple chars
       assert(isInteger("123"));
       // one char with invalid in it
       assert(!isInteger("1-"));
       // one char with invalid in it, trick negative
       assert(!isInteger("-1-"));
       // multiple chars
       assert(isInteger("123"));
       // multiple chars with invalid in it
       assert(!isInteger("123?"));
       // multiple chars with invalid in it, trick negative
       assert(!isInteger("-123 "));
       // negative number
       assert(isInteger("-1"));
       // negative number multiple chars
       assert(isInteger("-1123123123"));
       std::cout << NAME << ": passed isInteger() tests\n";
       
       std::cout << NAME << ": testing stripNonAlphaChars()\n";
       assert(stripNonAlphaChars("asdflkj") == std::string("asdflkj"));
       assert(stripNonAlphaChars(".asdflkj") == std::string("asdflkj"));
       assert(stripNonAlphaChars("a?sdf.lk.j") == std::string("asdflkj"));
       assert(stripNonAlphaChars("            asdflkj") == 
               std::string("            asdflkj"));
       assert(stripNonAlphaChars("as             dflkj") == 
               std::string("as             dflkj"));
       assert(stripNonAlphaChars("123asdflkj") == std::string("asdflkj"));
       assert(stripNonAlphaChars("asdflkj?") == std::string("asdflkj"));
       assert(stripNonAlphaChars("1234578734928374") == std::string(""));
       assert(stripNonAlphaChars("1234578734928374y") == std::string("y"));
       assert(stripNonAlphaChars("\n1234578734928374y") == std::string("y"));
       assert(stripNonAlphaChars("") == std::string(""));
       std::cout << NAME << ": passed stripNonAlphaChars() tests\n";
   }

   /******************************************************
    * DISPLAY GRID
    * Author(s): Benjamin Hansen
    * A helper function to display the fence
    ******************************************************/
   void displayGrid(const std::vector<std::vector<char>> grid)
    { 
        // cout header
        std::cout << "Grid:\n";

        for (typename std::vector<std::vector<char>>::const_iterator it = 
                grid.begin();
                it != grid.end(); ++it)
        {
            // walk-through each character in the sub-vector
            for (typename std::vector<char>::const_iterator itChar = 
                    it->begin(); 
                    itChar != it->end(); ++itChar)
            {
                // if the element is not the null character, add to our cipherText
                if (*itChar != '\0') 
                {
                    std::cout << " " << *itChar << " ";
                }
                else
                    std::cout << "   ";
            }
            // newline
            std::cout << "\n";
        }
   }
};

#endif // CIPHER05_H
