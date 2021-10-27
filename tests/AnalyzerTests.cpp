#include <gtest/gtest.h>
#include "../src/FileAnalyzer.hpp"
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(FileInformation, CountWords)
{
    Analyzer::FileInformation fileTest(std::filesystem::path(""));
    fileTest.SetContent("Ala has a cat, cat has Ala");

    EXPECT_EQ(fileTest.GetCountCharacters(),20);
}

TEST(FileInformation, CountCharacters)
{
    Analyzer::FileInformation fileTest(std::filesystem::path(""));
    fileTest.SetContent("Ala has a cat, cat has Ala");

    EXPECT_EQ(fileTest.GetCountWords(), 7);
}

TEST(FileAnalyzer, SingleThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");    
    std::vector<Analyzer::DirectoryInformation> directories;
    std::vector<Analyzer::FileInformation> files;

    fileAnalyzer.SingleThreadGetDirectoryContent(pathToTestDirectory.relative_path(), &directories, &files);

    EXPECT_EQ(directories.size(),3);
    EXPECT_EQ(files.size(), 6);
}

TEST(FileAnalyzer, TwoThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::vector<Analyzer::DirectoryInformation> directories;
    std::vector<Analyzer::FileInformation> files;

    fileAnalyzer.MultiThreadGetDirectoryContent(pathToTestDirectory.relative_path(), &directories, &files,2);

    EXPECT_EQ(directories.size(), 3);
    EXPECT_EQ(files.size(), 6);
}

TEST(FileAnalyzer, FourThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::vector<Analyzer::DirectoryInformation> directories;
    std::vector<Analyzer::FileInformation> files;

    fileAnalyzer.MultiThreadGetDirectoryContent(pathToTestDirectory.relative_path(), &directories, &files, 4);

    EXPECT_EQ(directories.size(), 3);
    EXPECT_EQ(files.size(), 6);
}