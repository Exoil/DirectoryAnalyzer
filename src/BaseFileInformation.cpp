#include "FileInformation.hpp"

using namespace Analyzer;

BaseFileInformation::BaseFileInformation(std::filesystem::path pathToFile) : 
    path(pathToFile)
{
    SetInformation();
}

void BaseFileInformation::SetInformation()
{

}

std::string BaseFileInformation::ToString()
{
    std::stringstream buffer;
    buffer << "Name: " << path.filename() << " ";

    if (path.has_parent_path())
        buffer << "Parent name" << path.parent_path().filename() << " ";
    else
        buffer << "Parent name: no parent" <<" ";

    buffer << "Last modification time" << lastModificationTime << " ";
    
    std::string outputString = buffer.str();

    return outputString;
}