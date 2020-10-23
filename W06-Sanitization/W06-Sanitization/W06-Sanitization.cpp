/*****************************************************
 * Title: W06 Sanitization Lab
 * Members: John Reiley, Benjamin Hansen, Justen Neeley, 
 *     Joseph Sanderson, Garrett Smith
 * 
 * Description: Basic SQL select statement generator
 *****************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <locale> // tolower
#include <regex>

using namespace std;
static string weakMitigation(string value);
static string strongMitigation(string value);
static void testTautology();
static void testUnion();
static void testAddStatement();
static void testComment();
static vector<string> split(string value, char delimiter);
static string join(vector<string> values, char delimiter);
static string to_lower(string s);

int main()
{
    testTautology();
    testUnion();
    testAddStatement();
    testComment();

    string username = "";
    string password = "";
    cout << "Username: "; 
    cin >> username;
    cout << "Password: "; 
    cin >> password; 

    cout << endl;
    // Shouldn't this be in a genQuery() standard function?
    cout << "SELECT authenticate" << endl 
        << "FROM passwordList" << endl 
        << "WHERE name=" + username + " AND password=" + password;
}

/*****************************************
 * This function whitelists the input by 
 * retaining only those characters that 
 * satisfy as a valid username and password,
 * namely: letters, numbers, and underscores
 *****************************************/
static string strongMitigation(string value)
{
    // split the sql up into a vector of strings
    vector<string> splitValues = split(value, ' ');
    // The std::regex to filter the sql string with
    const regex filterString = "^[a-zA-Z0-9_]+$";
    
    // whitelist the value input to contain only valid characters
    // put the valid query in sanitized
    string sanitized = regex_replace(value, filterString, ""); // no fmt string


    return sanitized;
}

/*****************************************
* This function removes the following from
* the input string value:
* 'UNION'
* 'OR'
* single quotes
* semicolons
* comments (--)
*****************************************/
static string weakMitigation(string value) 
{
    // split the sql
    vector<string> splitValues = split(value, ' ');
    string cleanValue = "";

    // Look for dirtysql
    for (int i = 0; i < splitValues.size(); i++)
    {
        string segment = splitValues[i];
        
        if (segment.find(';') != string::npos)
        {
            // remove the semicolon
            segment = join(split(segment, ';'), '\0');
        }
        if (segment.find("'") != string::npos)
        {
            // remove the single quotes
            segment = join(split(segment, '\''), '\0');
        }
        if (to_lower(segment) == "union" || segment.find("--") != string::npos)
        {
            return cleanValue;
        }
        if (to_lower(segment) == "or")
        {
            continue;
        }

        cleanValue += segment;
        if (i < splitValues.size() - 1)
        {
            cleanValue += " ";
        }
    }

    return cleanValue;
}

static void testTautology()
{
    string username = "Root";
    string password = "nothing' OR 'x' = 'x'";
    string weakCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + weakMitigation(username) + "' and passwd='" + weakMitigation(password) + "';";
    string strongCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + strongMitigation(username) + 
                        "' and passwd='" + strongMitigation(password) + "';";
    cout << "testTautology results: \n";
    cout << "Weak Mitigation: " << weakCleanSql << endl << endl;
    cout << "Strong Mitigation: " << strongCleanSql << endl << endl;
}

static void testUnion() 
{
    string username = "Root";
    string password = "nothing' UNION SELECT authenticate FROM passwordList";
    string weakCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + weakMitigation(username) + "' and passwd='" + weakMitigation(password) + "';";
    string strongCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + strongMitigation(username) + 
                        "' and passwd='" + strongMitigation(password) + "';";
    cout << "testUnion results: \n";
    cout << "Weak Mitigation: " << weakCleanSql << endl << endl;
    cout << "Strong Mitigation: " << strongCleanSql << endl << endl;
}

static void testAddStatement()
{
    string username = "Root";
    string password = "nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234";
    string weakCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + weakMitigation(username) + "' and passwd='" + weakMitigation(password) + "';";
    string strongCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + strongMitigation(username) + 
                        "' and passwd='" + strongMitigation(password) + "';";
    cout << "testAddStatement results: \n";
    cout << "Weak Mitigation: " << weakCleanSql << endl << endl;
    cout << "Strong Mitigation: " << strongCleanSql << endl << endl;
}

static void testComment()
{
    string username = "'Root' ; --";
    string password = "'nothing";
    string weakCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + weakMitigation(username) + "' and passwd='" + weakMitigation(password) + "';";
    string strongCleanSql = "SELECT authenticate\n" 
                        "FROM passwordList\n" 
                        "WHERE name='" + strongMitigation(username) + 
                        "' and passwd='" + strongMitigation(password) + "';";
    cout << "testComment results: \n";
    cout << "Weak Mitigation: " << weakCleanSql << endl << endl;
    cout << "Strong Mitigation: " << strongCleanSql << endl << endl;
}

static vector<string> split(string value, char delimeter)
{
    vector<string> splitString;
    string segment = "";

    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] != delimeter)
        {
            segment += value[i];
        }
        else
        {
            splitString.push_back(segment);
            segment = "";
        }
    }

    if (segment != " ")
    {
       splitString.push_back(segment);
    }

    return splitString;
}

static string join(vector<string> values, char delimeter)
{
    string joinedString = "";

    for (int i = 0; i < values.size(); i++)
    {
        joinedString += values[i];
        if (i < values.size() - 1) 
        {
            joinedString += delimeter;
        }
    }

    return joinedString;
}

static string to_lower(string s) {        
    for(char &c : s)
        c = tolower(c);
    return s;
}
