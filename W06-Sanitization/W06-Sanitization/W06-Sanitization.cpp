/*****************************************************
 * Title: W06 Sanitization Lab
 * Members: John Reiley, Benjamin Hansen, Justen Neeley, 
 *     Joseph Sanderson, Garrett Smith
 * 
 * Description: Basic SQL select statement generator
 *****************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string username = "";
    string password = "";
    cout << "Username: "; 
    cin >> username;
    cout << "Password: "; 
    cin >> password; 

    cout << endl;
    cout << "SELECT authenticate" << endl 
        << "FROM passwordList" << endl 
        << "WHERE name=" + username + " and password=" + password;
}

