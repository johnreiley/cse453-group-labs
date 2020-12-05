/********************************************************************
 * File: unit-tests.h
 * Author:
 *    Benjamin Hansen
 * Summary:
 *    Unit Tests to verify the W12-Bell-LaPadula behaves according to
 *    the exact behavior defined by Bell-LaPadula to assure
 *    their proofs validate the security of this system.
 *********************************************************************/
#include "unit-tests.h"
#define NAME "Unit Test"
using namespace std;

/***********************************************************
 * Run Unit Tests
 * Run the tests that will support our claim
 * that our program behaves in the 
 * exact contraints defined by Bell-LaPadula
 * for a secure system. These tests support
 * our claim that for every possible appearance 
 * (as Bell-LaPadula defines), every appearance of a subject
 * or use of the system is
 * secure and that no compromise possibilities exist.
 ************************************************************/
void runUnitTests()
{
    cout << endl << NAME << ": Testing securityControlRead\n";
    Control general = Control::PUBLIC;
    // general public shouldn't be able to read any type of confidential stuff
    assert(!securityControlRead(Control::CONFIDENTIAL, general));
    assert(!securityControlRead(Control::PRIVILEGED, general));
    assert(!securityControlRead(Control::SECRET, general));
    // general public should be able to read any public stuff
    assert(securityControlRead(Control::PUBLIC, general));

    Control confidant = Control::CONFIDENTIAL;
    // confidant shouldn't be able to read anything higher than confidential
    assert(!securityControlRead(Control::PRIVILEGED, confidant));
    assert(!securityControlRead(Control::SECRET, confidant));
    // confidant should be able to read anything confidential or lower
    assert(securityControlRead(Control::CONFIDENTIAL, confidant));
    assert(securityControlRead(Control::PUBLIC, confidant));

    Control privy = Control::PRIVILEGED;
    // privy shouldn't be able to read anything higher than priviledged 
    assert(!securityControlRead(Control::SECRET, privy));
    // privy should be able to read anything confidential or lower
    assert(securityControlRead(Control::PUBLIC, privy));
    assert(securityControlRead(Control::CONFIDENTIAL, privy));
    assert(securityControlRead(Control::PRIVILEGED, privy));
    
    Control seek = Control::SECRET;
    // seek should be able to read anything 
    assert(securityControlRead(Control::PUBLIC, seek));
    assert(securityControlRead(Control::CONFIDENTIAL, seek));
    assert(securityControlRead(Control::PRIVILEGED, seek));
    assert(securityControlRead(Control::SECRET, seek));
    cout << NAME << ": Passed securityControlRead tests\n";
    
    cout << endl << NAME << ": Testing securityControlWrite\n";
    // general public should be able to write to any asset
    assert(securityControlWrite(Control::PUBLIC, general));
    assert(securityControlWrite(Control::CONFIDENTIAL, general));
    assert(securityControlWrite(Control::PRIVILEGED, general));
    assert(securityControlWrite(Control::SECRET, general));

    // confidant should be able to write to anything confidential or higher
    assert(securityControlWrite(Control::PRIVILEGED, confidant));
    assert(securityControlWrite(Control::SECRET, confidant));
    assert(securityControlWrite(Control::CONFIDENTIAL, confidant));
    // confidant shouldn't be able to write to anything lower than confidential
    assert(!securityControlWrite(Control::PUBLIC, confidant));

    // privy shouldn't be able to write to anything lower than priviledged
    assert(!securityControlWrite(Control::PUBLIC, privy));
    assert(!securityControlWrite(Control::CONFIDENTIAL, privy));
    // privy should be able to write anything priviledged or higher
    assert(securityControlWrite(Control::PRIVILEGED, privy));
    assert(securityControlWrite(Control::SECRET, privy));
    
    // seek shouldn't be able to write anything except secret
    assert(!securityControlWrite(Control::PUBLIC, seek));
    assert(!securityControlWrite(Control::CONFIDENTIAL, seek));
    assert(!securityControlWrite(Control::PRIVILEGED, seek));
    // seek should be able to write secret assets 
    assert(securityControlWrite(Control::SECRET, seek));
    cout << NAME << ": Passed securityControlWrite tests\n";
}

