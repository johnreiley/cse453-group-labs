/********************************************************************
 * File: unit-tests.h
 * Author:
 *    Benjamin Hansen
 * Summary:
 *    Unit Tests to verify the W12-Bell-LaPadula behaves according to
 *    the exact behavior defined by Bell-LaPadula to assure
 *    their proofs validate the security of this system.
 *********************************************************************/
#pragma once 

#include <iostream>
#include <cassert>
#include "control.h"
#include "interact.h"
#include "messages.h"
#include "message.h"
#include "control.h"

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
void runUnitTests();
