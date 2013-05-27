/** \file RunTests.hh
    \author Rikard Lundmark
    \brief Header for the unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** \file RunTests.cc
    \author Rikard Lundmark
    \brief The unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** @defgroup UnitTests Unit tests
 *  Unit tests for the ENSDF++ software.
 \author Rikard Lundmark
 \todo Create more unit tests
 */


using namespace std;
#ifndef ASSERT_H
#define ASSERT_H //!<Inclusion guard.
#include <assert.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM //!<Inclusion guard.
#include <iostream>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard.
#include <list>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard.
#include <string>
#endif

#include "GenericUnitTest.hh"
#include "FileEventParser_TEST.hh"
#include "EventHit_TEST.hh"

#ifndef RUNTESTS_H
#define RUNTESTS_H //!<Inclusion guard.
int main();//!<The main test function and program entry point.
void addTests(); //!<Called by main() to prepare the test cases.
list<GenericUnitTest*> myTests; //!<The existing test cases.
#endif
