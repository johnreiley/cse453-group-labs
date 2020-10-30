/**********************************************************
 * File: W07-Memory-Organization.cpp
 *
 * Authors: Benjamin Hansen, Justen Neeley, John Reiley,
 *      Joseph Sanderson, Garrett Smith
 *
 * Description: This program displays the call-stack of
 *      the loaded program at execution. It also demontrates
 *      the ability to use that information to change variables
 *      outside of the scope of main.
 *********************************************************/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

// display helping funciton for validation of addresses
void displayAddressExamples();

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456; // binary: 
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
   
   for (long i = 24; i >= -4; i--)   // You may need to change 24 to another number
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      cout << '[' << setw(2) << i << ']'
         << setw(8) << "0x" << hex << &text
         << setw(20) << hex << "stuff here"
         << setw(20) << dec << "more stuff here"
         << setw(18) << displayCharArray(text) << endl;
      //
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()
                                                                                
   // change text in main() to "*main**"

   // change number in main() to 654321

   // just to help see stuff
   displayAddressExamples(); // use this to check assumptions visually

   // Benjamin's Idea
   const char * search = (char *)&bow; // start here like assignment says
   while (*((long *)search) != 123456)
   {
       search++; // increment one byte up at a time
   }
   cout << "\nTrying to change memory here. Found the long int!\n"
        << "\nStarting address...\n"
        << "Stack: " << &search 
        << endl;


   // change pointerFunction in main() to point to pass

   // change message in main() to point to passMessage

   //
   ////////////////////////////////////////////////
}

/******************************************************************************
 * displayAddressExamples
 * Not needed, but useful for seeing what the address displays look like for
 * stack variable, heap memory, or code segment.
 * ANY AND ALL CAN EDIT THIS CODE AS THEY PLEASE, within reason
 ******************************************************************************/
void displayAddressExamples()
{
    cout << "\nDisplaying address examples\n";
    int funNum = 99;

    // Stack variables
    cout << "Stack: " << &funNum << endl;
    
    int * pHeap = new int(5); // initialized to 5
    // Heap address
    cout << "Heap: " << pHeap << endl;

    // Code segment
    cout << "Code: " << "unsolved for now" << endl;

    // don't forget to free
    delete pHeap;
    pHeap = NULL;
}
