/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER05_H
#define CIPHER05_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher05 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "John Reiley"; }
   virtual std::string getCipherName() { return "Rail Fence Cipher"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
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
      str += "   IF index + % interval < (interval / 2)\n";
      str += "      RETURN index % interval\n";
      str += "   ELSE\n";
      str += "      RETURN absolute value of (index % (interval / 2)) - interval / 2\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText = plainText;
      // TODO - Add your code here
      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string plainText = cipherText;
      // TODO - Add your code here
      return plainText;
   }
};

#endif // CIPHER05_H