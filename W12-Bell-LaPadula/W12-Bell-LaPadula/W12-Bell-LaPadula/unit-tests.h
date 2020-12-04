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
using namespace std;

void runUnitTests();
