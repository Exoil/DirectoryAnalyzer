#include "FileInformation.hpp"

using namespace Analyzer;

FileInformation::FileInformation(std::filesystem::path pathToFile)
    : BaseFileInformation(pathToFile)
{
    SetInformation();
}

void FileInformation::SetInformation()
{
    BaseFileInformation::SetInformation();
    extension = path.extension();
    size = std::filesystem::file_size(path);
    SetCountWords();
    SetCountCharacters();
}

std::string FileInformation::ReadFile()
{
    return "";
}

void FileInformation::SetCountWords()
{
    countWords = 0;
    std::string fileContent = ReadFile();
}

void FileInformation::SetCountCharacters()
{
    countCharacters = 0;
    std::string fileContent = ReadFile();
}

std::string FileInformation::ToString()
{
    std::stringstream buffer;
    buffer << "FileType: File ";
    buffer << BaseFileInformation::ToString() << " ";
    buffer << "size: " << size << " ";
    buffer << "extension: " << extension << " ";
    buffer << "Word count: " << countWords << " ";
    buffer << "Character count: " << countCharacters << " ";
    std::string outputString = buffer.str();

    return outputString;
}