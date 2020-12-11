/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Justen Neeley"; }
   virtual std::string getCipherName() { return "Vigenere Cipher"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("DCode. (2020). Vigenere Cipher. Retrieved December 11, 2020, from https://www.dcode.fr/vigenere-cipher");
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
	  str += "   
	  str += "   FOR p is all values of plainText\n";
	  str += "      index <- indexFromCharacter(*p)+ indexFromCharacter(password++) % size\n";
	  str += "      cipherText += characterFromIndex(index)\n";
	  str += "   RETURN cipherText\n\n";

      // The decrypt pseudocode
	  str = "decrypt(plainText, password)\n";
	  str += "   
      str += "   FOR p is all values of cipherText\n";
	  str += "      index <- indexFromCharacter(*p) - indexFromCharacter(password++) % size\n";
	  str += "      cipherText += characterFromIndex(index)\n";
	  str += "   RETURN cipherText\n\n";

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
      // TOD
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

#endif // CIPHER03_H