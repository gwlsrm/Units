// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "FileUtilsTests.h"

#include <string>
#include "fileutils.h"
#include "test_runner.h"

using namespace std;

void TestAllFileUtils() {
    TestRunner tr;
    RUN_TEST(tr, TestLevelUp);
    RUN_TEST(tr, TestExpandFilePath);
    RUN_TEST(tr, TestExtractFilePath);
    RUN_TEST(tr, TestExtractFileName);
    RUN_TEST(tr, TestExpandFileExt);
}

void TestExtractFilePath() {
    ASSERT_EQUAL(extractFilePath("C:\\lsrm\\test\\text.txt"), "C:\\lsrm\\test\\");
}

void TestExtractFileName() {
    ASSERT_EQUAL(extractFileName("C:\\lsrm\\test\\text.txt"), "text.txt");
}

void TestLevelUp() {
    ASSERT_EQUAL(goOneLevelUp("C:\\lsrm\\test\\"), "C:\\lsrm\\");
    ASSERT_EQUAL(goOneLevelUp("C:\\lsrm\\test"), "C:\\lsrm\\");
    ASSERT_EQUAL(goOneLevelUp("C:\\lsrm\\"), "C:\\");
    ASSERT_EQUAL(goOneLevelUp("C:\\"), "C:\\");
}

void TestExpandFilePath() {
    // simple variants
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("C:\\lsrm\\test\\test.txt", "C:\\"), "C:\\lsrm\\test\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm\\"), "C:\\lsrm\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("test.txt", "C:\\lsrm"), "C:\\lsrm\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("test\\test.txt", "C:\\lsrm\\"), "C:\\lsrm\\test\\test.txt");
    // variants with ".."
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test\\"), "C:\\lsrm\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\test"), "C:\\lsrm\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm\\"), "C:\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\lsrm"), "C:\\test.txt");
    ASSERT_EQUAL(expandFileNamesToRelBaseDir("..\\test.txt", "C:\\"), "C:\\test.txt");
}

void TestExpandFileExt() {
    ASSERT_EQUAL(extractFileExt("C:\\lsrm\\test\\test.txt"), string(".txt"));
    ASSERT_EQUAL(extractFileExt("C:\\lsrm\\test\\test"), string(""));
}
