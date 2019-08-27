// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "gwstrTests.h"

#include "test_runner.h"
#include "str_utils.h"

using namespace std;

void TestTrim();
void TestToLower();
void StartsWith();
void TestJoinStrings();

void TestAllStrUtils() {
    TestRunner tr;
    RUN_TEST(tr, TestTrim);
    RUN_TEST(tr, TestToLower);
    RUN_TEST(tr, StartsWith);
    RUN_TEST(tr, TestJoinStrings);
}

void TestTrim() {
    //cout << "'" << trim("   test string   ") << "'" << endl;
    ASSERT_EQUAL(trim("   test string   "), "test string");
    ASSERT_EQUAL(trim("   test string"), "test string");
    ASSERT_EQUAL(trim("test string   "), "test string");
    ASSERT_EQUAL(trim("test string"), "test string");
    ASSERT_EQUAL(trim("test string "), "test string");
    ASSERT_EQUAL(trim(" test string"), "test string");
    ASSERT_EQUAL(trim(" "), "");
    ASSERT_EQUAL(trim("\n"), "");
    // trim right
    ASSERT_EQUAL(trim_right("   test string   "), "   test string");
    ASSERT_EQUAL(trim_right("   test string"), "   test string");
    ASSERT_EQUAL(trim_right("test string   "), "test string");
    ASSERT_EQUAL(trim_right("test string"), "test string");
    ASSERT_EQUAL(trim_right("test string "), "test string");
    ASSERT_EQUAL(trim_right(" test string"), " test string");
    ASSERT_EQUAL(trim_right(" "), "");
    ASSERT_EQUAL(trim_right("\n"), "");
}

void TestToLower() {
    ASSERT_EQUAL(str_tolower("Test string"), "test string");
    ASSERT_EQUAL(str_tolower("TesT StrIng"), "test string");
    ASSERT_EQUAL(str_tolower("test string"), "test string");
}

void StartsWith() {
    ASSERT(startWith("Test string", "Test"));
    ASSERT(startWith(string("Test string"), string("Test")));
    ASSERT(!startWith(string("Test string"), string("test")));
    ASSERT(startWith(string("  Test string"), string("  Test")));
    ASSERT(startWith(string("  Test"), string("  Test")));
    ASSERT(!startWith(string("  Test"), string("  Test ")));
    ASSERT(!startWith(("  Test"), ("  Test ")));
}

void TestJoinStrings() {
  ASSERT_EQUAL(join_strings({"str1", "str2", "str3"}), "str1 str2 str3");
  ASSERT_EQUAL(join_strings({"str1", "str2", "str3"}, ','), "str1,str2,str3");
  const vector<string> si {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  ASSERT_EQUAL(
    join_strings({"-" + si[5], "-" + si[10], si[2], "(", si[9], ":", si[4], ")"}),
    "-" + si[5] + " -" + si[10] + " " + si[2] + " ( " + si[9] + " : " + si[4] + " )"
  );
}
