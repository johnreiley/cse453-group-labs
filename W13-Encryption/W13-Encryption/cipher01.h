/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

#include <fstream>

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
public:
   virtual std::string getPseudoAuth() { return "Benjamin Hansen"; }
   virtual std::string getCipherName() { return "Playfair"; }
   virtual std::string getEncryptAuth() { return "Garrett Smith"; }
   virtual std::string getDecryptAuth() { return "decrypt author"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
       std::string s = "Al-Kazaz, N., Irvine, S., & Teahan, W. (2018). \n";
       s += "\tAn Automatic Cryptanalysis of Playfair Ciphers Using \n";
       s += "\tCompression. Proceedings Of The 1St Conference On Historical \n";
       s += "\tCryptology, 119. Retrieved 11 December 2020, from \n";
       s += "\thttps://ep.liu.se/ecp/149/021/ecp18149021.pdf. \n";
       s += "Alam, A., Khalid, B., & Salam, C. (2013). A Modified Version of \n";
       s += "\tPlayfair Cipher Using 7×4 Matrix. International Journal Of \n";
       s += "\tComputer Theory And Engineering, 5(4), 626. Retrieved 11 December \n";
       s += "\t2020, from http://www.ijcte.org/papers/762-C0168.pdf. \n";
       s += " Basu, S., & Ray, U. (2012). Modified Playfair Cipher \n";
       s += "\tusing Rectangular Matrix. International Journal Of \n";
       s += "\tComputer Applications, 46(9), 28. Retrieved 10 December \n";
       s += "\t2020, from https://d1wqtxts1xzle7.cloudfront.net/32997645\n";
       s += "\t/Modified_Playfair_Cipher_using_Rectangular_Matrix.pdf?\n";
       s += "\t1392421760=&response-content-disposition=inline%3B+f\n";
       s += "\tilename%3DModified_Playfair_Cipher_using_Rectangul.p\n";
       s += "\tdf&Expires=1607645195&Signature=a-r~uo68P5p45NJ3Nkn\n";
       s += "\tEDRjNYu6MLt4JdG4nkaO4LH9TgEwTkWyaWzQoU--NwtBfH7-~QTC\n";
       s += "\t~rZTv6R0WG5GF0WUF43OQUOpNSN8GprMxNFWcI9yR9rmGDSifhmId\n";
       s += "\tMfiNnyl6flS3qCi~M8zwytvzNfKWHEDCUxjZEexgDsaONCYp9G7G8w\n";
       s += "\tMRAbLi7knnMrvL-KtpI7E7ADh-0rv6x4f3Olbtnxk8qVWqmiJCqDh0E\n";
       s += "\tZu7CEBPST1p8KsAvLzR9w55ZidJz~VfnLs0Etn7KCwKZcoU-ZPDqp7IJ\n";
       s += "\tCm7Xc8p-jsAl-kPqACq-Zu~SqyjBstlBNib5PiDrxZMUdXYH3jXYA__&K\n";
       s += "\tey-Pair-Id=APKAJLOHF5GGSLRBV4ZA. \n";
       s += "Dhenakaran, S., & Llayaraja, M. (2012). Extension of \n";
       s += "\tPlayfair Cipher using 16X16 Matrix. International Journal \n";
       s += "\tOf Computer Applications, 48(7), 37. Retrieved 10 \n";
       s += "\tDecember 2020, from http://citeseerx.ist.psu.edu/\n";
       s += "\tviewdoc/download?doi=10.1.1.258.7527&rep=rep1&type=pdf.  \n";
       s += "Rembert, L. (2020). Playfair Cipher. Privacy Canada. \n";
       s += "\tRetrieved 10 December 2020, from https://privacycanada.net/\n";
       s += "\tclassical-encryption/playfair-cipher/.\n";
      return s;
   }

   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str = "";
      std::string temp = "";

      std::ifstream fin("playfair-pseudocode.txt");

      if (fin.fail())
      {
          std::cerr << "Error reading playfair-pseudocode.txt\n";
          return "";
      }
      // else continue
     
      while (std::getline(fin, temp))
      {
          str += temp;
      }

      return str;
   }

   /**********************************************************
    * BUILD POLYBIUS SQUARE
    * Creates the 5x5 square that is used to encrypt data
    **********************************************************/
   virtual void buildPolybiusSquare(char square[][5], std::string key)
   {
   string alphabet = "abcdefghi*klmnopqrstuvwxyz";
   string polybius = "";  
   for(int i = 0; i < key.size(); i++)
   {
      if(key[i] != 'j')
      {

         key[i] = tolower(key[i]);
      }
      else
      {
         continue;
      }

      if( key[i] == alphabet[(int)key[i] - 97])
      {
         polybius += key[i];
         alphabet[(int)key[i] - 97] = '*';
       
      }
                                   
   }
   polybius += alphabet;
   int i = 0;
   for(int r = 0; r < 5; r++)
      for(int c = 0; c < 5; c++)
      {
         
         square[c][r] = polybius[i];
         i++;
         while(polybius[i] == '*')
         i++;
      }   
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string& plainText,
      const std::string& password)
   {
      std::string cipherText = plainText;
      char matrix[5][5];
      buildPolybiusSquare(matrix, password);
      
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

#endif // CIPHER01_H
