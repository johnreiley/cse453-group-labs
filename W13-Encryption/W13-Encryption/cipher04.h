/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Joseph Sanderson"; }
   virtual std::string getCipherName() { return "Baconian Cipher"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "geeksforgeeks.org (2018), ";
      s += "\"Baconian Cipher\', \n   retrieved: December 11, 2020";
      s += "https://www.geeksforgeeks.org/baconian-cipher/";
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
      str =  "encrypt(password)\n";
      str += "declare map\n";
      str += "fill map\n";
      str += "FOR each character in password\n";
	   str += "         index through(plainText)\n";
	   str += "            plainText[?] = map index?\n";
		str += "            map index? = cipherText\n";
	   str += "      Return cipherText\n";

      // The decrypt pseudocode
      str =  "decrypt(cipherText, map)\n";
      str += "FOR each character in cipherText, variable+=7\n";
	   str += "         index through(cipherText)\n";
      str += "          split cipherText every 7 characters\n";
	   str += "            cipherText[?] = map[?]\n";
		str += "               map[?] = plainText\n";
	   str += "      Return plainText\n";

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

#endif // CIPHER04_H
