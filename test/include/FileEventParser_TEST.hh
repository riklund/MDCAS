/**\file FileEventParser_TEST.hh
   \author Rikard Lundmark
   \brief Header file for the FileEventParser test class.
   \ingroup UnitTests
*/
/**\file FileEventParser_TEST.cc
   \author Rikard Lundmark
   \brief Source file for the FileEventParser t
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

#ifndef FILEEVENTPARSER_TEST_HH
#define FILEEVENTPARSER_TEST_HH//!<Inclusion guard.

/** Test class for the FileEventParser class. 
    \author Rikard Lundmark
    \todo Add more test cases.
    \ingroup UnitTests
 */
class FileEventParser_TEST: public GenericUnitTest
{
 public:
  int runUnitTests() const; //!<Run the unit tests.
 protected:
  bool DoubleEquality(double d1, double d2, double eps) const; //!<Double equality.
  bool FileEventParser_OpensFile_AssertTrue() const; //!<Test.
  bool FileEventParser_ReturnsCorrectNumberOfHits_AssertTrue() const; //!<Test
  bool FileEventParser_ReturnsCorrectHits_AssertTrue() const; //!<Test


};

#endif
