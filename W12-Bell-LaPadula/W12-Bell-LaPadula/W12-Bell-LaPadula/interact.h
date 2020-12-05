/***********************************************************************
 * COMPONENT:
 *    INTERACT
 * Author:
 *    Br. Helfrich, Benjamin Hansen (added friends to class) 
 *    <your name here if you made a change>
 * Summary:
 *    This class allows one user to interact with the system
 ************************************************************************/

#pragma once

#include <string>     // for convenience
#include <vector>     // for users
#include "messages.h" // to interact with the collection of messages
#include "control.h"  // all the Bell-LaPadula stuff

 /**************************************************************
  * USER
  * All the users currently in the system
  *************************************************************/
struct User
{
   const char* name;
   const char* password;
   Control userControl;
};

/****************************************************
 * INTERACT
 * One user interacting with the system
 ***************************************************/
class Interact
{
    /*************************************************
     * make runUnitTests() in unit-tests.h a friend
     * of interact so it can access and test Interact's 
     * member variable usage
     * to create a fool-proof unit test, we can't test
     * functionality using other functions, we need 
     * direct access to the data
     *************************************************/
    friend void runUnitTests(); // define in unit-tests.h
public:
   Interact(const std::string& userName,
      const std::string& password,
      Messages& messages);

   // show a single message
   void show() const;

   // display the set of messages
   void display() const;

   // add a single message
   void add();

   // update a single message
   void update();

   // remove one message from the list
   void remove();

private:
   Messages* pMessages;
   std::string userName;

   // prompt for a line of input
   std::string promptForLine(const char* verb) const;

   // prompt for a message ID
   int promptForId(const char* verb) const;

   // authenticate the user;
   Control authenticate(const std::string& userName,
      const std::string& password) const;

   // find the ID of a given user
   int idFromUser(const std::string& userName) const;
};

// display the set of users in the system
void displayUsers();
