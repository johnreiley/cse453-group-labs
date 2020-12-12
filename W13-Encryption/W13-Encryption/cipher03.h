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
   virtual std::string getEncryptAuth() { return "Joseph Sanderson"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

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
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText = plainText;
  	std::string key = password;
		string key
  		{
    			for(int i = 0; i < key.size(); ++i)
    			{
      				if(key[i] >= 'A' && key[i] <= 'Z')
        			this->key += key[i];
      				else if(key[i] >= 'a' && key[i] <= 'z')
        			this->key += key[i] + 'A' - 'a';
    			}
		string encrypt(string plainText)
  		{
    		std::string cipherText;
 		
		int j = 0;
    		for(int i = 0, i < plainText.length(); ++i)
    		{
      			std::string add = plainText[i];
 
      			if(add >= 'a' && add <= 'z')
        		add += 'A' - 'a';
      			else if(add < 'A' || add > 'Z')
        		continue;
 			cipherText += (add + key[j] - 2*'A') % 26 + 'A'; 
      			j = (j + 1) % key.length();
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
      std::string plainText = cipherText;
      
      return plainText;
   }
};

#endif // CIPHER03_H
