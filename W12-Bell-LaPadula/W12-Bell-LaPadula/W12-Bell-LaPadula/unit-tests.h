/********************************************************************
 * File: unit-tests.h
 * Author:
 *    Benjamin Hansen
 * Summary:
 *    Unit Tests to verify the W12-Bell-LaPadula behaves according to
 *    the exact behavior defined by Bell-LaPadula to assure
 *    their proofs validate the security of this system.
 *********************************************************************/
#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <iostream>
#include <cassert>
#include "control.h"
#include "interact.h"
#include "messages.h"
#include "message.h"

void runUnitTests();

#endif // UNIT_TESTS_H
