#include <list>
/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Garrett Smith"; }
   virtual std::string getCipherName() { return "Bifid Cipher"; }
   virtual std::string getEncryptAuth() { return "encrypt author"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
      return std::string("citation");
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
      str = "insert the encryption pseudocode\n";

      // The decrypt pseudocode
      str += "insert the decryption pseudocode\n";

      return str;
   }

   void buildPolybiusSquare(char square[][5], std::string key)
   {
	   std::string alphabet = "abcdefghi*klmnopqrstuvwxyz";
	   std::string polybius = "";
	   for (int i = 0; i < key.size(); i++)
	   {
		   if (key[i] != 'j')
		   {

			   key[i] = tolower(key[i]);
		   }
		   else
		   {
			   continue;
		   }

		   if (key[i] == alphabet[(int)key[i] - 97])
		   {
			   polybius += key[i];
			   alphabet[(int)key[i] - 97] = '*';

		   }

	   }
	   polybius += alphabet;
	   int i = 0;
	   for (int r = 0; r < 5; r++)
		   for (int c = 0; c < 5; c++)
		   {

			   square[c][r] = polybius[i];
			   i++;
			   while (polybius[i] == '*')
				   i++;
		   }
   }


   void displayPolybiusSquare(char alphabet[][5])
   {
	   for (int r = 0; r < 5; r++)
	   {
		   for (int c = 0; c < 5; c++)
		   {
			   std::cout << " " << alphabet[c][r] << " ";
		   }
		   std::cout << std::endl;
	   }
   }

   void find(char alphabet[][5], char findme, int& x, int& y)
   {
	   for (int r = 0; r < 5; r++)
	   {
		   for (int c = 0; c < 5; c++)
		   {
			   if (alphabet[c][r] == findme)
			   {
				   x = c;
				   y = r;
				   return;
			   }

		   }
	   }
   }
   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
	   const std::string& password)
   {
		  std::string temp = plainText;
		  std::string cipherText = "";
		  char alphabet[5][5];
		  buildPolybiusSquare(alphabet, password);
		  displayPolybiusSquare(alphabet);
		  int x, y;
		  std::list<int> xs;
		  std::list<int> ys;
		  for (int i = 0; i < temp.size(); i++)
		  {

			  if (temp[i] == 'j')
			  {
				  temp[i] = 'i';
			  }
			  if (temp[i] == ' ')
			  {
				  continue;
			  }
			  find(alphabet, temp[i], x, y);
			  xs.push_back(x);
			  ys.push_back(y);
		  }
		  xs.splice(xs.end(), ys);
		  for (auto it = xs.begin(); it != xs.end();advance(it,2)) 
		  {

			  cipherText += alphabet[*it][*std::next(it)];
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
      // TODO - Add your code here
      return plainText;
   }
};

#endif // CIPHER02_H