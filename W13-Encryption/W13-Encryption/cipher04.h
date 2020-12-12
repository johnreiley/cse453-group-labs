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

      // a reverse-lookup map to reverse the letter-to-string mappings
      // done in lookup
      std::map<std::string, char> reverseLookup = {
         {"aaaaa", 'A'}, {"aaaab", 'B'}, {"aaaba", 'C'}, {"aaabb", 'D'},
         {"aabaa", 'E'}, {"aabab", 'F'}, {"aabba", 'G'}, {"aabbb", 'H'},
         {"abaaa", 'I'}, {"abaab", 'J'}, {"ababa", 'K'}, {"ababb", 'L'},
         {"abbaa", 'M'}, {"abbab", 'N'}, {"abbba", 'O'}, {"abbbb", 'P'},
         {"baaaa", 'Q'}, {"baaab", 'R'}, {"baaba", 'S'}, {"baabb", 'T'},
         {"babaa", 'U'}, {"babab", 'V'}, {"babba", 'W'}, {"babbb", 'X'},
         {"bbaaa", 'Y'}, {"bbaab", 'Z'}
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
      str +=  "decrypt(cipherText, map)\n";
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
    * Encrypt plaintext given a password converted to a number
    * which will change how long the character-to-string mappings
    * will be in the mapped string if the password is greater than
    * 5.
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
    * Decrypt the ciphertext using the reverseLookup table
    * Use the password to confirm the key size
    **********************************************************/
   virtual std::string decrypt(const std::string& cipherText,
      const std::string& password)
   {
      // convert the password into a bit-length
      int bits = convert(password);

      std::string plainText = "";

      // loop through bits-number of characters at a time
      // to extract the ciphertext
      for (int i = 0; i < cipherText.length(); )
      {
         /****************************************************
          * check for space. If character is not a space,
          * then we have bits-number of characters to extract
          * we only need 5 characters though since the map
          * has letter to 5-length string mappings and
          * the ciphertext will contain leading a's if 
          * bits > 5
          ****************************************************/
         if (cipherText[i] != ' ')
         {
            /*******************************************************
             * take 5 of characters from i and lookup its value
             * in the reverseLookup table to get the corresponding
             * character
             * To get the 5 bits we want, add the bit-length to
             * i and then subtract 5 to get the start of the valid 
             * string mapping
             *******************************************************/
            std::cerr << "cipherText.substr(i + bits - 5, 5) = " 
               << cipherText.substr(i + bits - 5, 5) << std::endl;
            std::cerr << "reverseLookup[cipherText.substr(i + bits - 5, 5)] = " 
               << reverseLookup[cipherText.substr(i + bits - 5, 5)] << std::endl;
            plainText += this->reverseLookup[cipherText.substr(i + bits - 5, 5)];
            // increment bits away from here
            i += bits;
            std::cerr << "cipherText[i] is not a space, i increment = " << i << std::endl;
         }
         else // add space and iterate by 1
         {
            plainText += " ";
            // increment to the next set, which will be one character away
            ++i;
            std::cerr << "cipherText[i] is a space, ++i = " << i << std::endl;
         }
      }

      return plainText;
   }
};

#endif // CIPHER04_H
