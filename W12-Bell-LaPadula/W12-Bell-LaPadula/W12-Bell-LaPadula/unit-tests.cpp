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

void runUnitTests()
{
    cout << endl << NAME << ": Testing securityControlRead\n";
    Control general = Control::PUBLIC;
    // general public shouldn't be able to read any type of confidential stuff
    assert(!securityControlRead(Control::CONFIDENTIAL, general));
    assert(!securityControlRead(Control::PRIVILEDGED, general));
    assert(!securityControlRead(Control::SECRET, general));
    // general public should be able to read any public stuff
    assert(securityControlRead(Control::PUBLIC, general));

    Control confidant = Control::CONFIDENTIAL;
    // confidant shouldn't be able to read anything higher than confidential
    assert(!securityControlRead(Control::PRIVILEDGED, confidant));
    assert(!securityControlRead(Control::SECRET, confidant));
    // confidant should be able to read anything confidential or lower
    assert(securityControlRead(Control::CONFIDENTIAL, confidant));
    assert(securityControlRead(Control::PUBLIC, confidant));

    Control privy = Control::PRIVILEDGED;
    // privy shouldn't be able to read anything higher than confidential
    assert(!securityControlRead(Control::SECRET, privy));
    // privy should be able to read anything confidential or lower
    assert(securityControlRead(Control::PUBLIC, privy));
    assert(securityControlRead(Control::CONFIDENTIAL, privy));
    assert(securityControlRead(Control::PRIVILEDGED, privy));
    
    Control seek = Control::SECRET;
    // seek should be able to read anything 
    assert(securityControlRead(Control::PUBLIC, seek));
    assert(securityControlRead(Control::CONFIDENTIAL, seek));
    assert(securityControlRead(Control::PRIVILEDGED, seek));
    assert(securityControlRead(Control::SECRET, seek));
    cout << NAME << ": Passed securityControlRead tests\n";
}
