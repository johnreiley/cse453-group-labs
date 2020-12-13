/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H
#include <iostream>
/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Justen Neeley"; }
   virtual std::string getCipherName() { return "Vigenere Cipher"; }
   virtual std::string getEncryptAuth() { return "Joseph Sanderson"; }
   virtual std::string getDecryptAuth() { return "John Reiley"; }

private: 
   /****************************************************************
    * CONVERT TO KEY
    * Helper function for turning the user's input password into
    * a usable key.
    ****************************************************************/
   std::string convertToKey(const std::string& password)
   {
      std::string key;
      for (int i = 0; i < password.size(); ++i)
      {
         if (password[i] >= 'A' && password[i] <= 'Z')
            key += password[i];
         else if (password[i] >= 'a' && password[i] <= 'z')
            key += password[i] + 'A' - 'a';
      }
      return key;
   }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("LaMagna, E. (2010). Vigenère Cipher. Retrieved December 11, 2020, from https://www.cs.uri.edu/cryptography/classicalvigenere.htm");
      // For encryption
      return std::string("Mol, Micheal (2020). Vigenère cipher. Retrieved December 12, 2020, from https://rosettacode.org/wiki/Vigen%C3%A8re_cipher#C.2B.2B");
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
	  str = "encrypt(plainText, password)\n";
	  str += "   FOR p is all values of plainText\n";
	  str += "      index <- indexFromCharacter(*p)+ indexFromCharacter(password++) % size\n";
	  str += "      cipherText += characterFromIndex(index)\n";
	  str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
	  str = "decrypt(plainText, password)\n";
      str += "   FOR p is all values of cipherText\n";
	  str += "      index <- indexFromCharacter(*p) - indexFromCharacter(password++) % size\n";
	  str += "      cipherText += characterFromIndex(index)\n";
	  str += "   RETURN cipherText\n\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * Encrypts plain text using the Vigenere cipher
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText;
      std::string key = convertToKey(password);

		int j = 0;
    	for(int i = 0; i < plainText.length(); ++i)
    	{
         char add = plainText[i];
 
      	if(add >= 'a' && add <= 'z')
        	   add += 'A' - 'a';
      	else if(add < 'A' || add > 'Z')
        	   continue;
 		   cipherText += (add + key[j]) % 26 + 'A';
      	j = (j + 1) % key.length();
    	}
      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * Decrypts a Vigenere cipher text
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      std::string plainText;
      std::string key = convertToKey(password);

      int j = 0;
      for (int i = 0; i < cipherText.length(); ++i)
      {
         char add = cipherText[i];

         // make sure it's uppercase
         if (add >= 'a' && add <= 'z')
            add += 'A' - 'a';
         else if (add < 'A' || add > 'Z')
            continue;
         char res;
         res = (add - key[j]);
         if (res < 0)
         {
            res += 26;
         }
         // bring the value back into the A-Z range
         plainText += res + 'A';
         j = (j + 1) % key.length();
      }
      
      return plainText;
   }
};

#endif // CIPHER03_H
