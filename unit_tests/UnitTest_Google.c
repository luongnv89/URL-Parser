/**
 * This is the UnitTest based on Google Test platform
 * Install Google Test platform:
 * 	
 * $ apt-get update -y
 * $ apt-get install -y cmake
 * $ git clone https://github.com/google/googletest.git
 * $ cd googletest/googletest/ 
 * $ mkdir build 
 * $ cd build/ 
 * $ cmake ..
 * $ make 
 * $ make install
 *
 * Compile Test:
 * 
 * Run all the test with Google Test Framework:
 * - http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html
 * - https://www.ibm.com/developerworks/aix/library/au-googletestingframework.html
*/

#include <limits.h>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}