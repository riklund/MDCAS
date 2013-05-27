/** \file GenericUnitTest.hh
    \author Rikard Lundmark
    \brief Generic test class
    \ingroup Unit tests
*/
/**
   \file GenericUnitTest.cc
   \author Rikard Lundmark
   \brief Generic test class
 */

using namespace std;

#ifndef GENERIC_UNIT_TEST_H
#define GENERIC_UNIT_TEST_H //!<Inclusion guard
/**A generic unit test. To be extended.*/
class GenericUnitTest
{
 public:
  virtual int runUnitTests() const = 0; //!<Run the tests.
  GenericUnitTest(); //!<Constructor, constructs the class.
};
#endif
