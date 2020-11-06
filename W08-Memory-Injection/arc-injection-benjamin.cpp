// Benjamin's Arc Injection Idea
#include <iostream>
#include <fstream>
#ifdef _WIN32 
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cassert>
using namespace std;

/***********************************************************
 * SAVED
 * Display success message for saving the private key to 
 * special-key.txt
 ***********************************************************/
void saved()
{
   cout << "Favorite Numbers have been saved at favorite-nums.txt\n";
}

/***********************************************************
 * FAILED SAVE
 * Display fail message for saving the private key to 
 * special-key.txt
 ***********************************************************/
void failedSave()
{
   cout << "Error: Favorite Numbers have failed saving to favorite-nums.txt\n";
}
/***********************************************************
 * ARC INJECTION VULNERABILITY
 * From (Helfrich, "Security for Software Engineers", 2019)
 * 1.  "There must be a function pointer used in the code."
 * 2.  "Through some vulnerability, there must be a way for
 *      user input to overwrite the function pointer. This 
 *      typically happens through a stack buffer 
 *      vulnerability."
 * 3.  "After the memory is overwritten, the function 
 *      pointer must be dereferenced."
 * The solution was helped by Baltasarq's post in this 
 * Stack Overflow post:
 * https://stackoverflow.com/questions/3811328/try-to-write-char-to-a-text-file
 **********************************************************/
void arcVulnerability(const long favoriteNums[], long int length)
{
   // load the 128-byte key into a char buffer
   long buffer[8]; // limit 8 longs
   void (* endMessage)() = saved;

   cout << "&length: " << &length << endl
      << "buffer: " << (void *)buffer << endl 
      << "endMessage: " << &endMessage << endl;
   // for some reason, length is allocated after
   // buffer and endMessage on the stack
   assert(buffer > (long *)&endMessage && (long *)&endMessage);

   // write the longs to our buffer
   for (--length; length >= 0; --length)
   {
      cout << "Rolling out " << favoriteNums[length] << endl;
      buffer[length] = favoriteNums[length];
      cout << "Buffer: " << buffer[length] << endl;
   }

   cout << "Buffer[9]: " << buffer[9] << endl;

   //assert((long)endMessage == (long)failedSave);

   // the work
   cout << "Now Writing Favorite Nums to File\n";

   ofstream ofs;
   ofs.open("favorite-nums.txt", ios::out);

   // check for failures
   if (ofs.fail())
   {
      // update endMessage to reflect failure
      endMessage = failedSave; 
   }
   else // we're good to write
   {
      for(int i = 0; i < 8; ++i)
      {
         ofs << buffer[i] << endl;
      }
      ofs.close(); // close the file
   }

   // display the end message
   (*endMessage)();

   cout << endl;

   return;
}

/***********************************************************
 * ARC INJECTION EXPLOIT
 * From (Helfrich, "Security for Software Engineers", 2019)
 * 1.  "The attacker must exploit a vulnerability allowing 
 *      unintended access to the function pointer."
 * 2.  "The attacker must have the address of another 
 *      function which is to be used to replace the existing
 *      function pointer."
 **********************************************************/
void arcExploit()
{
   // create a 128 character-string
   /*
   string key = "cUWt+]}IBr/b~d ;~b&yW<C|<f Klu%3d[WUZ;P*E<";
   key += "lr=~mxJnIP}bf#a#<+.kZN.[}RT_<8vp>B*] ;.5Kn~p+e$NF";
   key += "ZVN+j9sL&8(P:pZ/nH|MW/ECr.?sz@fIKJ$`.";
   */
   long numbers[9] = {
      123, 321, 432, 543, 654, 
      765, 876, 9999, (long)failedSave
   };
   arcVulnerability(numbers, 9 /*length*/);
   return;
}

/***********************************************************
 * ARC INJECTION WORKING
 * Initiate normal behavior of arcVulerability()
 **********************************************************/
void arcWorking()
{
   long numbers[8] = {
      123, 321, 432, 543, 654, 
      765, 876, 9999
   };
   arcVulnerability(numbers, 8 /*length*/);
   return;
}

int main()
{
   arcWorking();
   arcExploit();
   return 0;
}

