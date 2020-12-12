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
   virtual std::string getEncryptAuth() { return "John Reiley"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   private :
      std::map<char, std::string> lookup = {
         {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"},
         {'E', "aabaa"}, {'F', "aabab"}, {'G', "aabba"}, {'H', "aabbb"},
         {'I', "abaaa"}, {'J', "abaab"}, {'K', "ababa"}, {'L', "ababb"},
         {'M', "abbaa"}, {'N', "abbab"}, {'O', "abbba"}, {'P', "abbbb"},
         {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"},
         {'U', "babaa"}, {'V', "babab"}, {'W', "babba"}, {'X', "babbb"},
         {'Y', "bbaaa"}, {'Z', "bbaab"}
      };

      /**********************************************************
       * CONVERT
       * Converts a password into an int that is usable by the
       * Baconian cipher.
       **********************************************************/
      int convert(std::string password)
      {
         int bits;
         try
         {
            // if the password has a number, use as bits
            bits = stoi(password);
         }
         catch (const std::exception& e)
         {
            // use length as bits
            bits = password.length();
         }

         if (bits < 5) {
            return 5;
         }
         else
         {
            return bits;
         }
      }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      std::string s;
      s += "geeksforgeeks.org (2018), ";
      s += "\"Baconian Cipher\', \n   retrieved: December 11, 2020\n";
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
      std::string cipherText = "";
    
      int bits = convert(password);

      for (int i = 0; i < plainText.length(); i++)
      {
         char character = toupper(plainText[i]);
         if (character >= 'A' && character <= 'Z')
         {
            std::string extraBits = "";
            if (bits - 5 > 0) {
               // build the extra bits
               for (int i = 0; i < bits - 5; i++)
               {
                  extraBits += "a";
               }
               cipherText += extraBits;
            }
            // get the code cooresponing to the letter
            cipherText += this->lookup[character];
         }
         else if (character == 32)
         {
            cipherText += " ";
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
      int bits = convert(password);

      std::string plainText = cipherText;
      string * splitCipher = new string[cipherText.length()];
      // split the cipher by size of bits


      //for (int i = 0; i < (*splitCipher).length(); i++)
      //{
      //   char character = cipherText[i];
      //   if (character)
      //   for (const auto& keyValue : lookup)
      //   {

      //   }
      //}

      return plainText;
   }
};

#endif // CIPHER04_H
