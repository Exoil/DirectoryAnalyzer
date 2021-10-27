#include "FileInformation.hpp"

using namespace Analyzer;

FileInformation::FileInformation(std::filesystem::path pathToFile)
    : BaseFileInformation(pathToFile)
{
    if(!pathToFile.empty())
        SetInformation();
}

void FileInformation::SetInformation()
{
    BaseFileInformation::SetInformation();
    _extension = path.extension();
    _size = std::filesystem::file_size(path);
    SetContent();
}

void FileInformation::SetContent()
{
    _content = "";
    std::fstream fileToRead(path);

    if (!fileToRead.is_open())
        return;

    _content.assign((std::istreambuf_iterator<char>(fileToRead)),
                       (std::istreambuf_iterator<char>()));
}

void FileInformation::SetContent(std::string content)
{
    _content = content;
}

unsigned int FileInformation::GetCountWords()
{
    unsigned _countWords = 0;
    std::string contentCopy = _content;
    std::vector<std::string> splitedStirng;
    std::istringstream iss(contentCopy);
    std::string word;

    while (std::getline(iss, word, ' '))
        splitedStirng.push_back(word);

    _countWords = splitedStirng.size();
    splitedStirng.clear();
    iss.clear();

    return _countWords;
}

unsigned int FileInformation::GetCountCharacters()
{
    unsigned int countCharacters = 0;
    std::string contentCopy = _content;
    std::erase(contentCopy, ' ');
    std::erase(contentCopy, '\n');

    countCharacters = contentCopy.size();

    return countCharacters;
}

void FileInformation::SetContent(std::string content)
{
    _content = content;
}

std::string FileInformation::ToString()
{
    std::stringstream buffer;
    buffer << "FileType: File ";
    buffer << BaseFileInformation::ToString() << " ";
    buffer << "size: " << _size << " ";
    buffer << "extension: " << _extension << " ";
    buffer << "Word count: " << GetCountWords() << " ";
    buffer << "Character count: " << GetCountCharacters() << " ";
    std::string outputString = buffer.str();

    return outputString;
}
