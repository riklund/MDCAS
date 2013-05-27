/**\file EventHit_TEST.hh
   \author Rikard Lundmark
   \brief Header file for the EventHit test class.
   \ingroup UnitTests
*/
/**\file EventHit_TEST.cc
   \author Rikard Lundmark
   \brief Source file for the EventHit t
   \ingroup UnitTests
*/


using namespace std;
#ifndef ASSERT_H
#define ASSERT_H//!<Inclusion guard.
#include <assert.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM//!<Inclusion guard.
#include <iostream>
#endif

#ifndef LIST
#define LIST//!<Inclusion guard.
#include <list>
#endif

#ifndef STRING
#define STRING//!<Inclusion guard.
#include <string>
#endif

#include "FileEventParser.hh"
#include "EventHit.hh"
#include "GenericUnitTest.hh"
#include "HitType.hh"

#ifndef EVENTHIT_TEST_HH
#define EVENTHIT_TEST_HH//!<Inclusion guard.

/** Test class for the EventHit class. 
    \author Rikard Lundmark
    \todo Add more test cases.
    \ingroup UnitTests
 */
class EventHit_TEST: public GenericUnitTest
{
 public:
  int runUnitTests() const; //!<Run the unit tests.
 protected:
  bool DoubleEquality(double d1, double d2, double eps) const; //!<Double equality.
  bool EventHit_ClassifiesCorrectly_AssertTrue() const; //!<Test.
};

#endif
