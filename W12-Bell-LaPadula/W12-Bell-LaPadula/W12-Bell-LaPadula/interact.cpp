/***********************************************************************
 * COMPONENT:
 *    INTERACT
 * Author:
 *    Br. Helfrich, <your name here if you made a change>
 * Summary:
 *    This class allows one user to interact with the system
 ************************************************************************/

#include <iostream>   // standard input and output
#include <string>     // for convenience
#include <cassert>    // because I am paraniod
#include <stdlib.h>   // for atoi 
#include <vector>     // for std::vector
#include "messages.h" // to interact with the collection of messages
#include "control.h"  // all the Bell-LaPadula stuff
#include "interact.h" // the interact class and User structure

using namespace std;

/**************************************************************
 * USERS
 * All the users currently in the system
 * Make it a vector so users can be added or modified easily
 *************************************************************/
vector<User> users =
{
   { "AdmiralAbe",     "password", SECRET },
   { "CaptainCharlie", "password", PRIVILEGED },
   { "SeamanSam",      "password", CONFIDENTIAL },
   { "SeamanSue",      "password", CONFIDENTIAL },
   { "SeamanSly",      "password", CONFIDENTIAL }
};

const int ID_INVALID = -1;

/****************************************************
 * INTERACT constructor
 * Authenticat ethe user and get him/her all set up
 ***************************************************/
Interact::Interact(const string& userName,
   const string& password,
   Messages& messages)
{
   authenticate(userName, password);
   this->userName = userName;
   this->pMessages = &messages;
}

/****************************************************
 * INTERACT :: SHOW
 * show a single message
 ****************************************************/
void Interact::show() const
{
   Control userControl = users[idFromUser(userName)].userControl;

   int messageId = promptForId("display");
   Control messageControl = pMessages->getMessageControl(messageId);

   if (securityControlRead(messageControl, userControl))
   {
       pMessages->show(messageId);
   }
}

/****************************************************
 * INTERACT :: DISPLAY
 * display the set of messages
 ***************************************************/
void Interact::display() const
{
   Control userControl = users[idFromUser(userName)].userControl;
   pMessages->display(userControl);
}

/****************************************************
 * INTERACT :: ADD
 * add a single message
 ****************************************************/
void Interact::add()
{
   int id = idFromUser(userName);
   pMessages-> add(users[id].userControl,
      promptForLine("message"),
      userName,
      promptForLine("date"));
}

/****************************************************
 * INTERACT :: UDPATE
 * update a single message
 ****************************************************/
void Interact::update()
{
   Control userControl = users[idFromUser(userName)].userControl;

   int messageId = promptForId("update");
   Control messageControl = pMessages->getMessageControl(messageId);

   if (securityControlWrite(messageControl, userControl))
   {
      pMessages->update(messageId,
      promptForLine("message"));
   }
   else
   {
      cout << "You do not have access to update this asset." << endl;
   } 
}

/****************************************************
 * INTERACT :: REMOVE
 * remove one message from the list
 ***************************************************/
void Interact::remove()
{
   Control userControl = users[idFromUser(userName)].userControl;

   int messageId = promptForId("delete");
   Control messageControl = pMessages->getMessageControl(messageId);

   if (securityControlWrite(messageControl, userControl))
   {
      pMessages->remove(messageId);
   }
   else
   {
      cout << "You do not have access to remove this asset." << endl;
   }
}

/****************************************************
 * INTERACT :: DISPLAY USERS
 * display the set of users in the system
 ***************************************************/
void displayUsers()
{
   for (int idUser = 0; idUser < users.size(); idUser++)
      cout << "\t" << users[idUser].name << endl;
}

/****************************************************
 * INTERACT :: PROMPT FOR LINE
 * prompt for a line of input
 ****************************************************/
string Interact::promptForLine(const char* verb) const
{
   string line;
   cout << "Please provide a " << verb << ": ";
   getline(cin, line);
   return line;
}

/****************************************************
 * INTERACT :: PROMPT FOR ID
 * prompt for a message ID
 ***************************************************/
int Interact::promptForId(const char* verb) const
{
   string id;
   cout << "Select the message ID to " << verb << ": ";
   cin >> id;
   cin.ignore();
   return atoi(id.c_str());
}

/****************************************************
 * INTERACT :: AUTHENTICATION
 * authenticate the user: find their control level
 ****************************************************/
Control Interact::authenticate(const string& userName,
   const string& password) const
{
   int id = idFromUser(userName);
   if (ID_INVALID != id && password == string(users[id].password))
	   return users[id].userControl;
   else
	   return PUBLIC;
}

/****************************************************
 * INTERACT :: ID FROM USER
 * Find the ID of a given user
 ****************************************************/
int Interact::idFromUser(const string& userName) const
{
   for (int idUser = 0; idUser < users.size(); idUser++)
      if (userName == string(users[idUser].name))
         return idUser;
   return ID_INVALID;
}
