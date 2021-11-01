#include <gtest/gtest.h>
#include "../src/FileAnalyzer.hpp"
#include <iostream>

TEST(FileInformation, CountWords)
{
    Analyzer::FileInformation fileTest(std::filesystem::path(""));
    fileTest.SetContent("Ala has a cat, cat has Ala");

    EXPECT_EQ(fileTest.GetCountCharacters(), 20);
}

TEST(FileInformation, CountCharacters)
{
    Analyzer::FileInformation fileTest(std::filesystem::path(""));
    fileTest.SetContent("Ala has a cat, cat has Ala");

    EXPECT_EQ(fileTest.GetCountWords(), 7);
}

TEST(FileAnalyzer, SuccessSingleThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation>
        directories;
    std::list<Analyzer::FileInformation> files;

    fileAnalyzer.SingleThreadGetDirectoryContent(pathToTestDirectory.string(), &directories, &files);

    EXPECT_EQ(directories.size(), 3);
    EXPECT_EQ(files.size(), 6);
}

TEST(FileAnalyzer, NullDirectorylistArgumentSingleThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::FileInformation> files;

    EXPECT_THROW(fileAnalyzer.SingleThreadGetDirectoryContent(
                     pathToTestDirectory.string(),
                     nullptr,
                     &files),
                 std::invalid_argument);
}

TEST(FileAnalyzer, NullFilelistArgumentSingleThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation> directories;

    EXPECT_THROW(fileAnalyzer.SingleThreadGetDirectoryContent(
                     pathToTestDirectory.string(),
                     &directories,
                     nullptr),
                 std::invalid_argument);
}

TEST(FileAnalyzer, EmptyStringArgumentSingleThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::list<Analyzer::DirectoryInformation> directories;
    std::list<Analyzer::FileInformation> files;

    EXPECT_THROW(fileAnalyzer.SingleThreadGetDirectoryContent(
                     "",
                     &directories,
                     &files),
                 std::invalid_argument);
}

TEST(FileAnalyzer, SuccesTwoThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation> directories;
    std::list<Analyzer::FileInformation> files;

    fileAnalyzer.MultiThreadGetDirectoryContent(pathToTestDirectory.string(), &directories, &files, 2);

    EXPECT_EQ(directories.size(), 3);
    EXPECT_EQ(files.size(), 6);
}

TEST(FileAnalyzer, SuccesFourThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation> directories;
    std::list<Analyzer::FileInformation> files;

    fileAnalyzer.MultiThreadGetDirectoryContent(pathToTestDirectory.string(), &directories, &files, 4);

    EXPECT_EQ(directories.size(), 3);
    EXPECT_EQ(files.size(), 6);
}

TEST(FileAnalyzer, NullDirectorylistArgumentMultiThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::FileInformation> files;

    EXPECT_THROW(fileAnalyzer.MultiThreadGetDirectoryContent(
                     pathToTestDirectory.string(),
                     nullptr,
                     &files,
                     2),
                 std::invalid_argument);
}

TEST(FileAnalyzer, NullFilelistArgumentMultiThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation> directories;

    EXPECT_THROW(fileAnalyzer.MultiThreadGetDirectoryContent(
                     pathToTestDirectory.string(),
                     &directories,
                     nullptr,
                     2),
                 std::invalid_argument);
}

TEST(FileAnalyzer, EmptyStringArgumentMultiThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::list<Analyzer::DirectoryInformation> directories;
    std::list<Analyzer::FileInformation> files;

    EXPECT_THROW(fileAnalyzer.MultiThreadGetDirectoryContent(
                     "",
                     &directories,
                     &files,
                     2),
                 std::invalid_argument);
}

TEST(FileAnalyzer, ZeroThreadMultiThreadGetDirectoryContent)
{
    Analyzer::FileAnalyzer fileAnalyzer;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path pathToTestDirectory = currentPath.parent_path().append("TestDirectory");
    std::list<Analyzer::DirectoryInformation> directories;
    std::list<Analyzer::FileInformation> files;

    EXPECT_THROW(fileAnalyzer.MultiThreadGetDirectoryContent(
                     pathToTestDirectory.string(),
                     &directories,
                     &files,
                     0),
                 std::invalid_argument);
}