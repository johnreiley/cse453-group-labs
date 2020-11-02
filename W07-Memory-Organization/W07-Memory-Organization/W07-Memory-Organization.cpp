/**********************************************************
 * File: W07-Memory-Organization.cpp
 *
 * Authors: Benjamin Hansen, Justen Neeley, John Reiley,
 *      Joseph Sanderson, Garrett Smith
 *
 * Description: This program displays the call-stack of
 *      the loaded program at execution. It also demonstrates
 *      the ability to use that information to change variables
 *      outside of the scope of main.
 *********************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
// to disable asserts, un-comment this directive
// this will cause the compiler to not compile asserts
#define NDEBUG
#include <cassert>
using namespace std;

void one(long number);
void two(long number);
void pass() 
{ 
   cout << "You pass :)\n"; 
}
void fail() 
{ 
   cout << "You've failed :(\n"; 
}
const char * passMessage = ":)"; 
const char * failMessage = ":(";

// display helping function for validation of addresses
void displayAddressExamples();

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**"; // hex: 0x2a4d41494e2a2a
   long number = 123456; // hex: 0x1E240 
   // robustness test
   // testing adding local variable doesn't change solution
   long long stillWorks = 1234591823;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // ensure assumptions are met

   // asserting variable value changes
   // testing change to text[8] to "*main**"
   assert(text[0] == '*');
   assert(text[1] == 'm');
   assert(text[2] == 'a');
   assert(text[3] == 'i');
   assert(text[4] == 'n');
   assert(text[5] == '*');
   assert(text[6] == '*');
   assert(text[7] == '\0'); // last should be the null character
   // testing change to number
   assert(number == 654321);
   // testing change to pointerFunction
   assert(pointerFunction == pass); // do they point to the same address
   // testing change to message
   assert(message == passMessage); // do they hold the same address

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
      output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;

   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
      << setw(15) << "address"
      << setw(20) << "hexadecimal"
      << setw(20) << "decimal"
      << setw(18) << "characters"
      << endl;
   cout << "----+"
      << "---------------+"
      << "-------------------+"
      << "-------------------+"
      << "-----------------+\n";

   // TODO: define current here
   char * current;
   for (long i = 50; i >= -4; i--) 
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      current = (char*)((char*)&bow + 8 * i);

      cout << '[' << setw(2) << i << ']'
         << setw(15) << (void*)current
         << setw(20) << std::hex << std::showbase << *(long*)current
         << setw(20) << std::dec << *(long*)current
         << setw(18) << displayCharArray(current) << endl;
      //
      ////////////////////////////////////////////////
   }

   // just to help see stuff
   displayAddressExamples(); // use this to check assumptions visually

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()

   // change text in main() to "*main**"

   const char * search = (char *)&bow; // start here like assignment says
   // probe the memory until the text in main is found
   // convert to string for efficient comparison
   while (string(search) != "*MAIN**")
   {
      search++; // increment one byte up the stack at a time
   }
   assert(string(search) == "*MAIN**");
   cout << "\nTrying to change memory here. Found the text!\n"
      << "\nStarting address...\n"
      << "Stack: " << (void *)search 
      << endl;
   cout << "Text was: " << string(search) << endl;
   // not constant so we can change the value
   // get the starting address that we want from the const pointer 
   char * changeText = (char *)search;
   // change text's value in main to "*main**"
   // do it one at a time because we have a character array
   // procedural code, line-after-line, is the most efficient in terms of speed
   changeText[0] = '*';
   changeText[1] = 'm';
   changeText[2] = 'a';
   changeText[3] = 'i';
   changeText[4] = 'n';
   changeText[5] = '*';
   changeText[6] = '*'; // change the variable outside of its scope!

   // don't access through changeText... 
   // prove we updated what search pointed to
   cout << "Text now is: " << string(search) << endl;

   // change number in main() to 654321

   // do it the sure-fire way
   pLong = (long *)&bow;
   while (*pLong != 123456)
   {
      pLong++; // increment up 8 bytes at a time
   }
   assert(*pLong == 123456);

   // to have a robust solution, we must allow added local variables or
   // less local variables in main. Thus, always searching from this scope
   // up is more robust.
   // we can still change number here
   cout << "\nTrying to change memory here. Found the long int!\n"
      << "\nStarting address...\n"
      << "Stack: " << pLong
      << endl;
   cout << "Long number was: " << *pLong << endl;
   // not constant so we can change the value
   *pLong = 654321; // change the variable outside of its scope!
   cout << "Now is: " << *pLong << endl;


   // change pointerFunction in main() to point to pass

   // so far I can't get this logic to compile
   // start the search upward (increment search) instead of downward
   // start the search at
   // assert assumptions

   pLong = (long *)&bow;

   // do it the sure-fire way
   while (*pLong != (long)fail)
   {
      pLong++; // increment up 8 bytes at a time
   }
   assert(*pLong == (long)fail);
   cout << "\nTrying to change memory here. Found the pointerFunction!\n"
      << "\nStarting address...\n"
      << "Stack: " << pLong 
      << "\nWas: " << *pLong << endl;
   // set the 8 bytes pointed to by pLong to the pass address, as a long
   *pLong = (long)pass; 
   cout << "Now is: " << *pLong << endl;
   
   // change message in main() to point to passMessage
   pLong = (long *)&bow;
   while (*pLong != (long)failMessage)
   {
      pLong++; // increment up 8 bytes at a time
   }
   cout << "\nTrying to change memory here. Found the message!\n"
      << "\nStarting address...\n"
      << "Stack: " << pLong
      << endl;
   cout << "Message was: " << string((char *)*pLong) << endl;
   // set the memory location's value pLong points to the long address of 
   // passMessage
   *pLong = (long)passMessage; // change the variable outside of its scope!
   cout << "Now is: " << string((char *)*pLong) << endl << endl;
   //
   ////////////////////////////////////////////////
}

/**************************************************************************
 * displayAddressExamples
 * Not needed, but useful for seeing what the address displays look like for
 * stack variable, heap memory, or code segment.
 * ANY AND ALL CAN EDIT THIS CODE AS THEY PLEASE, within reason
 **************************************************************************/
void displayAddressExamples()
{
   cout << "\nDisplaying address examples\n";
   int funNum = 99;

   // Stack variables
   cout << "Stack: " << &funNum << endl;

   int * pHeap = new int(5); // initialized to 5
   // Heap address
   cout << "Heap: " << pHeap << endl;

   static string addressed = "this is here";
   // Code segment
   cout << "Code: " << &addressed << endl;

   // don't forget to free
   delete pHeap;
   pHeap = NULL;
}
