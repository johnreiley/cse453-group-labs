/***********************************************************************
 * Program:
 *    Lab 8, ANSI-Unicode Conversion
 *    Brother Wilson, CS453
 * Author:
 *    John Reiley
 * Summary:
 *    Write code demonstrating an ANSI-Unicode conversion vulnerability.
 *    Estimated: 1 hrs
 *    Actual: 1.5 hrs
 * <problems ran into...>
 ************************************************************************/
#include <iostream>
using namespace std;

void ansiVulnerability(char phrase[64]);
void ansiWorking();
void ansiExploit();


int main() {
  ansiWorking();
  ansiExploit();

  return 0;
}

/*************************************
 * ANSI VULNERABILTY
 * 1. There must be a buffer where the basetype is greater than one.
 * 2. Validation of the buffer must check the size of the buffer 
 *    rather than the number of elements in the buffer
 ****************************************/
void ansiVulnerability(char phrase[64])
{
  int asciiPhrase[5];
  int importantNums[15] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377 };

  cout << "\nimportantNums before: ";
  for (int i = 0; i < 15; i++)
    cout << importantNums[i] << " ";

  // convert the first 5 letters to ASCII values
  for (int i = 0; i < sizeof(asciiPhrase); i++)
    asciiPhrase[i] = (int)phrase[i];

  cout << "\nasciiPhrase: ";
  for (int i = 0; i < 5; i++)
    cout << asciiPhrase[i] << " ";
  cout << "\nimportantNums after: ";
  for (int i = 0; i < 15; i++)
    cout << importantNums[i] << " ";
  cout << endl;
}

/**************************************
 * ANSI WORKING
 * Call ansiVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void ansiWorking()
{
  cout << "\n/**************************\n"
       << "*ansiWorking()\n"
       << "**************************/";
  // simulate user input
  char phrase[15] = "Hello world!";

  ansiVulnerability(phrase);
}

/**************************************
 * ANSI EXPLOIT
 * 1. The attacker must provide more than half as much data into
 *    the outwardly facing buffer as it is designed to hold
 * 2. From here, a variety of injection attacks are possible. The
 *    most likely candidates are stack smashing or heap smashing.
 *************************************/
void ansiExploit()
{
  cout << "\n/**************************\n"
       << "*ansiExploit()\n"
       << "**************************/";
  // simulate user input
  char phrase[64] = "101010101010101010101010101010101010101010101010101010101010";

  ansiVulnerability(phrase);
}